/*
 * Copyright (c) 2024 Huawei Technologies Co., Ltd.
 * kvecturbo is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the Mulan PSL v2 for more details.
 */

#ifndef KVECTURBO_H
#define KVECTURBO_H

#include <cfloat>
#include <cstddef>
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
    signed int vlen;                /* Number of dimensions, same as dim */
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
    size_t subItemSize; /* Size of one sub-vector, aligned up; see the API reference for the formula */
    char *pqTable;      /* Codebook for PQ, caller-allocated, size >= pqM * pqKsub * subItemSize */
} PQParams;

/*
 * @brief Compute PQ code for a given vector
 * @param vector Input vector to be quantized; every component must be finite and its absolute value must not
 *               exceed 1.0e17, otherwise -1 is returned
 * @param params PQ algorithm parameters
 * @param pqCode Output PQ code
 * @param pqCode_size Length of pqCode
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int ComputeVectorPQCode(float *vector, const PQParams *params, unsigned char *pqCode,
                                        size_t pqCode_size);

/*
 * @brief Compute PQ codebook from training samples
 * @param samples Training samples for codebook generation; every component of every sample must be finite and
 *                its absolute value must not exceed 1.0e17, otherwise -1 is returned
 * @param params PQ algorithm parameters; params->pqTable must point to a caller-allocated buffer of at least
 *               pqM * pqKsub * params->subItemSize bytes, the codebook is written into that buffer
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int ComputePQTable(VectorArray samples, PQParams *params);

/*
 * @brief Validate a PQ codebook before it is used for queries
 * @param params PQ algorithm parameters; params->pqTable points to the codebook to be validated. Centroids
 *               with non-finite components or components whose absolute value exceeds 1.0e17 are invalid
 * @param pqTableSize Length of the codebook buffer in bytes
 * @return int Error code, 0 for a valid codebook, -1 otherwise
 */
KVEC_API_PUBLIC int ValidatePQTable(const PQParams *params, size_t pqTableSize);

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
 * @param vector Query vector; every component must be finite and its absolute value must not exceed 1.0e17,
 *               otherwise -1 is returned
 * @param params PQ algorithm parameters
 * @param pqDistanceTable Output distance table
 * @param pqDistanceTable_size Length of pqDistanceTable, at least pqM * pqKsub
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int GetPQDistanceTableAdc(float *vector, const PQParams *params, float *pqDistanceTable,
                                          size_t pqDistanceTable_size);

/*
 * @brief Calculate PQ distance between two codes
 * @param basecode Base PQ code
 * @param querycode Query PQ code
 * @param params PQ algorithm parameters
 * @param pqDistanceTable Precomputed distance table; needs pqM * pqKsub entries for the ADC path
 *                         (querycode == nullptr) and pqM * pqKsub * pqKsub entries for the SDC path
 * @param pqDistance Output distance result
 * @param basecode_size Length of basecode
 * @param querycode_size Length of querycode
 * @param pqDistanceTable_size Length of pqDistanceTable
 * @param pqDistance_size Length of pqDistance
 * @return int Error code, 0 for success
 */
KVEC_API_PUBLIC int GetPQDistance(const unsigned char *basecode, const unsigned char *querycode, const PQParams *params,
                                  const float *pqDistanceTable, float *pqDistance, size_t basecode_size,
                                  size_t querycode_size, size_t pqDistanceTable_size, size_t pqDistance_size);

} // namespace PQHead

#ifdef __cplusplus
}
#endif

#endif // KVECTURBO_H