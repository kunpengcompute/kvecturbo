# API参考

本文档提供KVecTurbo接口列表、结构体说明、以及ComputePQTable、ValidatePQTable、ComputeVectorPQCode、GetPQDistanceTableSdc、GetPQDistanceTableAdc、GetPQDistance六个接口的具体说明。

## 接口列表

KVecTurbo提供的接口如[**表 1** KVecTurbo提供的接口](#KVecTurbo提供的接口)所示。

**表 1** KVecTurbo提供的接口<a id="KVecTurbo提供的接口"></a>

<a name="table1194910128449"></a>

| 接口名称 | 接口作用 |
| --- | --- |
| ComputePQTable | 计算PQ码本。 |
| ValidatePQTable | 校验已加载的PQ码本是否可用。 |
| ComputeVectorPQCode | 根据PQ码本，量化输入向量。 |
| GetPQDistanceTableSdc | 计算PQ SDC距离表，即计算各个子空间内聚类中心之间的距离。 |
| GetPQDistanceTableAdc | 计算PQ ADC距离表，即计算查询向量和各个子空间内聚类中心的距离。 |
| GetPQDistance | 计算PQ ADC或SDC距离。若querycode == NULL，计算的是ADC距离；若querycode != NULL，计算的是SDC距离。 |

## 结构体说明

KVecTurbo提供的接口所使用参数涉及“VectorArray“和“PQParams“两类结构体，详细参数描述如**表 1** 结构体VectorArray字段描述和**表 2** 结构体PQParams字段描述所示。

**表 1** 结构体VectorArray字段描述<a id="结构体VectorArray字段描述"></a>

| 字段名称 | 描述 | 数据类型 | 取值范围 |
| --- | --- | --- | --- |
| maxLen | 向量最大个数。 | int | 若取值过大，可能因系统内存资源限制导致内存分配操作失败。 |
| length | 向量个数。 | int | [1,maxLen]，其中“maxLen”是结构体“VectorArray”中的字段，表示向量最大个数。 |
| dim | 向量维度。 | int | [1,2000] |
| itemSize | 单个向量长度。 | size_t | 限制非0。 |
| items | length个向量首地址。 | char* | 限制非空。 |

**表 2** 结构体PQParams字段描述<a id="tb2"></a>

| 字段名称 | 描述 | 数据类型 | 取值范围 |
| --- | --- | --- | --- |
| dim | 维度。 | int | [1,2000] |
| pqM | 子空间数。 | int | [1,dim]，其中“dim”是结构体“PQParams”中的字段，表示向量维度。 |
| pqKsub | 子空间内聚类中心数。 | int | [1,256] |
| funcType | 距离类型。 | int | [1,3]；1：表示L2类型；2：表示IP类型；3：表示Cosine类型。 |
| subItemSize | 码字大小，必须为对齐后的子向量大小：(8 + 4 * (dim / pqM)) 按 MAXIMUM_ALIGNOF 向上对齐。 | size_t | 必须精确等于 (8 + 4 * (dim / pqM)) 按 MAXIMUM_ALIGNOF 向上对齐后的值，否则接口返回 -1。 |
| pqTable | 码本。 | char* | 限制非空，容量至少为 pqM \* pqKsub \* subItemSize 字节。 |

## ComputePQTable

**接口定义<a name="section172317194488"></a>**

int ComputePQTable\(VectorArray samples, PQParams \*params\);

**接口用途<a name="section1153124784912"></a>**

计算PQ码本。

**参数说明<a name="section157501312135019"></a>**

| 参数名称 | 数据类型 | 描述 |
| --- | --- | --- |
| samples | VectorArray | 字段描述请参见[结构体说明](#结构体说明)中的“VectorArray”字段描述。每个样本的每个分量必须为有限值且绝对值不超过 1e17，否则接口返回 -1。 |
| params | PQParams | 字段描述请参见[结构体说明](#结构体说明)中的“PQParams”字段描述。其中，“pqTable”必须指向调用方预先分配的缓冲区，容量至少为 pqM \* pqKsub \* subItemSize 字节。 |

**返回值<a name="section49971832106"></a>**

<a name="table17997635100"></a>

| 数据类型 | 说明 |
| --- | --- |
| int | 正常运行时返回0，异常退出返回-1。 |

**注意事项**

- **缓冲区归属与容量责任**：`params->pqTable`指向由调用方分配并持有的缓冲区，本接口按`pqM × pqKsub × subItemSize`字节写入码本。接口不含容量参数，**不校验缓冲区实际容量**，容量正确性由调用方保证。
- **容量不足的后果**：若缓冲区小于所需容量，本接口不会返回-1（容量不在入口校验范围内），越界写入将造成堆内存破坏，通常表现为远离调用点的崩溃，无法通过返回值检测。
- **容量必须在调用前预先保证**：调用本接口之前，必须按下方公式为`params->pqTable`分配`pqM × pqKsub × subItemSize`字节，这是避免堆越界写入的唯一有效控制点。
- **自检建议（仅事后侦测）**：本接口返回0后，可用真实分配容量调用`ValidatePQTable(params, pqTableSize)`复核码本缓冲区容量与质心数值合法性；但它只能在越界写已经发生之后才发现容量不足，无法阻止堆破坏，不能替代预分配。

码本缓冲区的标准分配公式（使用`size_t`计算）：

```c
/* subItemSize：Vector 头（8 字节）+ dsub 个 float，按 MAXIMUM_ALIGNOF 向上对齐 */
params.subItemSize = (sizeof(Vector) + sizeof(float) * (dim / pqM)
                      + MAXIMUM_ALIGNOF - 1) & ~(size_t)(MAXIMUM_ALIGNOF - 1);
/* 码本缓冲区所需容量 */
size_t pqTableSize = (size_t)pqM * pqKsub * params.subItemSize;
```

其中`sizeof(Vector)`头部为8字节（`vlen`、`dim`、`unused`三个字段，`vlen`填向量维度、与`dim`相同），`MAXIMUM_ALIGNOF`为8。`pqKsub`大于训练样本数时，实际聚类数被钳制为样本数并对已有质心取模复用，写入总量不变。

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvecturbo.h"
using namespace PQHead;

int main() {
    // 参数配置
    int dim = 128;          // 向量维度
    int numSamples = 10000; // 训练样本数量
    int pqM = 8;            // 子空间数（dim需能被pqM整除）
    int pqKsub = 256;       // 每个子空间的聚类中心数
    int funcType = 1;       // L2距离

    // 准备训练样本：每个样本按 Vector 布局存放（8 字节头部 + dim 个 float）
    size_t sampleItemSize =
        (sizeof(Vector) + sizeof(float) * dim + MAXIMUM_ALIGNOF - 1) & ~(size_t)(MAXIMUM_ALIGNOF - 1);
    char* sampleData = (char*)calloc(numSamples, sampleItemSize);
    if (sampleData == NULL) {
        printf("内存分配失败\n");
        return -1;
    }
    // ... 填充sampleData训练数据 ...
    for (int i = 0; i < numSamples; i++) {
        Vector* sample = (Vector*)(sampleData + (size_t)i * sampleItemSize);
        sample->vlen = dim;
        sample->dim = (signed short)dim;
        for (int d = 0; d < dim; d++) {
            sample->x[d] = (float)rand() / RAND_MAX;  // 示例：随机填充
        }
    }

    // 初始化VectorArray结构体
    VectorArrayData samplesData;
    samplesData.maxLen = numSamples;
    samplesData.length = numSamples;
    samplesData.dim = dim;
    samplesData.itemSize = sampleItemSize;
    samplesData.items = sampleData;
    VectorArray samples = &samplesData;

    // 初始化PQParams结构体
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.funcType = funcType;
    params.subItemSize = (sizeof(Vector) + sizeof(float) * (dim / pqM) + MAXIMUM_ALIGNOF - 1) & ~(size_t)(MAXIMUM_ALIGNOF - 1);  // 头部+数据，按 MAXIMUM_ALIGNOF 对齐
    
    // 分配码本存储空间
    size_t pqTableSize = pqM * pqKsub * params.subItemSize;
    params.pqTable = (char*)malloc(pqTableSize);
    if (params.pqTable == NULL) {
        printf("码本内存分配失败\n");
        free(sampleData);
        return -1;
    }

    // 计算PQ码本
    int ret = ComputePQTable(samples, &params);

    if (ret != 0) {
        printf("计算PQ码本失败，错误码: %d\n", ret);
        free(sampleData);
        free(params.pqTable);
        return -1;
    }

    printf("成功计算PQ码本\n");
    printf("  - 子空间数: %d\n", pqM);
    printf("  - 每子空间聚类中心数: %d\n", pqKsub);

    // ... 使用params.pqTable进行后续量化操作 ...

    // 清理资源
    free(sampleData);
    free(params.pqTable);

    return 0;
}
```

## ValidatePQTable

**接口定义<a name="section_validate_pq_table"></a>**

int ValidatePQTable\(const PQParams \*params, size_t pqTableSize\);

**接口用途**

校验调用方加载的PQ码本是否可用。建议在载入持久化码本后调用一次，可拦截早期版本或异常训练数据产生的含NaN/Inf、超出取值范围的质心，避免后续查询静默返回错误结果。在 `ComputePQTable`返回0后调用可用于事后侦测码本缓冲区容量不足或质心数值非法，但此时越界写可能已经发生、无法预防；缓冲区容量必须在调用`ComputePQTable`之前按公式自行分配（详见其"注意事项"）。

**参数说明<a name="section_validate_pq_table_params"></a>**

<a name="table_validate_pq_table_params"></a>

| 参数名称 | 数据类型 | 描述 |
| --- | --- | --- |
| params | PQParams | PQ算法参数，其中pqTable指向待校验的码本缓冲区。字段描述请参见结构体说明中的“PQParams”字段描述。 |
| pqTableSize | size_t | 码本缓冲区长度（字节），至少为pqM \* pqKsub \* subItemSize。 |

**返回值<a name="section_validate_pq_table_return"></a>**

<a name="table_validate_pq_table_return"></a>

| 数据类型 | 说明 |
| --- | --- |
| int | 码本合法返回0；参数不合法、缓冲区容量不足或质心取值非法（NaN/Inf 或任一分量绝对值超过 1e17）时返回-1。 |

## ComputeVectorPQCode

**接口定义<a name="section172317194488"></a>**

int ComputeVectorPQCode\(float \*vector, const PQParams \*params, unsigned char \*pqCode, size\_t pqCode\_size\);

**接口用途<a name="section1153124784912"></a>**

根据PQ码本，量化输入向量。

**参数说明<a name="section157501312135019"></a>**

| 参数名称 | 数据类型 | 描述 | 取值范围 |
| --- | --- | --- | --- |
| vector | float * | 原始向量。 | 限制非空；每个分量必须为有限值且绝对值不超过 1e17，否则接口返回 -1。 |
| pqCode | unsigned char * | 量化后的向量。也可以作为输出值。 | 限制非空。长度为pqCode_size，其中“pqCode_size”为量化后向量数组的长度。 |
| pqCode_size | size_t | 量化后向量数组的长度。 | 限制为pqM，其中“pqM”是结构体“PQParams”中的字段，表示子空间数。 |
| params | const PQParams | 字段描述请参见[结构体说明](#结构体说明)中的“PQParams”字段描述。 | - |

**返回值<a name="section49971832106"></a>**

<a name="table17997635100"></a>

| 数据类型 | 说明 |
| --- | --- |
| int | 正常运行时返回0，异常退出返回-1。 |

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"
using namespace PQHead;

int main() {
    // 假设已通过ComputePQTable计算得到PQ码本
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // 初始化PQParams（假设pqTable已填充）
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.funcType = 1;  // L2距离
    params.subItemSize = (sizeof(Vector) + sizeof(float) * (dim / pqM) + MAXIMUM_ALIGNOF - 1) & ~(size_t)(MAXIMUM_ALIGNOF - 1);  // 头部+数据，按 MAXIMUM_ALIGNOF 对齐
    
    // 分配并填充码本（实际应用中应使用ComputePQTable的输出）
    size_t pqTableSize = pqM * pqKsub * params.subItemSize;
    params.pqTable = (char*)malloc(pqTableSize);
    // ... 假设pqTable已通过ComputePQTable填充 ...

    // 准备待量化的原始向量
    float* vector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        vector[i] = (float)rand() / RAND_MAX;  // 示例数据
    }

    // 分配量化后的PQ码存储空间
    size_t pqCodeSize = pqM;  // 每个子空间一个码字（uint8）
    unsigned char* pqCode = (unsigned char*)malloc(pqCodeSize);

    // 执行向量量化
    int ret = ComputeVectorPQCode(vector, &params, pqCode, pqCodeSize);

    if (ret != 0) {
        printf("向量量化失败，错误码: %d\n", ret);
        free(vector);
        free(pqCode);
        free(params.pqTable);
        return -1;
    }

    printf("向量量化成功\n");
    printf("PQ码: ");
    for (size_t i = 0; i < pqCodeSize; i++) {
        printf("%u ", pqCode[i]);
    }
    printf("\n");

    // 清理资源
    free(vector);
    free(pqCode);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistanceTableSdc

**接口定义<a name="section172317194488"></a>**

int GetPQDistanceTableSdc\(const PQParams \*params, float \*pqDistanceTable, size\_t pqDistanceTable\_size\);

**接口用途<a name="section1153124784912"></a>**

计算PQ SDC距离表，即计算各个子空间内聚类中心之间的距离。

**参数说明<a name="section157501312135019"></a>**

| 参数名称 | 数据类型 | 描述 | 取值范围 |
| --- | --- | --- | --- |
| pqDistanceTable | float* | SDC距离表。也可以作为输出值。 | 限制非空。长度为pqDistanceTable_size，其中“pqDistanceTable_size”为SDC距离表数组的长度。 |
| pqDistanceTable_size | size_t | SDC距离表数组的长度。 | 限制为pqM*pqKsub*pqKsub，其中“pqM”是结构体“PQParams”中的字段，表示子空间数，“pqKsub”是结构体“PQParams”中的字段，表示子空间内聚类中心数。 |
| params | const PQParams | 字段描述请参见[结构体说明](#结构体说明)中的“PQParams”字段描述。 | - |

**返回值<a name="section49971832106"></a>**

<a name="table17997635100"></a>

| 数据类型 | 说明 |
| --- | --- |
| int | 正常运行时返回0，异常退出返回-1。 |

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"
using namespace PQHead;

int main() {
    // 假设已通过ComputePQTable计算得到PQ码本
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // 初始化PQParams（假设pqTable已填充）
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.funcType = 1;  // L2距离
    params.subItemSize = (sizeof(Vector) + sizeof(float) * (dim / pqM) + MAXIMUM_ALIGNOF - 1) & ~(size_t)(MAXIMUM_ALIGNOF - 1);  // 头部+数据，按 MAXIMUM_ALIGNOF 对齐
    
    size_t pqTableSize = pqM * pqKsub * params.subItemSize;
    params.pqTable = (char*)malloc(pqTableSize);
    // ... 假设pqTable已通过ComputePQTable填充 ...

    // 计算SDC距离表大小并分配内存
    // SDC表存储每个子空间内所有聚类中心对之间的距离
    size_t sdcTableSize = pqM * pqKsub * pqKsub;
    float* sdcDistanceTable = (float*)malloc(sdcTableSize * sizeof(float));
    if (sdcDistanceTable == NULL) {
        printf("SDC距离表内存分配失败\n");
        free(params.pqTable);
        return -1;
    }

    // 计算SDC距离表
    int ret = GetPQDistanceTableSdc(&params, sdcDistanceTable, sdcTableSize);

    if (ret != 0) {
        printf("计算SDC距离表失败，错误码: %d\n", ret);
        free(sdcDistanceTable);
        free(params.pqTable);
        return -1;
    }

    printf("成功计算SDC距离表\n");
    printf("  - 距离表大小: %zu\n", sdcTableSize);
    printf("  - 第一个子空间中心0与中心1的距离: %f\n", sdcDistanceTable[1]);

    // ... 使用SDC距离表进行后续距离计算 ...

    // 清理资源
    free(sdcDistanceTable);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistanceTableAdc

**接口定义<a name="section172317194488"></a>**

int GetPQDistanceTableAdc\(float\* vector, const PQParams \*params, float \*pqDistanceTable, size\_t pqDistanceTable\_size\);

**接口用途<a name="section1153124784912"></a>**

计算PQ ADC距离表，即计算查询向量和各个子空间内聚类中心的距离。

**参数说明<a name="section157501312135019"></a>**

| 参数名称 | 数据类型 | 描述 | 取值范围 |
| --- | --- | --- | --- |
| vector | float* | 原始向量。 | 限制非空；每个分量必须为有限值且绝对值不超过 1e17，否则接口返回 -1。 |
| pqDistanceTable | float* | ADC距离表。也可以作为输出值。 | 限制非空。长度为pqDistanceTable_size，其中“pqDistanceTable_size”为ADC距离表数组的长度。 |
| pqDistanceTable_size | size_t | ADC距离表数组的长度。 | 限制为pqM*pqKsub，其中“pqM”是结构体“PQParams”中的字段，表示子空间数，“pqKsub”是结构体“PQParams”中的字段，表示子空间内聚类中心数。 |
| params | const PQParams | 字段描述请参见[结构体说明](#结构体说明)中的“PQParams”字段描述。 | - |

**返回值**

| 数据类型 | 说明 |
| --- | --- |
| int | 正常运行时返回0，异常退出返回-1。 |

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"
using namespace PQHead;

int main() {
    // 假设已通过ComputePQTable计算得到PQ码本
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // 初始化PQParams（假设pqTable已填充）
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.funcType = 1;  // L2距离
    params.subItemSize = (sizeof(Vector) + sizeof(float) * (dim / pqM) + MAXIMUM_ALIGNOF - 1) & ~(size_t)(MAXIMUM_ALIGNOF - 1);  // 头部+数据，按 MAXIMUM_ALIGNOF 对齐
    
    size_t pqTableSize = pqM * pqKsub * params.subItemSize;
    params.pqTable = (char*)malloc(pqTableSize);
    // ... 假设pqTable已通过ComputePQTable填充 ...

    // 准备查询向量
    float* queryVector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        queryVector[i] = (float)rand() / RAND_MAX;  // 示例数据
    }

    // 计算ADC距离表大小并分配内存
    // ADC表存储查询向量与每个子空间内所有聚类中心的距离
    size_t adcTableSize = pqM * pqKsub;
    float* adcDistanceTable = (float*)malloc(adcTableSize * sizeof(float));
    if (adcDistanceTable == NULL) {
        printf("ADC距离表内存分配失败\n");
        free(queryVector);
        free(params.pqTable);
        return -1;
    }

    // 计算ADC距离表
    int ret = GetPQDistanceTableAdc(queryVector, &params, adcDistanceTable, adcTableSize);

    if (ret != 0) {
        printf("计算ADC距离表失败，错误码: %d\n", ret);
        free(adcDistanceTable);
        free(queryVector);
        free(params.pqTable);
        return -1;
    }

    printf("成功计算ADC距离表\n");
    printf("  - 距离表大小: %zu\n", adcTableSize);
    printf("  - 查询向量与子空间0中心0的距离: %f\n", adcDistanceTable[0]);

    // ... 使用ADC距离表进行后续距离计算 ...

    // 清理资源
    free(adcDistanceTable);
    free(queryVector);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistance

**接口定义<a name="section172317194488"></a>**

int GetPQDistance\(const unsigned char \*basecode, const unsigned char \*querycode, const PQParams \*params, const float \*pqDistanceTable, float \*PQDistance, size\_t basecode\_size, size\_t querycode\_size, size\_t pqDistanceTable\_size, size\_t pqDistance\_size\);

**接口用途<a name="section1153124784912"></a>**

计算PQ ADC或SDC距离。若querycode == NULL，计算的是ADC距离；若querycode != NULL，计算的是SDC距离。

**参数说明<a name="section157501312135019"></a>**

| 参数名称 | 数据类型 | 描述 | 取值范围 |
| --- | --- | --- | --- |
| basecode | unsigned char* | 量化后的base。 | 限制非空。 |
| querycode | unsigned char* | 量化后的query。 | - |
| pqDistanceTable | float* | SDC/ADC距离表。 | 限制非空。 |
| PQDistance | float* | SDC/ADC距离。 | 限制非空。 |
| basecode_size | size_t | 量化后的base数组的长度。 | 限制为pqM，其中“pqM”是结构体“PQParams”中的字段，表示子空间数。 |
| querycode_size | size_t | 量化后的query数组的长度。 | 若querycode非空，限制为pqM，其中“querycode”表示量化后的query，“pqM”是结构体“PQParams”中的字段，表示子空间数。 |
| pqDistanceTable_size | size_t | SDC/ADC距离表数组的长度。 | 若querycode为空时，限制为pqM*pqKsub，querycode非空时，限制为pqM*pqKsub*pqKsub，其中“querycode”表示量化后的query，“pqM”是结构体“PQParams”中的字段，表示子空间数，“pqKsub”是结构体“PQParams”中的字段，表示子空间内聚类中心数。 |
| PQDistance_size | size_t | SDC/ADC距离数组的长度。 | 限制为1。 |
| params | const PQParams | 字段描述请参见[结构体说明](#结构体说明)中的“PQParams”字段描述。 | - |

**返回值**

| 数据类型 | 说明 |
| --- | --- |
| int | 正常运行时返回0，异常退出返回-1。 |

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"
using namespace PQHead;

int main() {
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // 初始化PQParams（假设pqTable已填充）
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.funcType = 1;  // L2距离
    params.subItemSize = (sizeof(Vector) + sizeof(float) * (dim / pqM) + MAXIMUM_ALIGNOF - 1) & ~(size_t)(MAXIMUM_ALIGNOF - 1);  // 头部+数据，按 MAXIMUM_ALIGNOF 对齐
    
    size_t pqTableSize = pqM * pqKsub * params.subItemSize;
    params.pqTable = (char*)malloc(pqTableSize);
    // ... 假设pqTable已通过ComputePQTable填充 ...

    // 准备base和query向量的PQ码（假设已通过ComputeVectorPQCode得到）
    unsigned char* basecode = (unsigned char*)malloc(pqM);
    unsigned char* querycode = (unsigned char*)malloc(pqM);
    for (int i = 0; i < pqM; i++) {
        basecode[i] = rand() % pqKsub;
        querycode[i] = rand() % pqKsub;
    }

    // 准备查询向量（用于ADC距离计算）
    float* queryVector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        queryVector[i] = (float)rand() / RAND_MAX;
    }

    float pqDistance = 0.0f;
    int ret;

    // ========== 方式1：计算ADC距离（querycode为NULL） ==========
    // ADC距离表大小：pqM * pqKsub
    size_t adcTableSize = pqM * pqKsub;
    float* adcDistanceTable = (float*)malloc(adcTableSize * sizeof(float));
    GetPQDistanceTableAdc(queryVector, &params, adcDistanceTable, adcTableSize);

    ret = GetPQDistance(
        basecode,           // 量化后的base
        NULL,               // querycode为NULL，计算ADC距离
        &params,
        adcDistanceTable,
        &pqDistance,
        pqM,                // basecode_size
        0,                  // querycode_size（querycode为NULL时无意义）
        adcTableSize,       // ADC距离表大小
        1                   // 输出距离数组大小
    );

    if (ret == 0) {
        printf("ADC距离: %f\n", pqDistance);
    }

    // ========== 方式2：计算SDC距离（querycode非NULL） ==========
    // SDC距离表大小：pqM * pqKsub * pqKsub
    size_t sdcTableSize = pqM * pqKsub * pqKsub;
    float* sdcDistanceTable = (float*)malloc(sdcTableSize * sizeof(float));
    GetPQDistanceTableSdc(&params, sdcDistanceTable, sdcTableSize);

    ret = GetPQDistance(
        basecode,           // 量化后的base
        querycode,          // querycode非NULL，计算SDC距离
        &params,
        sdcDistanceTable,
        &pqDistance,
        pqM,                // basecode_size
        pqM,                // querycode_size
        sdcTableSize,       // SDC距离表大小
        1                   // 输出距离数组大小
    );

    if (ret == 0) {
        printf("SDC距离: %f\n", pqDistance);
    }

    // 清理资源
    free(queryVector);
    free(adcDistanceTable);
    free(sdcDistanceTable);
    free(basecode);
    free(querycode);
    free(params.pqTable);

    return 0;
}
```

## 修订记录

|文档版本|发布日期|修改说明|
|--|--|--|
|01|2025-09-30|第一次正式发布。|
