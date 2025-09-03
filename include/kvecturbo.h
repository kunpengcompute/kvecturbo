/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2024-2024. All rights reserved.
 * Description: PQ Quantization and Search
 */

#ifndef KVECTURBO_H
#define KVECTURBO_H

#include <cstddef>
#include <cfloat>
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

#define FLEXIBLE_ARRAY_MEMBER
#define MAXIMUM_ALIGNOF 8
#define KVEC_API_PUBLIC __attribute__((visibility("default")))

namespace PQHead {

/*
 * @brief Data structure for storing vector arrays
 */
typedef struct VectorArrayData {
    int length;      /* Number of vectors in the array */
    int maxLen;      /* Maximum length of vectors */
    int dim;         /* Vector dimension */
    size_t itemSize; /* Size of a single vector */
    char *items;     /* Pointer to the first vector in the array */
} VectorArrayData;
typedef VectorArrayData *VectorArray;

/*
 * @brief Data structure for storing individual vectors
 */
typedef struct Vector {
    signed int vlen;                /* Length of the vector */
    signed short dim;               /* Vector dimension */
    signed short unused;            /* Reserved field for future use */
    float x[FLEXIBLE_ARRAY_MEMBER]; /* Vector data */
} Vector;

/*
 * @brief Parameters for PQ (Product Quantization) algorithm
 */
typedef struct PQParams {
    int pqM;            /* Number of PQ subspaces */
    int pqKsub;         /* Number of clusters per subspace */
    int funcType;       /* Distance calculation type */
    int dim;            /* Vector dimension */
    size_t subItemSize; /* Size of sub-vectors in PQ table */
    char *pqTable;      /* Codebook for PQ */
} PQParams;

/*
 * @brief Compute PQ code for a given vector
 * @param vector Input vector to be quantized
 * @param params PQ algorithm parameters
 * @param pqCode Output PQ code
 * @param pqCode_size Length of pqCode
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int ComputeVectorPQCode(
    float *vector, const PQParams *params, unsigned char *pqCode, size_t pqCode_size);

/*
 * @brief Compute PQ codebook from training samples
 * @param samples Training samples for codebook generation
 * @param params PQ algorithm parameters (will be updated with codebook)
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int ComputePQTable(VectorArray samples, PQParams *params);

/*
 * @brief Get distance table for PQ search (SDC mode)
 * @param params PQ algorithm parameters
 * @param pqDistanceTable Output distance table
 * @param pqDistanceTable_size Length of pqDistanceTable
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int GetPQDistanceTableSdc(const PQParams *params, float *pqDistanceTable, size_t pqDistanceTable_size);

/*
 * @brief Get distance table for PQ search (ADC mode)
 * @param vector Query vector
 * @param params PQ algorithm parameters
 * @param pqDistanceTable Output distance table
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int GetPQDistanceTableAdc(
    float *vector, const PQParams *params, float *pqDistanceTable, size_t pqDistanceTable_size);

/*
 * @brief Calculate PQ distance between two codes
 * @param basecode Base PQ code
 * @param querycode Query PQ code
 * @param params PQ algorithm parameters
 * @param pqDistanceTable Precomputed distance table
 * @param pqDistance Output distance result
 * @param basecode_size Length of basecode
 * @param querycode_size Length of querycode
 * @param pqDistanceTable_size Length of pqDistanceTable
 * @param pqDistance_size Length of pqDistance
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int GetPQDistance(const unsigned char *basecode, const unsigned char *querycode, const PQParams *params,
    const float *pqDistanceTable, float *pqDistance, size_t basecode_size, size_t querycode_size,
    size_t pqDistanceTable_size, size_t pqDistance_size);

}  // namespace PQHead

#ifdef __cplusplus
}
#endif

#endif  // KVECTURBO_H