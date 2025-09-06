/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2024-2024. All rights reserved.
 */
#include "kvecturbo.h"

#include <securec.h>
#include <algorithm>
#include <arm_neon.h>
#include <atomic>
#include <cassert>
#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <float.h>
#include <iostream>
#include <limits>
#include <memory>
#include <omp.h>
#include <queue>
#include <random>
#include <vector>

namespace PQHead {

/*
 * @brief Union for variable attribute data storage
 */
union Varattrib4b {
    /* Normal varlena (4-byte length) */
    struct {
        unsigned int vaHeader;
        char vaData[FLEXIBLE_ARRAY_MEMBER];
    } va4byte;
    /* Compressed-in-line format */
    struct {
        unsigned int vaHeader;
        unsigned int vaRawsize;             /* Original data size (excludes header) */
        char vaData[FLEXIBLE_ARRAY_MEMBER]; /* Compressed data */
    } vaCompressed;
};

/*
 * @brief Structure for 1-byte variable attribute data
 */
struct Varattrib1b {
    unsigned char vaHeader;
    char vaData[FLEXIBLE_ARRAY_MEMBER]; /* Data begins here */
};

/*
 * @brief Calculate the aligned size based on the given alignment value
 * @param alignVal Alignment value
 * @param len Length to align
 * @return Aligned size
 */
uintptr_t TYPEALIGN(size_t alignVal, size_t len)
{
    return (len + (alignVal - 1)) & ~(alignVal - 1);
}

/*
 * @brief Calculate the maximum aligned size
 * @param len Length to align
 * @return Maximum aligned size
 */
uintptr_t MAXALIGN(size_t len)
{
    return TYPEALIGN(MAXIMUM_ALIGNOF, len);
}

/*
 * @brief Calculate the size of a vector based on its dimension
 * @param dim Vector dimension
 * @return Size of the vector
 */
size_t VECTOR_SIZE(int dim)
{
    return offsetof(Vector, x) + sizeof(float) * dim;
}

/*
 * @brief Get the address of a vector in the array at the specified offset
 * @param arr Vector array
 * @param offset Offset of the vector
 * @return Pointer to the vector data
 */
char *VectorArrayGet(VectorArray arr, int offset)
{
    return (static_cast<char *>(arr->items)) + (offset * arr->itemSize);
}

/*
 * @brief Set the value of a VectorArray at a specific offset using memcpy
 * @param arr Pointer to the VectorArray
 * @param offset Offset within the VectorArray
 * @param val Pointer to the source data
 * @param vecSize Size of the data to copy
 * @return 0 on success, -1 on failure
 */
int VectorArraySet(VectorArray arr, int offset, char *val, size_t vecSize)
{
    void *dest = VectorArrayGet(arr, offset);
    size_t arrSize = arr->itemSize;
    errno_t result = memcpy_s(dest, arrSize, val, vecSize);
    if (result != 0) {
        std::cerr << "memcpy_s failed in VectorArraySet : " << result << std::endl;
        return -1;
    }
    return 0;
}

/*
 * @brief Random number generator class
 */
class kvecturbo {
public:
    /*
     * @brief Constructor for random number generator
     * @param seed Initial seed value (default: 42)
     */
    explicit kvecturbo(unsigned int seed = 42) : mt(seed), dist(0.0f, 1.0f)
    {}

    /*
     * @brief Generate a random float value
     * @return Random float value between 0.0f and 1.0f
     */
    float operator()()
    {
        return dist(mt);
    }

    /*
     * @brief Get the underlying random engine
     * @return Reference to the random engine
     */
    std::mt19937 &GetEngine()
    {
        return mt;
    }

private:
    std::mt19937 mt;
    std::uniform_real_distribution<float> dist;
};

/*
 * @brief Calculate L2 distance using NEON SIMD instructions
 * @param a First vector
 * @param b Second vector
 * @param size Vector dimension
 * @return L2 distance between the vectors
 */
float L2Distance2Simd(const float *a, const float *b, int size)
{
    int dim = size;
    const float *pa = a;
    const float *pb = b;

    float sum = 0.0f;
    int i = 0;

    /* Use NEON instructions to process four elements at a time */
    float32x4_t sum_vec = vdupq_n_f32(0.0f);
    for (; i + 3 < dim; i += 4) {
        float32x4_t va = vld1q_f32(pa + i);
        float32x4_t vb = vld1q_f32(pb + i);
        float32x4_t diff = vsubq_f32(va, vb);
        sum_vec = vmlaq_f32(sum_vec, diff, diff); /* sum_vec += diff * diff */
    }

    /* Sum the elements of sum_vec */
    float32x2_t sum_vec_low = vget_low_f32(sum_vec);
    float32x2_t sum_vec_high = vget_high_f32(sum_vec);
    float32x2_t sum_pair = vpadd_f32(sum_vec_low, sum_vec_high);
    float32x2_t sum_total = vpadd_f32(sum_pair, sum_pair);
    sum += vget_lane_f32(sum_total, 0);

    /* Handle remaining elements */
    for (; i < dim; i++) {
        float diff = pa[i] - pb[i];
        sum += diff * diff;
    }

    return sum;
}

/*
 * @brief Copy data from source to destination in VectorArray
 * @param arr Pointer to the VectorArray
 * @param offset Offset within the VectorArray
 * @param src Source data pointer
 * @param newDim Number of elements to copy
 * @return 0 on success, -1 on failure
 */
static inline int VectorArrayCopy(VectorArray arr, int offset, float *src, int newDim)
{
    float *dst = reinterpret_cast<Vector *>(VectorArrayGet(arr, offset))->x;
    if (dst == nullptr) {
        std::cerr << "Error: VectorArrayGet returned dst is nullptr" << std::endl;
        return -1;
    }
    size_t bytesToCopy = newDim * sizeof(float);
    size_t dstSize = arr->itemSize;
    errno_t result = memcpy_s(dst, dstSize, src, bytesToCopy);
    if (result != 0) {
        std::cerr << "Error: memcpy_s failed with dst and src: " << result << std::endl;
        return -1;
    }
    return 0;
}

/*
 * @brief Initialize a vector array
 * @param maxLen Maximum number of vectors
 * @param dimensions Vector dimension
 * @param itemSize Size of each vector item
 * @return Pointer to the initialized vector array, nullptr on failure
 */
VectorArray VectorArrayInit(int maxLen, int dimensions, size_t itemSize)
{
    VectorArray res = static_cast<VectorArray>(malloc(sizeof(VectorArrayData)));
    if (res == nullptr) {
        std::cerr << "Error: VectorArrayInit failed and returned nullptr" << std::endl;
        return nullptr;
    }

    /* Ensure items are aligned to prevent UB */
    itemSize = MAXALIGN(itemSize);

    res->length = 0;
    res->maxLen = maxLen;
    res->dim = dimensions;
    res->itemSize = itemSize;
    res->items = static_cast<char *>(calloc(maxLen, itemSize));
    if (res->items == nullptr) {
        free(res);
        std::cerr << "Error: VectorArrayInit items failed and returned nullptr" << std::endl;
        return nullptr;
    }
    return res;
}

/*
 * @brief Release a vector array and free its memory
 * @param arrays Vector array to release
 */
void VectorArrayRelease(VectorArray arrays)
{
    if (arrays == nullptr) {
        return;
    }
    if (arrays->items != nullptr) {
        free(arrays->items);
		arrays->items = nullptr;
    }
    free(arrays);
	arrays == nullptr;
}
/*
 * @brief Split a vector array into subarrays
 * @param arr Input vector array
 * @param subnum Number of subspaces
 * @param chunkNum Chunk number to process
 * @return Pointer to the split vector array, nullptr on failure
 */
VectorArray VectorArraySplitSingle(VectorArray arr, int subnum, int chunkNum)
{
    int originalDim = arr->dim;
    if ((subnum <= 0) || (originalDim % subnum != 0)) {
        return nullptr;
    }

    int newDim = originalDim / subnum;

    /* Step 1: Initialize all subarrays serially */
    VectorArray array = VectorArrayInit(arr->maxLen, newDim, VECTOR_SIZE(newDim));
    if (array == nullptr) {
        std::cerr << "Error: Init arrays failed and returned nullptr" << std::endl;
        VectorArrayRelease(array);
        return nullptr;
    }
    array->length = arr->length;

    /* Step 2: Parallel split vectors */
    std::atomic<bool> errCondition(false);
#pragma omp parallel for
    for (int index = 0; index < arr->length; index++) {
        if (errCondition.load()) {
            continue;
        }

        Vector *originalVec = reinterpret_cast<Vector *>(VectorArrayGet(arr, index));
        if (originalVec == nullptr) {
            std::cerr << "Error: VectorArrayGet returned originalVec is nullptr at index " << index << std::endl;
            errCondition.store(true);
            continue;
        }

        float *src = originalVec->x + (chunkNum * newDim);
        int err = VectorArrayCopy(array, index, src, newDim);
        if (err != 0) {
            std::cerr << "Error: VectorArrayCopy failed at index " << index << std::endl;
            errCondition.store(true);
            continue;
        }
    }

    if (errCondition) {
        VectorArrayRelease(array);
        return nullptr;
    }

    return array;
}

/*
 * @brief Initialize a vector with the given dimension
 * @param dim Vector dimension
 * @return Pointer to the initialized vector, nullptr on failure
 */
Vector *InitVector(int dim)
{
    Vector *result;
    int size;

    size = VECTOR_SIZE(dim);
    result = static_cast<Vector *>(calloc(size, sizeof(Vector)));
    if (result == nullptr) {
        std::cerr << "Error: InitVector failed and returned nullptr" << std::endl;
        return nullptr;
    }

#ifdef WORDS_BIGENDIAN
    ((Varattrib4b *)(result))->va4byte.vaHeader = size & 0x3FFFFFFF;
#else
    /* Little-endian mode: Left shift by 2 bits */
    ((Varattrib4b *)(result))->va4byte.vaHeader = size << 2;
#endif

    result->dim = dim;
    return result;
}

/*
 * @brief Initialize cluster centers randomly
 * @param samples Sample data
 * @param centers Cluster centers to initialize
 * @param numSamples Number of samples
 * @param numCenters Number of cluster centers
 * @param dimension Vector dimension
 * @return 0 on success, -1 on failure
 */
int InitCenters(const float *samples, float *centers, int numSamples, int numCenters, int dimension)
{
    if (!samples || !centers || numSamples <= 0 || numCenters <= 0 || dimension <= 0) {
        std::cerr << "Error: Invalid input parameters" << std::endl;
        return -1;
    }

    if (numCenters > numSamples) {
        std::cerr << "Error: Number of centers cannot exceed number of samples" << std::endl;
        return -1;
    }

    /* Create random number generator with seed 42 */
    kvecturbo randGen(42);

    /* Create a vector containing all sample indices */
    std::vector<int> sampleIndices(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        sampleIndices[i] = i;
    }

    /* Shuffle sample indices randomly */
    std::shuffle(sampleIndices.begin(), sampleIndices.end(), randGen.GetEngine());

    /* Select the first numCenters samples as initial centers */
    for (int i = 0; i < numCenters; ++i) {
        size_t remainingSize = (numCenters - i) * dimension * sizeof(float);
        int idx = sampleIndices[i];
        errno_t result =
            memcpy_s(&centers[i * dimension], remainingSize, &samples[idx * dimension], sizeof(float) * dimension);
        if (result != 0) {
            /* Handle error. The function failed. */
            std::cerr << "Error: memcpy_s failed with centers and samples: " << result << std::endl;
            return -1;
        }
    }
    return 0;
}

/*
 * @brief Merge cluster aggregation results from a single thread to the global aggregation
 * @param agg Global aggregation buffer
 * @param centerCounts Global count of samples per center
 * @param threadAgg Thread's local aggregation buffer
 * @param threadCounts Thread's local count of samples per center
 * @param c Cluster index
 * @param dimensions Vector dimension
 */
void mergeClusterAggregate(float *agg, std::vector<int> &centerCounts, const std::vector<float> &threadAgg,
    const std::vector<int> &threadCounts, int c, int dimensions)
{
    if (threadCounts[c] > 0) {
        float *aggPtr = &agg[c * dimensions];
        const float *localAggPtr = &threadAgg[c * dimensions];
        for (int d = 0; d < dimensions; d++) {
            aggPtr[d] += localAggPtr[d];
        }
        centerCounts[c] += threadCounts[c];
    }
}

/*
 * @brief Merge thread aggregation results to the global aggregation buffer
 * @param threadAgg List of thread's local aggregation buffers
 * @param threadCounts List of thread's local count of samples per center
 * @param agg Global aggregation buffer
 * @param centerCounts Global count of samples per center
 * @param numThreads Number of threads
 * @param numCenters Number of clusters
 * @param dimensions Vector dimension
 */
void mergeThreadAggregates(const std::vector<std::vector<float>> &threadAgg,
    const std::vector<std::vector<int>> &threadCounts, float *agg, std::vector<int> &centerCounts, int numThreads,
    int numCenters, int dimensions)
{
    for (int t = 0; t < numThreads; t++) {
        for (int c = 0; c < numCenters; c++) {
            /* Call helper function to merge single cluster's thread aggregation */
            mergeClusterAggregate(agg, centerCounts, threadAgg[t], threadCounts[t], c, dimensions);
        }
    }
}

/*
 * @brief Accumulate a single sample to the specified local aggregation buffer
 * @param sample Sample data
 * @param center Target cluster index
 * @param localAgg Local aggregation buffer
 * @param localCounts Local count of samples per center
 * @param dimensions Vector dimension
 */
void accumulateSampleToCenter(
    const float *sample, int center, std::vector<float> &localAgg, std::vector<int> &localCounts, int dimensions)
{
    if (center >= 0 && center < static_cast<int>(localCounts.size())) {
        float *x = &localAgg[center * dimensions];
        for (int d = 0; d < dimensions; d++) {
            x[d] += sample[d];
        }
        localCounts[center]++;
    }
}

/*
 * @brief Aggregate samples assigned to each cluster
 * @param samples Sample data
 * @param agg Aggregation buffer
 * @param closestCenters Array indicating the closest cluster for each sample
 * @param numSamples Number of samples
 * @param numCenters Number of clusters
 * @param centerCounts Count of samples per center
 * @param dimensions Vector dimension
 */
void SumCenters(const float *samples, float *agg, const int *closestCenters, int numSamples, int numCenters,
    std::vector<int> &centerCounts, int dimensions)
{
    /* Use each thread's local aggregation buffer */
    int numThreads = omp_get_max_threads();
    size_t numCentersD = static_cast<size_t>(numCenters * dimensions);
    std::vector<std::vector<float>> threadAgg(numThreads, std::vector<float>(numCentersD, 0.0f));
    std::vector<std::vector<int>> threadCounts(numThreads, std::vector<int>(numCenters, 0));

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        std::vector<float> &localAgg = threadAgg[tid];
        std::vector<int> &localCounts = threadCounts[tid];
#pragma omp for nowait
        for (int i = 0; i < numSamples; i++) {
            int center = closestCenters[i];
            const float *sample = &samples[i * dimensions];
            /* Call helper function to accumulate sample to specified center */
            accumulateSampleToCenter(sample, center, localAgg, localCounts, dimensions);
        }
    }

    /* Merge all threads' aggregation results */
    std::fill(agg, agg + numCentersD, 0.0f);
    std::fill(centerCounts.begin(), centerCounts.end(), 0);

    /* Call merge function */
    mergeThreadAggregates(threadAgg, threadCounts, agg, centerCounts, numThreads, numCenters, dimensions);
}

/*
 * @brief Handle empty clusters or clusters with few samples by initializing randomly
 * @param agg Aggregation buffer
 * @param newCenters New cluster centers
 * @param centerCounts Count of samples per center
 * @param j Cluster index
 * @param dimensions Vector dimension
 * @param numCenters Number of clusters
 * @param randGen Random number generator
 * @param newCentersSize Size of new cluster centers buffer
 * @return 0 on success, -1 on failure
 */
int handleClusterOrInitializeRandomly(float *agg, float *newCenters, std::vector<int> &centerCounts, int j,
    int dimensions, int numCenters, kvecturbo &randGen, size_t *newCentersSize)
{
    int maxCenter = -1;
    int maxCount = 0;
    std::atomic<bool> errCondition(false);

    /* Find the cluster with the most samples */
#pragma omp critical
    {
        for (int c = 0; c < numCenters; c++) {
            if (centerCounts[c] > maxCount) {
                maxCount = centerCounts[c];
                maxCenter = c;
            }
        }

        if (maxCenter != -1 && maxCount > 1) {
            float *maxCenterSumBuffer = agg + maxCenter * dimensions;
            float *sumBuffer = agg + j * dimensions;

            errno_t result = memcpy_s(sumBuffer, *newCentersSize, maxCenterSumBuffer, dimensions * sizeof(float));
            if (result != 0) {
                std::cerr << "Error: memcpy_s failed with sumBuffer and maxCenterSumBuffer: " << result << std::endl;
                errCondition.store(true);
                goto critical_end;
            }

            /* Apply larger perturbation */
            float eps = 1e-4f; /* Increase the disturbance amount */
            for (int k = 0; k < dimensions; k++) {
                float perturbation = (k % 2 == 0) ? eps : -eps;
                sumBuffer[k] += perturbation;
                maxCenterSumBuffer[k] -= perturbation;
            }

            /* Update counts */
            int transferCount = maxCount / 2;
            if (transferCount == 0) {
                transferCount = 1;
            }
            centerCounts[j] = transferCount;
            centerCounts[maxCenter] -= transferCount;

            result = memcpy_s(&newCenters[j * dimensions], *newCentersSize, sumBuffer, dimensions * sizeof(float));
            if (result != 0) {
                std::cerr << "Error: memcpy_s failed with newCenters and sumBuffer: " << result << std::endl;
                errCondition.store(true);
                goto critical_end;
            }

            result = memcpy_s(
                &newCenters[maxCenter * dimensions], *newCentersSize, maxCenterSumBuffer, dimensions * sizeof(float));
            if (result != 0) {
                std::cerr << "Error: memcpy_s failed with newCenters and maxCenterSumBuffer: " << result << std::endl;
                errCondition.store(true);
                goto critical_end;
            }
        }
    critical_end:;
    }

    return errCondition.load() ? -1 : 0;
}

/*
 * @brief Compute new cluster centers
 * @param samples Sample data
 * @param agg Aggregation buffer
 * @param newCenters New cluster centers
 * @param centerCounts Count of samples per center
 * @param closestCenters Array indicating the closest cluster for each sample
 * @param numSamples Number of samples
 * @param numCenters Number of clusters
 * @param dimensions Vector dimension
 */
int ComputeNewCenters(const float *samples, float *agg, float *newCenters, std::vector<int> &centerCounts,
    const int *closestCenters, int numSamples, int numCenters, int dimensions)
{
    if (!samples || !agg || !newCenters || !closestCenters || numSamples <= 0 || numCenters <= 0 || dimensions <= 0) {
        std::cerr << "Error: Invalid input parameters" << std::endl;
        return -1;
    }

    size_t numCentersD = static_cast<size_t>(numCenters * dimensions);
    std::fill(agg, agg + numCentersD, 0.0f);
    std::fill(centerCounts.begin(), centerCounts.end(), 0);

    SumCenters(samples, agg, closestCenters, numSamples, numCenters, centerCounts, dimensions);

    thread_local kvecturbo randGen;

    std::atomic<bool> errCondition(false);

#pragma omp parallel shared(errCondition)
    {
        int nt = omp_get_num_threads();
        int rank = omp_get_thread_num();

        int c0 = (numCenters * rank) / nt;
        int c1 = (numCenters * (rank + 1)) / nt;

        for (int j = c0; j < c1; j++) {
#pragma omp cancellation point parallel
            if (errCondition.load())
                break;

            size_t offset = j * dimensions;
            size_t remainingBytes = (numCentersD - offset) * sizeof(float);
            float *sumBuffer = agg + j * dimensions;

            if (centerCounts[j] > 0) {
                float norm = 1.0f / centerCounts[j];
                for (int k = 0; k < dimensions; k++) {
                    sumBuffer[k] *= norm;
                }
                errno_t result = memcpy_s(&newCenters[offset], remainingBytes, sumBuffer, dimensions * sizeof(float));
                if (result != 0) {
#pragma omp critical
                    {
                        std::cerr << "Error: memcpy_s failed with error code: " << result << std::endl;
                        errCondition.store(true);
                    }
#pragma omp cancel parallel
                    break;
                }
            } else {
                if (handleClusterOrInitializeRandomly(
                        agg, newCenters, centerCounts, j, dimensions, numCenters, randGen, &remainingBytes) != 0) {
#pragma omp critical
                    {
                        std::cerr << "Error: Failed to handle empty cluster " << j << std::endl;
                        errCondition.store(true);
                    }
#pragma omp cancel parallel
                    break;
                }
            }
        }
    }
    return errCondition.load() ? -1 : 0;
}

/*
 * @brief Main K-means function
 * @param samples Sample data
 * @param centers Cluster centers
 * @param pqM Number of subspaces
 * @return 0 on success, -1 on failure
 */
int NormalKmeans(VectorArray samples, VectorArray centers, int pqM)
{
    if (!samples || !centers || pqM <= 0) {
        std::cerr << "Error: Invalid input parameters" << std::endl;
        return -1;
    }

    const int dimensions = centers->dim;
    int numCenters = centers->maxLen;
    const int numSamples = samples->length;

    /* Ensure number of centers doesn't exceed samples */
    if (numCenters > numSamples) {
        numCenters = numSamples;
    }

    /* Calculate array sizes */
    const size_t numSamplesD = static_cast<size_t>(numSamples) * dimensions;
    const size_t numCentersD = static_cast<size_t>(numCenters) * dimensions;

    /* Allocate memory with proper error handling */
    std::unique_ptr<float[]> samplesData;
    std::unique_ptr<float[]> centersData;
    std::unique_ptr<float[]> newCentersData;
    try {
        samplesData = std::make_unique<float[]>(numSamplesD);
        centersData = std::make_unique<float[]>(numCentersD);
        newCentersData = std::make_unique<float[]>(numCentersD);
    } catch (const std::bad_alloc &e) {
        std::cerr << "Error: Memory allocation failed - " << e.what() << std::endl;
        return -1;
    }

    /* Initialize arrays */
    std::fill(samplesData.get(), samplesData.get() + numSamplesD, 0.0f);
    std::fill(centersData.get(), centersData.get() + numCentersD, 0.0f);
    std::fill(newCentersData.get(), newCentersData.get() + numCentersD, 0.0f);

    /* Convert VectorArray to flat array with safety checks */
    std::atomic<bool> errCondition(false);
#pragma omp parallel for
    for (int i = 0; i < numSamples; i++) {
        if (errCondition.load()) {
            continue;
        }
        Vector *vec = reinterpret_cast<Vector *>(VectorArrayGet(samples, i));
        if (vec == nullptr) {
#pragma omp critical
            {
                std::cerr << "Error: VectorArrayGet returned vec is nullptr" << std::endl;
                errCondition.store(true);
            }
            continue;
        }
        size_t remainingSize = static_cast<size_t>((numSamples - i) * dimensions * sizeof(float));
        if (remainingSize > SECUREC_MEM_MAX_LEN) {
			remainingSize = SECUREC_MEM_MAX_LEN;
		}	
        errno_t result =
            memcpy_s(samplesData.get() + i * dimensions, remainingSize, vec->x, dimensions * sizeof(float));
        if (result != 0) {
            std::cerr << "Error: memcpy_s failed with samplesData and vec->x: " << result << std::endl;
            errCondition.store(true);
        }
    }
    if (errCondition.load()) {
        return -1;
    }

    /* Allocate and initialize clustering support structures */
    std::vector<int> centerCounts(numCenters, 0);
    auto closestCenters = std::make_unique<int[]>(numSamples);
    auto agg = std::make_unique<float[]>(numCentersD);
    std::fill(closestCenters.get(), closestCenters.get() + numSamples, -1);
    std::fill(agg.get(), agg.get() + numCentersD, 0.0f);

    /* Initialize cluster centers */
    if (InitCenters(samplesData.get(), centersData.get(), numSamples, numCenters, dimensions) != 0) {
        std::cerr << "Error: Failed to initialize centers" << std::endl;
        return -1;
    }

    /* Main K-means iteration loop */
    const int maxIterations = 30;
    for (int iteration = 0; iteration < maxIterations; iteration++) {
        /* Assign samples to nearest centers */
#pragma omp parallel for
        for (int j = 0; j < numSamples; j++) {
            float minDistance = std::numeric_limits<float>::max();
            int closestCenter = -1;
            const float *sample = samplesData.get() + j * dimensions;

            for (int k = 0; k < numCenters; k++) {
                const float *center = centersData.get() + k * dimensions;
                float dist = L2Distance2Simd(sample, center, dimensions);
                if (dist < minDistance) {
                    minDistance = dist;
                    closestCenter = k;
                }
            }

            closestCenters[j] = closestCenter;
        }

        /* Compute new cluster centers */
        if (ComputeNewCenters(samplesData.get(),
                agg.get(),
                newCentersData.get(),
                centerCounts,
                closestCenters.get(),
                numSamples,
                numCenters,
                dimensions) != 0) {
            std::cerr << "Error: Failed to Compute New Centers" << std::endl;
            return -1;
        }

        /* Update centers with boundary check */
        errno_t result =
            memcpy_s(centersData.get(), numCentersD * sizeof(float), newCentersData.get(), numCentersD * sizeof(float));
        if (result != 0) {
            std::cerr << "Error: memcpy_s failed with centersData and newCentersData: " << result << std::endl;
            return -1;
        }
    }

    /* Write final centers back to output structure */
    for (int i = 0; i < numCenters; i++) {
        Vector *vec = InitVector(dimensions);
        if (vec == nullptr) {
            std::cerr << "Error: InitVector failed and returned nullptr" << std::endl;
            return -1;
        }
        errno_t result = memcpy_s(
            vec->x, dimensions * sizeof(float), centersData.get() + i * dimensions, dimensions * sizeof(float));
        if (result != 0) {
            std::cerr << "Error: memcpy_s failed with vec->x and centersData: " << result << std::endl;
            free(vec);
            return -1;
        }
        size_t vecSize = VECTOR_SIZE(vec->dim);
        char *vecChar = reinterpret_cast<char *>(vec);
        if (vecChar == nullptr) {
            std::cerr << "Error: VectorArrayGet returned vecChar is nullptr" << std::endl;
            free(vec);
            return -1;
        }
        int err2 = VectorArraySet(centers, i, vecChar, vecSize);
        if (err2 != 0) {
            std::cerr << "Error: VectorArraySet failed" << std::endl;
            free(vec);
            return -1;
        }
        free(vec);
		vec = nullptr;
    }

    centers->length = numCenters;
    return 0;
}

/*
 * @brief Compute L2 squared distance for product quantization
 * @param step Step size for sub-vector processing
 * @param a Input vector
 * @param c Codebook
 * @param ksub Number of sub-centers
 * @param size Vector dimension
 * @return Index of the closest sub-center
 */
unsigned char VectorL2SquaredDistancePQ(int step, float *a, float *c, int ksub, int size)
{
    float minDis = FLT_MAX;
    int minIdx = -1;

    for (int k = 0; k < ksub; k++) {
        float *b = c + k * step;
        float distance = 0.0;

        for (int j = 0; j < size; j++) {
            float diff = a[j] - b[j];
            distance += diff * diff;
        }

        if (distance < minDis) {
            minDis = distance;
            minIdx = k;
        }
    }

    return minIdx;
}

/*
 * @brief Compute L2 squared distance between two vectors (reference implementation)
 * @param dim Vector dimension
 * @param ax First vector
 * @param bx Second vector
 * @return L2 squared distance
 */
float L2SquaredDistanceRef(int dim, float *ax, float *bx)
{
    float distance = 0.0f;
    for (int i = 0; i < dim; ++i) {
        float diff = ax[i] - bx[i];
        distance += diff * diff;
    }
    return distance;
}

/*
 * @brief Compute L2 squared distance using NEON instructions
 * @param dim Vector dimension
 * @param ax First vector
 * @param bx Second vector
 * @return L2 squared distance
 */
float L2SquaredDistanceNeonV2(int dim, float *ax, float *bx)
{
    /* 128-bit register = float32x4 */
    /* Round1 padding as float32x4x4, namely 16 float32 one iteration */
    float32x4_t r1 = vdupq_n_f32(0);
    float32x4_t r2 = vdupq_n_f32(0);
    float32x4_t r3 = vdupq_n_f32(0);
    float32x4_t r4 = vdupq_n_f32(0);
    int i = 0;
    float *pta = ax;
    float *ptb = bx;
    const int prefetchStride = 16; /* Prefetch 16 elements at a time */
    for (; i + prefetchStride <= dim; i += prefetchStride, pta += prefetchStride, ptb += prefetchStride) {
        float32x4_t packdata_a0 = vld1q_f32(pta);
        float32x4_t packdata_a1 = vld1q_f32(pta + 4);
        float32x4_t packdata_a2 = vld1q_f32(pta + 8);
        float32x4_t packdata_a3 = vld1q_f32(pta + 12);

        float32x4_t packdata_b0 = vld1q_f32(ptb);
        float32x4_t packdata_b1 = vld1q_f32(ptb + 4);
        float32x4_t packdata_b2 = vld1q_f32(ptb + 8);
        float32x4_t packdata_b3 = vld1q_f32(ptb + 12);

        float32x4_t diff0 = vsubq_f32(packdata_a0, packdata_b0);
        float32x4_t diff1 = vsubq_f32(packdata_a1, packdata_b1);
        float32x4_t diff2 = vsubq_f32(packdata_a2, packdata_b2);
        float32x4_t diff3 = vsubq_f32(packdata_a3, packdata_b3);

        r1 = vfmaq_f32(r1, diff0, diff0);
        r2 = vfmaq_f32(r2, diff1, diff1);
        r3 = vfmaq_f32(r3, diff2, diff2);
        r4 = vfmaq_f32(r4, diff3, diff3);
    }

    /* Round2 padding as float32, namely 4 float32 one iteration */
    for (; i + 4 <= dim; i += 4, pta += 4, ptb += 4) {
        float32x4_t data_a = vld1q_f32(pta);
        float32x4_t data_b = vld1q_f32(ptb);
        float32x4_t diff = vsubq_f32(data_a, data_b);
        r1 = vfmaq_f32(r1, diff, diff);
    }

    r1 = vaddq_f32(r1, r2);
    r2 = vaddq_f32(r3, r4);
    r1 = vaddq_f32(r1, r2);

    float distance = vaddvq_f32(r1);
    if ((dim & 0x3)) { /* Check if dim is a multiple of 4 */
        distance += L2SquaredDistanceRef(dim - i, ax + i, bx + i);
    }
    return distance;
}

/*
 * @brief Compute PQ (Product Quantization) table
 * @param samples Sample data
 * @param params PQ parameters
 * @return 0 on success, -1 on failure
 */
int ComputePQTable(VectorArray samples, PQParams *params)
{
    if (params == nullptr || params->pqTable == nullptr || samples == nullptr || samples->items == nullptr) {
        std::cerr << "Error: Null pointer in input parameters" << std::endl;
        return -1;
    }

    if (samples->length > samples->maxLen) {
        std::cerr << "Error: VectorArray lenth > VectorArray maxLen" << std::endl;
        return -1;
    }

    char *const pqTable = params->pqTable;
    const int pqKsub = params->pqKsub;
    const int pqM = params->pqM;
    const int dimS = samples->dim;
    const int dimPQ = params->dim;

    /* Validate dimension consistency */
    if (dimS != dimPQ) {
        std::cerr << "Error: Dimension mismatch - samples:" << dimS << " vs PQ:" << dimPQ << std::endl;
        return -1;
    }
    const int dim = dimPQ;
    int samplenum = samples->length;
    const int maxDim = 2000;   /* Maximum dimension value */
    const int maxPQksub = 256; /* Maximum PQ sub-center value */
    if (dim < 1 || dim > maxDim || pqM <= 0 || pqM > maxDim || pqM > dim || dim % pqM != 0) {
        std::cerr << "Error: Invalid pqM=" << pqM << " or dim=" << dim << " values" << std::endl;
        return -1;
    }
    if (pqKsub <= 0 || pqKsub > maxPQksub) {
        std::cerr << "Error: Invalid pqKsub=" << pqKsub << std::endl;
        return -1;
    }
    const size_t itemSize = MAXALIGN(VECTOR_SIZE(dim));
    if (itemSize != samples->itemSize) {
        std::cerr << "Error: Item size mismatch" << std::endl;
        return -1;
    }

    if (samplenum < 1 || static_cast<size_t>(samplenum) > (1ULL << 48) / itemSize) {
        std::cerr << "Error: Invalid samplenum=" << samplenum << std::endl;
        return -1;
    }

    const int dsub = dim / pqM; /* Total dimension / number of subspaces */
    const size_t subItemSize = MAXALIGN(VECTOR_SIZE(dsub));
    if (subItemSize != params->subItemSize) {
        std::cerr << "Error: Sub-item size mismatch" << std::endl;
        return -1;
    }

    /* Process each subspace */
    for (int m = 0; m < pqM; m++) {
        /* Split samples into subspace vectors */
        VectorArray subVectorArrays = VectorArraySplitSingle(samples, pqM, m);
        if (subVectorArrays == nullptr) {
            std::cerr << "Error: Failed to split vector array for subspace " << m << std::endl;
            return -1;
        }

        /* Initialize centers for this subspace */
        VectorArray centers = VectorArrayInit(pqKsub, dsub, subItemSize);
        if (centers == nullptr) {
            std::cerr << "Error: Failed to initialize centers for subspace " << m << std::endl;
            VectorArrayRelease(subVectorArrays);
            return -1;
        }

        /* Perform K-means clustering */
        if (NormalKmeans(subVectorArrays, centers, pqM) == -1) {
            std::cerr << "Error: K-means failed for subspace " << m << std::endl;
            VectorArrayRelease(centers);
            VectorArrayRelease(subVectorArrays);
            return -1;
        }

        /* Copy centers to PQ table with safety checks */
        for (int i = 0; i < pqKsub; i++) {
            char *vec = VectorArrayGet(centers, i);
            if (vec == nullptr) {
                std::cerr << "Error: Null vector at index " << i << " in subspace " << m << std::endl;
                VectorArrayRelease(centers);
                VectorArrayRelease(subVectorArrays);
                return -1;
            }

            /* Calculate target position in PQ table */
            size_t remainingSize = (pqKsub - i) * centers->itemSize;
            errno_t result = memcpy_s(pqTable + (m * pqKsub + i) * centers->itemSize,
                remainingSize,
                static_cast<void *>(vec),
                centers->itemSize);
            if (result != 0) {
                std::cerr << "Error: memcpy_s failed with pqTable and vec: " << result << std::endl;
                VectorArrayRelease(centers);
                VectorArrayRelease(subVectorArrays);
                return -1;
            }
        }

        /* Cleanup resources */
        VectorArrayRelease(centers);
        VectorArrayRelease(subVectorArrays);
    }

    return 0;
}

/*
 * @brief Compute PQ distance between base and query codes
 * @param basecode Base code
 * @param querycode Query code
 * @param params PQ parameters
 * @param pqDistanceTable Precomputed PQ distance table
 * @param pqDistance Pointer to store the computed distance
 * @param basecode_size Length of basecode
 * @param querycode_size Length of querycode
 * @param pqDistanceTable_size Length of pqDistanceTable
 * @param pqDistance_size Length of pqDistance
 * @return 0 on success, -1 on failure
 */
int GetPQDistance(const unsigned char *basecode, const unsigned char *querycode, const PQParams *params,
    const float *pqDistanceTable, float *pqDistance, size_t basecode_size, size_t querycode_size,
    size_t pqDistanceTable_size, size_t pqDistance_size)
{
    if (basecode == nullptr || params == nullptr || pqDistanceTable == nullptr || pqDistance == nullptr) {
        std::cerr << "Error: GetPQDistance input with nullptr" << std::endl;
        return -1;
    }
    int pqKsub = params->pqKsub;
    int pqM = params->pqM;
    int dim = params->dim;
    int maxDim = 2000;   /* Maximum dimension value */
    int maxPQksub = 256; /* Maximum PQ sub-center value */
    if (pqM <= 0 || dim % pqM != 0 || dim < pqM || dim < 1 || dim > maxDim || pqM > maxDim || pqKsub <= 0 ||
        pqKsub > maxPQksub || basecode_size < static_cast<size_t>(pqM) || pqDistance_size < 1) {
        std::cerr << "Error: invalid pq values" << std::endl
                  << "dim = " << dim << std::endl
                  << "pqM = " << pqM << std::endl
                  << "pqKsub = " << pqKsub << std::endl;
        return -1;
    }

    float distance = 0.0f;

    if (querycode == nullptr) {
        if (pqDistanceTable_size < static_cast<size_t>(pqM * pqKsub)) {
            std::cerr << "Error: invalid pqDistanceTable" << std::endl
                      << "pqDistanceTable_size = " << pqDistanceTable_size << std::endl;
            return -1;
        }
        size_t offset = 0;
        int k = 0;
        int num = pqM;
        while (num / 8 > 0) { /* Process 8 subspaces at a time */
            int i1 = basecode[k++];
            int i2 = basecode[k++];
            int i3 = basecode[k++];
            int i4 = basecode[k++];
            int i5 = basecode[k++];
            int i6 = basecode[k++];
            int i7 = basecode[k++];
            int i8 = basecode[k++];
            if (i1 >= pqKsub || i1 < 0 || i2 >= pqKsub || i2 < 0 || i3 >= pqKsub || i3 < 0 || i4 >= pqKsub || i4 < 0 ||
                i5 >= pqKsub || i5 < 0 || i6 >= pqKsub || i6 < 0 || i7 >= pqKsub || i7 < 0 || i8 >= pqKsub || i8 < 0) {
                std::cerr << "Error: invalid basecode values" << std::endl;
                return -1;
            }
            distance += pqDistanceTable[offset + i1];
            offset += pqKsub;
            distance += pqDistanceTable[offset + i2];
            offset += pqKsub;
            distance += pqDistanceTable[offset + i3];
            offset += pqKsub;
            distance += pqDistanceTable[offset + i4];
            offset += pqKsub;
            distance += pqDistanceTable[offset + i5];
            offset += pqKsub;
            distance += pqDistanceTable[offset + i6];
            offset += pqKsub;
            distance += pqDistanceTable[offset + i7];
            offset += pqKsub;
            distance += pqDistanceTable[offset + i8];
            offset += pqKsub;
            num -= 8; /* Process 8 subspaces at a time */
        }
        while (num > 0) {
            int i = basecode[k++];
            if (i >= pqKsub || i < 0) {
                std::cerr << "Error: invalid basecode values" << std::endl;
                return -1;
            }
            distance += pqDistanceTable[offset + i];
            offset += pqKsub;
            num -= 1;
        }
    } else {
        if (querycode_size < static_cast<size_t>(pqM) ||
            pqDistanceTable_size < static_cast<size_t>(pqM * pqKsub * pqKsub)) {
            std::cerr << "Error: invalid querycode or pqDistanceTable values" << std::endl;
			return -1;
        }
        size_t offset = 0;
        for (int k = 0; k < pqM; k++) {
            int i = basecode[k];
            int j = querycode[k];
            if (i >= pqKsub || i < 0 || j >= pqKsub || j < 0) {
                std::cerr << "Error: invalid basecode or querycode values" << std::endl;
                return -1;
            }
            offset = k * pqKsub * pqKsub + i * pqKsub + j;
            distance += pqDistanceTable[offset];
        }
    }
    *pqDistance = distance;
    return 0;
}

/*
 * @brief Compute PQ (Product Quantization) code for a vector
 * @param vector Input vector
 * @param params PQ parameters
 * @param pqCode Pointer to store the PQ code
 * @param pqCode_size Length of pqCode
 * @return 0 on success, -1 on failure
 */
int ComputeVectorPQCode(float *vector, const PQParams *params, unsigned char *pqCode, size_t pqCode_size)
{
    if (vector == nullptr || params == nullptr || pqCode == nullptr || params->pqTable == nullptr) {
        std::cerr << "Error: ComputeVectorPQCode input with nullptr" << std::endl;
        return -1;
    }
    char *pqTable = params->pqTable;

    int pqM = params->pqM;
    int dim = params->dim;
    int pqKsub = params->pqKsub;
    int maxDim = 2000;   /* Maximum dimension value */
    int maxPQksub = 256; /* Maximum PQ sub-center value */
    if (pqM <= 0 || dim % pqM != 0 || dim < pqM || dim < 1 || dim > maxDim || pqM > maxDim || pqKsub <= 0 ||
        pqKsub > maxPQksub || pqCode_size < static_cast<size_t>(pqM)) {
        std::cerr << "invalid pq values" << std::endl
                  << "dim = " << dim << std::endl
                  << "pqM = " << pqM << std::endl
                  << "pqKsub = " << pqKsub << std::endl
                  << "pqCode_size = " << pqCode_size << std::endl;
        return -1;
    }
    int dsub = dim / pqM;
    size_t subItemSize = MAXALIGN(VECTOR_SIZE(dsub));
    if (subItemSize != params->subItemSize) {
        std::cerr << "Error: invalid subItemSize" << std::endl;
        return -1;
    }
    int step = subItemSize / sizeof(float);

    for (int i = 0; i < pqM; i++) {
        unsigned char minIndex = -1;
        Vector *tempVec2 = reinterpret_cast<Vector *>(pqTable + (i * pqKsub) * subItemSize);
        if (tempVec2 == nullptr) {
            std::cerr << "Error: VectorArrayGet returned tempVec2 is nullptr" << std::endl;
            return -1;
        }
        minIndex = VectorL2SquaredDistancePQ(step, vector + i * dsub, tempVec2->x, pqKsub, dsub);
        pqCode[i] = minIndex;
    }
    return 0;
}

/*
 * @brief Compute distance between two sub-vectors
 * @param params PQ parameters
 * @param pqDistanceTable Precomputed PQ distance table
 * @param i Index of the first sub-vector
 * @param k Subspace index
 */
int ComputeOne(const PQParams *params, float *pqDistanceTable, int i, int k)
{
    int pqM = params->pqM;
    int pqKsub = params->pqKsub;
    int dim = params->dim;
    char *pqTable = params->pqTable;
    int funcType = params->funcType;
    int dsub = dim / pqM;
    size_t subItemSize = params->subItemSize;

    Vector *vec1 = reinterpret_cast<Vector *>(pqTable + (k * pqKsub + i) * subItemSize);
    if (vec1 == nullptr) {
        std::cerr << "Error: VectorArrayGet returned vec1 is nullptr" << std::endl;
        return -1;
    }
    for (int j = i; j < pqKsub; j++) {
        Vector *vec2 = reinterpret_cast<Vector *>(pqTable + (k * pqKsub + j) * subItemSize);
        if (vec2 == nullptr) {
            std::cerr << "Error: VectorArrayGet returned vec2 is nullptr" << std::endl;
            return -1;
        }
        /* funcType: 1/2/3 */
        if (funcType == 1 || funcType == 3) {
            float pqDis = L2SquaredDistanceNeonV2(dsub, vec1->x, vec2->x);
            size_t offset = k * pqKsub * pqKsub + i * pqKsub + j;
            pqDistanceTable[offset] = pqDis;
            if (i != j) {
                size_t offsetSymmetry = k * pqKsub * pqKsub + j * pqKsub + i;
                pqDistanceTable[offsetSymmetry] = pqDis;
            }
        } else {
            float pqDis = 0.0f;
            float *temp1 = vec1->x;
            float *temp2 = vec2->x;
            for (int d = 0; d < dsub; d++) {
                pqDis -= temp1[d] * temp2[d];
            }
            size_t offset = k * pqKsub * pqKsub + i * pqKsub + j;
            pqDistanceTable[offset] = pqDis;
            if (i != j) {
                size_t offsetSymmetry = k * pqKsub * pqKsub + j * pqKsub + i;
                pqDistanceTable[offsetSymmetry] = pqDis;
            }
        }
    }
    return 0;
}

/*
 * @brief Compute PQ distance table for all subspaces
 * @param params PQ parameters
 * @param pqDistanceTable Precomputed PQ distance table
 * @param pqDistanceTable_size Length of pqDistanceTable
 * @return 0 on success, -1 on failure
 */
int GetPQDistanceTableSdc(const PQParams *params, float *pqDistanceTable, size_t pqDistanceTable_size)
{
    if (params == nullptr || pqDistanceTable == nullptr || params->pqTable == nullptr) {
        std::cerr << "Error: GetPQDistanceTableSdc input with nullptr" << std::endl;
        return -1;
    }
    int pqM = params->pqM;
    int pqKsub = params->pqKsub;
    int dim = params->dim;
    int funcType = params->funcType;
    /* funcType: 1/2/3 */
    int maxDim = 2000;   /* Maximum dimension value */
    int maxPQksub = 256; /* Maximum PQ sub-center value */
    if (pqM <= 0 || dim % pqM != 0 || dim < pqM || dim < 1 || dim > maxDim || pqM > maxDim || pqKsub <= 0 ||
        pqKsub > maxPQksub || funcType < 1 || funcType > 3 ||
        pqDistanceTable_size < static_cast<size_t>(pqM * pqKsub * pqKsub)) {
        std::cerr << "Error: invalid pq values" << std::endl
                  << "dim = " << dim << std::endl
                  << "pqM = " << pqM << std::endl
                  << "pqKsub = " << pqKsub << std::endl
                  << "funcType = " << funcType << std::endl
                  << "pqDistanceTable_size = " << pqDistanceTable_size << std::endl;
        return -1;
    }

    int dsub = dim / pqM;
    size_t subItemSize = MAXALIGN(VECTOR_SIZE(dsub));
    if (subItemSize != params->subItemSize) {
        std::cerr << "Error: invalid subItemSize" << std::endl;
        return -1;
    }

    std::atomic<bool> errCondition(false);
#pragma omp parallel for collapse(2)
    for (int k = 0; k < pqM; k++) {
        for (int i = 0; i < pqKsub; i++) {
            if (errCondition.load()) {
                continue;
            }
            if (ComputeOne(params, pqDistanceTable, i, k) != 0) {
                errCondition.store(true);
            }
        }
    }

    return errCondition.load() ? -1 : 0;
}

/*
 * @brief Compute adaptive PQ distance table
 * @param vector Input vector
 * @param params PQ parameters
 * @param pqDistanceTable Precomputed PQ distance table
 * @param pqDistanceTable_size Length of pqDistanceTable
 * @return 0 on success, -1 on failure
 */
int GetPQDistanceTableAdc(float *vector, const PQParams *params, float *pqDistanceTable, size_t pqDistanceTable_size)
{
    if (vector == nullptr || params == nullptr || pqDistanceTable == nullptr || params->pqTable == nullptr) {
        std::cerr << "Error: GetPQDistanceTableAdc input with nullptr" << std::endl;
        return -1;
    }
    char *pqTable = params->pqTable;

    int dim = params->dim;
    int pqM = params->pqM;
    int pqKsub = params->pqKsub;
    int maxDim = 2000;   /* Maximum dimension value */
    int maxPQksub = 256; /* Maximum PQ sub-center value */
    if (pqM <= 0 || dim % pqM != 0 || dim < pqM || dim < 1 || dim > maxDim || pqM > maxDim || pqKsub <= 0 ||
        pqKsub > maxPQksub || pqDistanceTable_size < static_cast<size_t>(pqM * pqKsub * pqKsub)) {
        std::cerr << "invalid pq values" << std::endl
                  << "dim = " << dim << std::endl
                  << "pqM = " << pqM << std::endl
                  << "pqKsub = " << pqKsub << std::endl
                  << "pqDistanceTable_size = " << pqDistanceTable_size << std::endl;
        return -1;
    }
    int dsub = dim / pqM;
    size_t subItemSize = MAXALIGN(VECTOR_SIZE(dsub));
    if (subItemSize != params->subItemSize) {
        std::cerr << "Error: invalid subItemSize" << std::endl;
        return -1;
    }

    int funcType = params->funcType;
    /* funcType: 1/2/3 */
    if (funcType < 1 || funcType > 3) {
        std::cerr << "Error: invalid funcType : " << funcType << std::endl;
        return -1;
    }
    int step = subItemSize / sizeof(float);

    for (int i = 0; i < pqM; i++) {
        Vector *tmpvec = reinterpret_cast<Vector *>(pqTable + (i * pqKsub) * subItemSize);
        if (tmpvec == nullptr) {
            std::cerr << "Error: VectorArrayGet returned tmpvec is nullptr" << std::endl;
            return -1;
        }
        float *a = vector + i * dsub;
        float *c = tmpvec->x;
        int k = 0;
        for (; k < pqKsub; k++) {
            float *b = c + k * step;
            if (funcType == 1 || funcType == 3) {
                float l2Disatance = 0.0;
                for (int j = 0; j < dsub; j++) {
                    float diff = a[j] - b[j];
                    l2Disatance += diff * diff;
                }
                size_t l2Offset = i * pqKsub + k;
                pqDistanceTable[l2Offset] = l2Disatance;
            } else {
                float ipDisatance = 0.0;
                for (int j = 0; j < dsub; j++) {
                    ipDisatance -= a[j] * b[j];
                }
                size_t ipOffset = i * pqKsub + k;
                pqDistanceTable[ipOffset] = ipDisatance;
            }
        }
    }
    return 0;
}
}  // namespace PQHead