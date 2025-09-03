#include <gtest/gtest.h>
#include "kvecturbo.h"
#include <cmath>
#include <vector>
#include <memory>
#include <cstring>

/*
 * @brief Typedef for unsigned char with 8 bits
 */
typedef unsigned char uint8;

using namespace PQHead;

/*
 * @brief Union for variable attribute data structures
 */
typedef union {
    struct { /* Normal varlena (4-byte length) */
        unsigned int vaHeader;
        char vaData[FLEXIBLE_ARRAY_MEMBER];
    } va4byte;
    struct { /* Compressed-in-line format */
        unsigned int vaHeader;
        unsigned int vaRawsize;             /* Original data size (excludes header) */
        char vaData[FLEXIBLE_ARRAY_MEMBER]; /* Compressed data */
    } vaCompressed;
} Varattrib4b;

/*
 * @brief Structure for variable attribute with 1-byte header
 */
typedef struct {
    unsigned char vaHeader;
    char vaData[FLEXIBLE_ARRAY_MEMBER]; /* Data begins here */
} Varattrib1b;

/*
 * @brief Calculate the aligned size based on the given alignment value
 * @param alignVal The alignment value
 * @param len The length to align
 * @return Aligned size
 */
uintptr_t TYPEALIGN(size_t alignVal, size_t len)
{
    return (len + (alignVal - 1)) & ~(alignVal - 1);
}

/*
 * @brief Calculate the maximum aligned size
 * @param len The length to align
 * @return Maximum aligned size
 */
uintptr_t MAXALIGN(size_t len)
{
    return TYPEALIGN(MAXIMUM_ALIGNOF, len);
}

/*
 * @brief Initialize a VectorArray structure
 * @param maxLen Maximum length of the array
 * @param dimensions Number of dimensions
 * @param itemSize Size of each item
 * @return Pointer to the initialized VectorArray or nullptr on failure
 */
VectorArray VectorArrayInit(int maxLen, int dimensions, size_t itemSize)
{
    VectorArray res = static_cast<VectorArray>(malloc(sizeof(VectorArrayData)));
    if (res == nullptr) {
        std::cerr << "VectorArrayInit failed and returned nullptr\n";
        return nullptr;
    }

    /* Ensure items are aligned to prevent UB */
    itemSize = MAXALIGN(itemSize);

    res->length = 0;
    res->maxLen = maxLen;
    res->dim = dimensions;
    res->itemSize = itemSize;
    res->items = static_cast<char*>(malloc(maxLen * itemSize));
    /* Check for null pointer */
    if (res->items == nullptr) {
        free(res);
        std::cerr << "VectorArrayInit items failed and returned nullptr\n";
        return nullptr;
    }
    return res;
}

/*
 * @brief Calculate the size of a vector based on its dimensions
 * @param dim Number of dimensions
 * @return Size of the vector
 */
size_t VECTOR_SIZE(int dim)
{
    return offsetof(Vector, x) + sizeof(float) * dim;
}

/*
 * @brief Initialize a Vector structure
 * @param dim Number of dimensions
 * @return Pointer to the initialized Vector or nullptr on failure
 */
Vector *InitVector(int dim)
{
    Vector *result;
    int size;

    size = VECTOR_SIZE(dim);

    result = static_cast<Vector*>(calloc(size, sizeof(Vector)));
    /* Check for null pointer */
    if (result == nullptr) {
        std::cerr << "InitVector failed and returned nullptr" << std::endl;
        return nullptr;
    }

#ifdef WORDS_BIGENDIAN
    ((Varattrib4b *)(result))->va4byte.vaHeader = size & 0x3FFFFFFF;
#else
    /* Little-endian mode: shift left by 2 */
    ((Varattrib4b *)(result))->va4byte.vaHeader = size << 2;
#endif

    result->dim = dim;

    return result;
}

/*
 * @brief Test function for PQ parameters
 */
TEST(PQTest, ParamsTest) {
    /* Test different parameter scenarios for ComputePQTable */
    int dim = 99;
    int samplenum = 10000;
    int pqM = 1;
    int pqKsub = 256;

    VectorArray fakearray = VectorArrayInit(samplenum, dim, VECTOR_SIZE(dim));
    fakearray->length = samplenum;
    fakearray->dim = dim;
    fakearray->itemSize = MAXALIGN(VECTOR_SIZE(dim));
    size_t itemSize = MAXALIGN(VECTOR_SIZE(dim / pqM));
    char *pqTable = static_cast<char *>(malloc(pqM * pqKsub * itemSize));
    PQParams params = {
            pqM,
            pqKsub,
            1,
            dim,
            itemSize,
            pqTable
    };
    PQParams params_null = {
            pqM,
            pqKsub,
            1,
            dim,
            VECTOR_SIZE(dim / pqM),
            nullptr
    };
    PQParams params_dim = {
            pqM,
            pqKsub,
            1,
            80,
            VECTOR_SIZE(dim / pqM),
            pqTable
    };

    EXPECT_EQ(ComputePQTable(fakearray, &params), 0);
    EXPECT_EQ(ComputePQTable(fakearray, &params_null), -1);
    EXPECT_EQ(ComputePQTable(fakearray, &params_dim), -1);

    PQParams params1 = {
        -1,
        pqKsub,
        1,
        dim,
        VECTOR_SIZE(dim / pqM),
        pqTable
    };

    EXPECT_EQ(ComputePQTable(fakearray, &params1), -1);

    PQParams params2 = {
        pqM,
        -1,
        1,
        dim,
        VECTOR_SIZE(dim / pqM),
        pqTable
    };

    EXPECT_EQ(ComputePQTable(fakearray, &params2), -1);

    PQParams params3 = {
        pqM,
        pqKsub,
        1,
        -1,
        VECTOR_SIZE(dim / pqM),
        pqTable
    };
    EXPECT_EQ(ComputePQTable(fakearray, &params3), -1);

    fakearray->itemSize = 1;
    EXPECT_EQ(ComputePQTable(fakearray, &params), -1);
}

/*
 * @brief Test function for GetPQDistance with L2 distance and SDC mode
 */
TEST(GetPQDistance_testl2_Sdc, l2_Sdc){
    /* Test GetPQDistance with L2 distance and SDC mode */
    uint8 base[4] = {0,1,2,3};
    uint8 query[4] = {3,2,1,0};
    int dim = 16;
    int pqM = 4;
    int funcType = 1;
    int pqMode = 1;
    int pqKsub = 4;
    float PQDistance = 0;
    float pqDistanceTable[64] = {5,8,7,9,6,3,2,1,5,4,7,8,9,6,2,1,5,8,7,9,6,3,2,1,5,4,7,8,9,6,2,1,5,8,7,9,6,3,2,1,5,4,7,8,9,6,2,1,5,8,7,9,6,3,2,1,5,4,7,8,9,6,2,1};
    PQParams params = {
            pqM,
            pqKsub,
            funcType,
            dim,
            VECTOR_SIZE(dim / pqM),
            NULL
    };
    float res = 24;
    uint8 base2[4] = {9,11,21,35};
    uint8 query2[4] = {31,21,11,10};
    EXPECT_EQ(GetPQDistance(base, query, &params, pqDistanceTable, &PQDistance), 0);
    EXPECT_EQ(GetPQDistance(base2, query2, &params, pqDistanceTable, &PQDistance), -1);
    EXPECT_EQ(PQDistance, res);
    EXPECT_EQ(GetPQDistance(NULL, query, &params, pqDistanceTable, &PQDistance), -1);
}

/*
 * @brief Test function for GetPQDistance with L2 distance and ADC mode
 */
TEST(GetPQDistance_testl2_adc, l2_adc){
    /* Test GetPQDistance with L2 distance and ADC mode */
    uint8 base[4] = {0,1,2,3};
    int dim = 16;
    int pqM = 4;
    int funcType = 1;
    int pqMode = 1;
    int pqKsub = 4;
    float PQDistance = 0;
    float pqDistanceTable[16] = {5,8,7,9,6,3,2,1,5,4,7,8,9,6,2,1};
    PQParams params = {
            pqM,
            pqKsub,
            funcType,
            dim,
            VECTOR_SIZE(dim / pqM),
            NULL
    };
    float res = 16;

    EXPECT_EQ(GetPQDistance(base, nullptr, &params, pqDistanceTable, &PQDistance), 0);
    EXPECT_EQ(PQDistance, res);
    EXPECT_EQ(GetPQDistance(base, nullptr, NULL, pqDistanceTable, &PQDistance), -1);

    float PQDistance20 = 0;
    uint8 base20[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    float pqDistanceTable20[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    PQParams params20 = {
            20,
            1,
            funcType,
            20,
            VECTOR_SIZE(dim / pqM),
            NULL
    };
    EXPECT_EQ(GetPQDistance(base20, nullptr, &params20, pqDistanceTable20, &PQDistance20), -1);

    float PQDistance10 = 0;
    uint8 base10[10] = {0,0,0,0,0,0,0,0,0,0};
    float pqDistanceTable10[10] = {0,1,2,3,0,1,2,3,0,1};
    uint8 base4[4] = {5,9,8,7};
    float pqDistanceTable4[4] = {0,1,2,3};
    PQParams params10 = {
            10,
            1,
            funcType,
            10,
            VECTOR_SIZE(dim / pqM),
            NULL
    };
    PQParams params4 = {
            4,
            1,
            funcType,
            4,
            VECTOR_SIZE(dim / pqM),
            NULL
    };
    PQParams params10_1 = {
            -1,
            1,
            funcType,
            10,
            VECTOR_SIZE(dim / pqM),
            NULL
    };
    EXPECT_EQ(GetPQDistance(base10, nullptr, &params10, pqDistanceTable10, &PQDistance10), 0);
    EXPECT_EQ(GetPQDistance(base4, nullptr, &params4, pqDistanceTable4, &PQDistance10), -1);
    EXPECT_EQ(GetPQDistance(base10, nullptr, &params10_1, pqDistanceTable10, &PQDistance10), -1);
}

/*
 * @brief Test function for ComputeVectorPQCode
 */
TEST(ComputeVectorPQCode_Test, ComputeVectorPQCode){
    /* Test ComputeVectorPQCode with various scenarios */
    float vector[4] = {1,2,3,4};
    int dim = 4;
    int pqM = 4;
    size_t subItemSize = MAXALIGN(VECTOR_SIZE(dim/pqM));
    int pqKsub = 4;
    int funcType = 1;
    int pqMode = 1;
    Vector *vectors[16];
    for(int i = 0; i < 16; i++){
        vectors[i] = InitVector(1);
        vectors[i]->x[0] = i;
    }
    size_t total_size = 16 * subItemSize;
    char *pqTable = (char*)malloc(total_size);
    uint8 *pqCode = (uint8*)malloc(4 * sizeof(uint8));
    for(int i = 0; i < 16; i++){
        memcpy(pqTable + i * subItemSize, vectors[i], subItemSize);
    }
    PQParams params = {
            pqM,
            pqKsub,
            funcType,
            dim,
            subItemSize,
            pqTable
    };
    PQParams params2 = {
            -1,
            pqKsub,
            funcType,
            dim,
            subItemSize,
            pqTable
    };
    PQParams params_null = {
            pqM,
            pqKsub,
            funcType,
            dim,
            subItemSize,
            nullptr
    };
    uint8 res[4] = {1,0,0,0};
    EXPECT_EQ(ComputeVectorPQCode(vector, &params, pqCode), 0);
    EXPECT_EQ(ComputeVectorPQCode(vector, &params2, pqCode), -1);
    for(int i = 0 ; i < 4; i++){
        EXPECT_EQ(res[i],pqCode[i]);
    }
    EXPECT_EQ(ComputeVectorPQCode(NULL, &params, pqCode), -1);
    EXPECT_EQ(ComputeVectorPQCode(vector, NULL, pqCode), -1);
    EXPECT_EQ(ComputeVectorPQCode(vector, &params, NULL), -1);
    EXPECT_EQ(ComputeVectorPQCode(vector, &params_null, pqCode), -1);

    PQParams params_size = {
            pqM,
            pqKsub,
            funcType,
            dim,
            0,
            pqTable
    };
    EXPECT_EQ(ComputeVectorPQCode(vector, &params_size, pqCode), -1);

    free(pqTable);
    free(pqCode);
    for (int i = 0; i < 16; i++) {
        free(vectors[i]);
    }

}

/*
 * @brief Test function for GetPQDistanceTable with SDC and ADC modes
 */
TEST(GetPQDistanceTable_test, sdc_adc){
    /* Test GetPQDistanceTable with SDC and ADC modes */
    int pqM = 4;
    int dim = 4;
    size_t subItemSize = MAXALIGN(VECTOR_SIZE(dim / pqM));
    int pqKsub = 4;
    int funcType = 1;
    int pqMode = 1;
    Vector *vectors[16];
    for(int i = 0; i < 16; i++){
        vectors[i] = InitVector(1);
        vectors[i]->x[0] = (float)i;
    }
    float vector[4] = {0,1,2,3};
    size_t total_size = 16 * subItemSize;
    char *pqTable = (char*)malloc(total_size);
    for(int i = 0; i < 16; i++){
        memcpy(pqTable + i * subItemSize, vectors[i], subItemSize);
    }
    float *pqDistanceTable1 = (float*)malloc(4*4*4*sizeof(float));
    PQParams params1 = {
            pqM,
            pqKsub,
            1,
            dim,
            subItemSize,
            pqTable
    };
    PQParams params_size = {
            pqM,
            pqKsub,
            1,
            dim,
            0,
            pqTable
    };
    float res1[64] = {0,1,4,9,1,0,1,4,4,1,0,1,9,4,1,0,0,1,4,9,1,0,1,4,4,1,0,1,9,4,1,0,0,1,4,9,1,0,1,4,4,1,0,1,9,4,1,0,0,1,4,9,1,0,1,4,4,1,0,1,9,4,1,0};
    EXPECT_EQ(GetPQDistanceTableSdc(&params1, pqDistanceTable1), 0);
    EXPECT_EQ(GetPQDistanceTableSdc(&params_size, pqDistanceTable1), -1);
    for(int i = 0; i < 64; i++){
        EXPECT_EQ(res1[i], pqDistanceTable1[i]);
    }
    free(pqDistanceTable1);

    Vector *vectors20 = InitVector(20);
    size_t subItemSize20 = VECTOR_SIZE(20);
    size_t total_size20 = 1 * subItemSize20;
    char *pqTable20 = (char*)malloc(total_size20);
    for(int i = 0; i < 16; i++){
        vectors20->x[i] = i;
    }
    memcpy(pqTable20, vectors20, subItemSize20);
    float *pqDistanceTable20 = (float*)malloc(1*1*1*sizeof(float));
    PQParams params20 = {
            1,
            1,
            1,
            20,
            subItemSize20,
            pqTable20
    };
    EXPECT_EQ(GetPQDistanceTableSdc(&params20, pqDistanceTable20), 0);
    free(pqDistanceTable20);
    free(vectors20);
    free(pqTable20);

    float *qDis1 = (float*)malloc(4*4*sizeof(float));
    float *qDisSize = (float*)malloc(4*4*sizeof(float));
    float res2[16] = {0,1,4,9,9,16,25,36,36,49,64,81,81,100,121,144};
    EXPECT_EQ(GetPQDistanceTableAdc(vector, &params1, qDis1), 0);
    EXPECT_EQ(GetPQDistanceTableAdc(vector, &params_size, qDisSize), -1);
    for(int i = 0; i < 16; i++){
        EXPECT_EQ(res2[i], qDis1[i]);
    }
    free(qDis1);

    float *pqDistanceTable2 = (float*)malloc(4*4*4*sizeof(float));
    PQParams params2 = {
            pqM,
            pqKsub,
            2,
            dim,
            subItemSize,
            pqTable
    };
    float res3[64] = {0,0,0,0,0,-1,-2,-3,0,-2,-4,-6,0,-3,-6,-9,
                      -16,-20,-24,-28,-20,-25,-30,-35,-24,-30,-36,-42,-28,-35,-42,-49,
                      -64,-72,-80,-88,-72,-81,-90,-99,-80,-90,-100,-110,-88,-99,-110,-121,
                      -144,-156,-168,-180,-156,-169,-182,-195,-168,-182,-196,-210,-180,-195,-210,-225};
    EXPECT_EQ(GetPQDistanceTableSdc(&params2, pqDistanceTable2), 0);
    for(int i = 0; i < 64; i++){
        EXPECT_EQ(res3[i], pqDistanceTable2[i]);
    }
    free(pqDistanceTable2);

    float *qDis2 = (float*)malloc(4*4*sizeof(float));
    float res4[16] = {0,0,0,0,-4,-5,-6,-7,-16,-18,-20,-22,-36,-39,-42,-45};
    EXPECT_EQ(GetPQDistanceTableAdc(vector, &params2, qDis2), 0);
    for(int i = 0; i < 16; i++){
        EXPECT_EQ(res4[i], qDis2[i]);
    }
    free(qDis2);

    float *pqDistanceTable3 = (float*)malloc(4*4*4*sizeof(float));
    float *qDis3 = (float*)malloc(4*4*sizeof(float));
    PQParams params3 = {
            pqM,
            pqKsub,
            2,
            dim,
            subItemSize,
            nullptr
    };

    EXPECT_EQ(GetPQDistanceTableSdc(nullptr, nullptr), -1);
    EXPECT_EQ(GetPQDistanceTableSdc(&params3, pqDistanceTable3), -1);
    EXPECT_EQ(GetPQDistanceTableAdc(nullptr, nullptr, nullptr), -1);
    EXPECT_EQ(GetPQDistanceTableAdc(vector, &params3, qDis3), -1);

    PQParams params4 = {
            -1,
            pqKsub,
            2,
            dim,
            subItemSize,
            pqTable
    };
    PQParams params5 = {
            pqM,
            pqKsub,
            4,
            dim,
            subItemSize,
            pqTable
    };
    EXPECT_EQ(GetPQDistanceTableSdc(&params4, pqDistanceTable3), -1);
    EXPECT_EQ(GetPQDistanceTableAdc(vector, &params4, qDis3), -1);
    EXPECT_EQ(GetPQDistanceTableAdc(vector, &params5, qDis3), -1);

    free(pqDistanceTable3);
    free(qDis3);
    free(pqTable);
    for (int i = 0; i < 16; i++) {
        free(vectors[i]);
    }
}