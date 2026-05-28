# API Reference

## API List

[**Table 1** KVecTurbo APIs](#table1194910128449) lists the APIs provided by KVecTurbo.

**Table 1** KVecTurbo APIs<a id="table1194910128449"></a>

<a id="table1194910128449"></a>
<table><thead align="left"><tr id="row99491812134412"><th class="cellrowborder" valign="top" width="31.25%" id="mcps1.2.3.1.1"><p id="p1794951224415"><a name="p1794951224415"></a><a name="p1794951224415"></a>API</p>
</th>
<th class="cellrowborder" valign="top" width="68.75%" id="mcps1.2.3.1.2"><p id="p6949612124415"><a name="p6949612124415"></a><a name="p6949612124415"></a>Function</p>
</th>
</tr>
</thead>
<tbody><tr id="row712018285575"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p12121102835714"><a name="p12121102835714"></a><a name="p12121102835714"></a>ComputePQTable</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p111217289571"><a name="p111217289571"></a><a name="p111217289571"></a>Calculates the PQ codebook.</p>
</td>
</tr>
<tr id="row119491112174414"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p539219519167"><a name="p539219519167"></a><a name="p539219519167"></a>ComputeVectorPQCode</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p617774433819"><a name="p617774433819"></a><a name="p617774433819"></a>Quantizes the input vector based on the PQ codebook.</p>
</td>
</tr>
<tr id="row9949131219443"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p1094921294415"><a name="p1094921294415"></a><a name="p1094921294415"></a>GetPQDistanceTableSdc</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p1794941284418"><a name="p1794941284418"></a><a name="p1794941284418"></a>Calculates the PQ SDC distance table, that is, calculates the distance between the cluster centroids in each subspace.</p>
</td>
</tr>
<tr id="row1594913120443"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p472151416393"><a name="p472151416393"></a><a name="p472151416393"></a>GetPQDistanceTableAdc</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p1509193871710"><a name="p1509193871710"></a><a name="p1509193871710"></a>Calculates the PQ ADC distance table, that is, calculates the distance between the query vector and the cluster centroids in each subspace.</p>
</td>
</tr>
<tr id="row6949131274416"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p81502298399"><a name="p81502298399"></a><a name="p81502298399"></a>GetPQDistance</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p31521029163914"><a name="p31521029163914"></a><a name="p31521029163914"></a>Calculates the PQ ADC or SDC distance. If querycode == NULL, the ADC distance is calculated. If querycode != NULL, the SDC distance is calculated.</p>
</td>
</tr>
</tbody>
</table>

## Struct Description

The parameters used by the KVecTurbo APIs involve the `VectorArray` and `PQParams` structures. For details, see [**Table 1** VectorArray field description](#table1646711617442) and [**Table 2** PQParams field description](#table11706934103516).

**Table 1** VectorArray field description<a id="table1646711617442"></a>

<a id="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="16.27%" id="mcps1.2.5.1.1"><p id="p81762043154713"><a name="p81762043154713"></a><a name="p81762043154713"></a>Field</p>
</th>
<th class="cellrowborder" valign="top" width="21.82%" id="mcps1.2.5.1.2"><p id="p4377125320521"><a name="p4377125320521"></a><a name="p4377125320521"></a><strong id="b1137765315529"><a name="b1137765315529"></a><a name="b1137765315529"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="18.88%" id="mcps1.2.5.1.3"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a>Data Type</strong></p>
</th>
<th class="cellrowborder" valign="top" width="43.03%" id="mcps1.2.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row18468216154410"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p8902349194711"><a name="p8902349194711"></a><a name="p8902349194711"></a>maxLen</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p4377115320525"><a name="p4377115320525"></a><a name="p4377115320525"></a>Maximum number of vectors.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p784815918455"><a name="p784815918455"></a><a name="p784815918455"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p484829144516"><a name="p484829144516"></a><a name="p484829144516"></a>If the value is too large, the memory allocation may fail due to insufficient system memory resources.</p>
</td>
</tr>
<tr id="row4356161812514"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p1236742011517"><a name="p1236742011517"></a><a name="p1236742011517"></a>length</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p1936720201356"><a name="p1936720201356"></a><a name="p1936720201356"></a>Number of vectors.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p123673202050"><a name="p123673202050"></a><a name="p123673202050"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p1836710201655"><a name="p1836710201655"></a><a name="p1836710201655"></a>[1, maxLen], where <code>maxLen</code> is a field in the <code>VectorArray</code> structure, indicating the maximum number of vectors.</p>
</td>
</tr>
<tr id="row746811684410"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p159021849104714"><a name="p159021849104714"></a><a name="p159021849104714"></a>dim</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p12377153155215"><a name="p12377153155215"></a><a name="p12377153155215"></a>Vector dimension.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p48488911459"><a name="p48488911459"></a><a name="p48488911459"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p08481993451"><a name="p08481993451"></a><a name="p08481993451"></a>[1, 2000]</p>
</td>
</tr>
<tr id="row84681167446"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p1190210496473"><a name="p1190210496473"></a><a name="p1190210496473"></a>itemSize</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p2377753175214"><a name="p2377753175214"></a><a name="p2377753175214"></a>Length of a single vector.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p1784811934515"><a name="p1784811934515"></a><a name="p1784811934515"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p16848139174518"><a name="p16848139174518"></a><a name="p16848139174518"></a>The value cannot be <code>0</code>.</p>
</td>
</tr>
<tr id="row11468101614449"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p1290213494474"><a name="p1290213494474"></a><a name="p1290213494474"></a>items</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p163771553175210"><a name="p163771553175210"></a><a name="p163771553175210"></a>Start addresses of <code>length</code> vectors.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p28481299458"><a name="p28481299458"></a><a name="p28481299458"></a>char*</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p13848119154518"><a name="p13848119154518"></a><a name="p13848119154518"></a>The value cannot be null.</p>
</td>
</tr>
</tbody>
</table>

**Table 2** PQParams field description<a id="table11706934103516"></a>

<a id="table11706934103516"></a>
<table><thead align="left"><tr id="row11414124012358"><th class="cellrowborder" valign="top" width="16.27%" id="mcps1.2.5.1.1"><p id="p82251946143516"><a name="p82251946143516"></a><a name="p82251946143516"></a>Field</p>
</th>
<th class="cellrowborder" valign="top" width="21.82%" id="mcps1.2.5.1.2"><p id="p102251046193511"><a name="p102251046193511"></a><a name="p102251046193511"></a><strong id="b9225194613512"><a name="b9225194613512"></a><a name="b9225194613512"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="18.88%" id="mcps1.2.5.1.3"><p id="p16225194616358"><a name="p16225194616358"></a><a name="p16225194616358"></a><strong id="b1722524613356"><a name="b1722524613356"></a><a name="b1722524613356"></a>Data Type</strong></p>
</th>
<th class="cellrowborder" valign="top" width="43.03%" id="mcps1.2.5.1.4"><p id="p102251446143517"><a name="p102251446143517"></a><a name="p102251446143517"></a><strong id="b18225114653515"><a name="b18225114653515"></a><a name="b18225114653515"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row11788163121319"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p125529339138"><a name="p125529339138"></a><a name="p125529339138"></a>dim</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p17552633101319"><a name="p17552633101319"></a><a name="p17552633101319"></a>Dimension.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p135521633171317"><a name="p135521633171317"></a><a name="p135521633171317"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p12552193321320"><a name="p12552193321320"></a><a name="p12552193321320"></a>[1, 2000]</p>
</td>
</tr>
<tr id="row9706834203510"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p6902174915472"><a name="p6902174915472"></a><a name="p6902174915472"></a>pqM</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p17377175319523"><a name="p17377175319523"></a><a name="p17377175319523"></a>Number of subspaces.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p38481898457"><a name="p38481898457"></a><a name="p38481898457"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p15848209134510"><a name="p15848209134510"></a><a name="p15848209134510"></a>[1, dim], where <code>dim</code> is a field in the <code>PQParams</code> structure, indicating the vector dimension.</p>
</td>
</tr>
<tr id="row167067341356"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p169031449134713"><a name="p169031449134713"></a><a name="p169031449134713"></a>pqKsub</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p33781853165216"><a name="p33781853165216"></a><a name="p33781853165216"></a>Number of cluster centroids in the subspace.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p2848159114511"><a name="p2848159114511"></a><a name="p2848159114511"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p28487964518"><a name="p28487964518"></a><a name="p28487964518"></a>[1, 256]</p>
</td>
</tr>
<tr id="row3706173411353"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p15903249194711"><a name="p15903249194711"></a><a name="p15903249194711"></a>functype</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p10378553185217"><a name="p10378553185217"></a><a name="p10378553185217"></a>Distance type.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p48488911458"><a name="p48488911458"></a><a name="p48488911458"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p1260341310305"><a name="p1260341310305"></a><a name="p1260341310305"></a>[1, 3]</p>
<a name="ul7615133223018"></a><a name="ul7615133223018"></a><ul id="ul7615133223018"><li><code>1</code>: L2 type. </li><li><code>2</code>: Inner product (IP) type. </li><li><code>3</code>: Cosine type.</li></ul>
</td>
</tr>
<tr id="row4707934123513"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p209032495474"><a name="p209032495474"></a><a name="p209032495474"></a>subItemSize</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p6378053195212"><a name="p6378053195212"></a><a name="p6378053195212"></a>Codeword size.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p2849991457"><a name="p2849991457"></a><a name="p2849991457"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p98491298451"><a name="p98491298451"></a><a name="p98491298451"></a>The value cannot be <code>0</code>.</p>
</td>
</tr>
<tr id="row1670718344353"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p19903154912477"><a name="p19903154912477"></a><a name="p19903154912477"></a>pqTable</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p9378175375213"><a name="p9378175375213"></a><a name="p9378175375213"></a>Codebook.</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p88493920454"><a name="p88493920454"></a><a name="p88493920454"></a>char*</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p6849189154513"><a name="p6849189154513"></a><a name="p6849189154513"></a>The value cannot be null.</p>
</td>
</tr>
</tbody>
</table>

### Example

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvecturbo.h"

int main() {
    // Parameter configuration
    int dim = 128;          // Vector dimension
    int numSamples = 10000; // Number of training samples
    int pqM = 8;            // Number of subspaces (dim must be exactly divisible by pqM)
    int pqKsub = 256;       // Number of cluster centers per subspace
    int functype = 1;       // L2 distance

    // Prepare training sample data.
    size_t dataSize = numSamples * dim * sizeof(float);
    float* sampleData = (float*)malloc(dataSize);
    if (sampleData == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    //... Populate sampleData with training data ...
    for (int i = 0; i < numSamples * dim; i++) {
        sampleData[i] = (float)rand() / RAND_MAX;  // Example: random filling
    }

    // Initialize the VectorArray structure.
    VectorArray samples;
    samples.maxLen = numSamples;
    samples.length = numSamples;
    samples.dim = dim;
    samples.itemSize = dim * sizeof(float);
    samples.items = (char*)sampleData;

    // Initialize the PQParams structure.
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = functype;
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    // Allocate storage space for the codebook.
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    if (params.pqTable == NULL) {
        printf("Failed to allocate memory for the codebook.\n");
        free(sampleData);
        return -1;
    }

    // Calculate the PQ codebook.
    int ret = ComputePQTable(samples, &params);

    if (ret != 0) {
        printf("Failed to compute the PQ codebook. Error code: %d\n", ret);
        free(sampleData);
        free(params.pqTable);
        return -1;
    }

    printf("PQ codebook computed successfully.\n");
    printf(" - Number of subspaces: %d\n", pqM);
    printf(" - Number of cluster centers per subspace: %d\n", pqKsub);

    //... Use params.pqTable to perform subsequent quantization operations.

    // Free resources.
    free(sampleData);
    free(params.pqTable);

    return 0;
}
```

## ComputePQTable

**API Definition<a name="section172317194488"></a>**

int ComputePQTable\(VectorArray samples, PQParams \*params\);

**Function<a name="section1153124784912"></a>**

Calculates the PQ codebook.

**Parameters<a name="section157501312135019"></a>**

<a name="table4285822103716"></a>
<table><thead align="left"><tr id="row1286152233717"><th class="cellrowborder" valign="top" width="15.39%" id="mcps1.1.5.1.1"><p id="p1028632213373"><a name="p1028632213373"></a><a name="p1028632213373"></a><strong id="b229432916375"><a name="b229432916375"></a><a name="b229432916375"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="19.24%" id="mcps1.1.5.1.2"><p id="p426420913521"><a name="p426420913521"></a><a name="p426420913521"></a><strong id="b1657933643718"><a name="b1657933643718"></a><a name="b1657933643718"></a>Data Type</strong></p>
</th>
<th class="cellrowborder" valign="top" width="35.3%" id="mcps1.1.5.1.3"><p id="p16579163614371"><a name="p16579163614371"></a><a name="p16579163614371"></a><strong id="b65791236113717"><a name="b65791236113717"></a><a name="b65791236113717"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="30.070000000000004%" id="mcps1.1.5.1.4"><p id="p1657912363375"><a name="p1657912363375"></a><a name="p1657912363375"></a><strong id="b55791367373"><a name="b55791367373"></a><a name="b55791367373"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row16286112213372"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p1244551123717"><a name="p1244551123717"></a><a name="p1244551123717"></a>samples</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p1726499165213"><a name="p1726499165213"></a><a name="p1726499165213"></a>VectorArray</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p928622293716"><a name="p928622293716"></a><a name="p928622293716"></a>For details, see <a href="#table1646711617442">VectorArray field description.</a></p>
</td>
</tr>
<tr id="row6286022173712"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p1596013543378"><a name="p1596013543378"></a><a name="p1596013543378"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p226410910524"><a name="p226410910524"></a><a name="p226410910524"></a>PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p107381649203819"><a name="p107381649203819"></a><a name="p107381649203819"></a>For details, see <a href="#table11706934103516">PQParams field description.</a> The <code>pqTable</code> may also be used as an output value.</p>
</td>
</tr>
</tbody>
</table>

**Return Value<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>Data Type</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>The value <code>0</code> is returned when the system runs properly, and the value <code>-1</code> is returned when the system exits abnormally.</p>
</td>
</tr>
</tbody>
</table>

### Example

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvecturbo.h"

int main() {
    // Parameter configuration
    int dim = 128;          // Vector dimension
    int numSamples = 10000; // Number of training samples
    int pqM = 8;            // Number of subspaces (dim must be exactly divisible by pqM)
    int pqKsub = 256;       // Number of cluster centers per subspace
    int functype = 1;       // L2 distance

    // Prepare training sample data.
    size_t dataSize = numSamples * dim * sizeof(float);
    float* sampleData = (float*)malloc(dataSize);
    if (sampleData == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    //... Populate sampleData with training data ...
    for (int i = 0; i < numSamples * dim; i++) {
        sampleData[i] = (float)rand() / RAND_MAX;  // Example: random filling
    }

    // Initialize the VectorArray structure.
    VectorArray samples;
    samples.maxLen = numSamples;
    samples.length = numSamples;
    samples.dim = dim;
    samples.itemSize = dim * sizeof(float);
    samples.items = (char*)sampleData;

    // Initialize the PQParams structure.
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = functype;
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    // Allocate storage space for the codebook.
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    if (params.pqTable == NULL) {
        printf("Failed to allocate memory for the codebook.\n");
        free(sampleData);
        return -1;
    }

    // Calculate the PQ codebook.
    int ret = ComputePQTable(samples, &params);

    if (ret != 0) {
        printf("Failed to compute the PQ codebook. Error code: %d\n", ret);
        free(sampleData);
        free(params.pqTable);
        return -1;
    }

    printf("PQ codebook computed successfully.\n");
    printf(" - Number of subspaces: %d\n", pqM);
    printf(" - Number of cluster centers per subspace: %d\n", pqKsub);

    //... Use params.pqTable to perform subsequent quantization operations.

    // Free resources.
    free(sampleData);
    free(params.pqTable);

    return 0;
}
```

## ComputeVectorPQCode

**API Definition<a name="section172317194488"></a>**

int ComputeVectorPQCode\(float \*vector, const PQParams \*params, unsigned char \*pqCode, size\_t pqCode\_size\);

**Function<a name="section1153124784912"></a>**

Quantizes the input vector based on the PQ codebook.

**Parameters<a name="section157501312135019"></a>**

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="16.06%" id="mcps1.1.5.1.1"><p id="p1035755516441"><a name="p1035755516441"></a><a name="p1035755516441"></a><strong id="b535775554413"><a name="b535775554413"></a><a name="b535775554413"></a> Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="18.56%" id="mcps1.1.5.1.2"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a> Data Type</strong></p>
</th>
<th class="cellrowborder" valign="top" width="33.85%" id="mcps1.1.5.1.3"><p id="p577354119532"><a name="p577354119532"></a><a name="p577354119532"></a><strong id="b9773541165316"><a name="b9773541165316"></a><a name="b9773541165316"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="31.53%" id="mcps1.1.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row146815169448"><td class="cellrowborder" valign="top" width="16.06%" headers="mcps1.1.5.1.1 "><p id="p18290135419477"><a name="p18290135419477"></a><a name="p18290135419477"></a>vector</p>
</td>
<td class="cellrowborder" valign="top" width="18.56%" headers="mcps1.1.5.1.2 "><p id="p5290654174714"><a name="p5290654174714"></a><a name="p5290654174714"></a>float *</p>
</td>
<td class="cellrowborder" valign="top" width="33.85%" headers="mcps1.1.5.1.3 "><p id="p197735413538"><a name="p197735413538"></a><a name="p197735413538"></a>Original vector.</p>
</td>
<td class="cellrowborder" valign="top" width="31.53%" headers="mcps1.1.5.1.4 "><p id="p1829095424711"><a name="p1829095424711"></a><a name="p1829095424711"></a>The value cannot be null.</p>
</td>
</tr>
<tr id="row18468216154410"><td class="cellrowborder" valign="top" width="16.06%" headers="mcps1.1.5.1.1 "><p id="p2290754114711"><a name="p2290754114711"></a><a name="p2290754114711"></a>pqCode</p>
</td>
<td class="cellrowborder" valign="top" width="18.56%" headers="mcps1.1.5.1.2 "><p id="p112901054164717"><a name="p112901054164717"></a><a name="p112901054164717"></a>unsigned char *</p>
</td>
<td class="cellrowborder" valign="top" width="33.85%" headers="mcps1.1.5.1.3 "><p id="p17773144119539"><a name="p17773144119539"></a><a name="p17773144119539"></a>Quantized vector. It can also be used as an output value.</p>
</td>
<td class="cellrowborder" valign="top" width="31.53%" headers="mcps1.1.5.1.4 "><p id="p184321218164110"><a name="p184321218164110"></a><a name="p184321218164110"></a>The value cannot be null. The value is specified by <code>pqCode_size</code>, the length of the quantized vector array.</p>
</td>
</tr>
<tr id="row1097711208581"><td class="cellrowborder" valign="top" width="16.06%" headers="mcps1.1.5.1.1 "><p id="p18978152020588"><a name="p18978152020588"></a><a name="p18978152020588"></a>pqCode_size</p>
</td>
<td class="cellrowborder" valign="top" width="18.56%" headers="mcps1.1.5.1.2 "><p id="p18978920195820"><a name="p18978920195820"></a><a name="p18978920195820"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="33.85%" headers="mcps1.1.5.1.3 "><p id="p1197892016583"><a name="p1197892016583"></a><a name="p1197892016583"></a>Length of the quantized vector array.</p>
</td>
<td class="cellrowborder" valign="top" width="31.53%" headers="mcps1.1.5.1.4 "><p id="p169783208589"><a name="p169783208589"></a><a name="p169783208589"></a>The value is specified by <code>pqM</code>, which is a field in the <code>PQParams</code> structure and indicates the number of subspaces.</p>
</td>
</tr>
<tr id="row746811684410"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p1329075411477"><a name="p1329075411477"></a><a name="p1329075411477"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p8969751950"><a name="p8969751950"></a><a name="p8969751950"></a>const PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p107381649203819"><a name="p107381649203819"></a><a name="p107381649203819"></a>For details, see <a href="#table11706934103516">PQParams field description.</a></p>
</td>
</tr>
</tbody>
</table>

**Return Value<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>Data Type</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>The value <code>0</code> is returned when the system runs properly, and the value <code>-1</code> is returned when the system exits abnormally.</p>
</td>
</tr>
</tbody>
</table>

### Example

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"

int main() {
    // Assume that the PQ codebook has been obtained by calling ComputePQTable
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // Initialize PQParams (assuming that pqTable has been populated with data).
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = 1;  // L2 distance
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    // Allocate memory and populate the codebook (in production, use the output of ComputePQTable)
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    // ... Assume that pqTable has been filled by calling ComputePQTable ...

    // Prepare the original vector to be quantized.
    float* vector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        vector[i] = (float)rand() / RAND_MAX;  // Example data
    }

    // Allocate storage for quantized PQ codes
    size_t pqCodeSize = pqM; // One codeword (uint8) per subspace
    unsigned char* pqCode = (unsigned char*)malloc(pqCodeSize);

    // Perform vector quantization.
    int ret = ComputeVectorPQCode(vector, &params, pqCode, pqCodeSize);

    if (ret != 0) {
        printf("Vector quantization failed. Error code: %d\n", ret);
        free(vector);
        free(pqCode);
        free(params.pqTable);
        return -1;
    }

    printf("Vector quantization succeeded.\n");
    printf("PQ code: ");
    for (size_t i = 0; i < pqCodeSize; i++) {
        printf("%u ", pqCode[i]);
    }
    printf("\n");

    // Free resources.
    free(vector);
    free(pqCode);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistanceTableSdc

**API Definition<a name="section172317194488"></a>**

int GetPQDistanceTableSdc\(const PQParams \*params, float \*pqDistanceTable, size\_t pqDistanceTable\_size\);

**Function<a name="section1153124784912"></a>**

Calculates the PQ SDC distance table, that is, calculates the distance between the cluster centroids in each subspace.

**Parameters<a name="section157501312135019"></a>**

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="18.94810518948105%" id="mcps1.1.5.1.1"><p id="p1035755516441"><a name="p1035755516441"></a><a name="p1035755516441"></a><strong id="b535775554413"><a name="b535775554413"></a><a name="b535775554413"></a> Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="17.408259174082595%" id="mcps1.1.5.1.2"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a> Data Type</strong></p>
</th>
<th class="cellrowborder" valign="top" width="31.586841315868412%" id="mcps1.1.5.1.3"><p id="p1161011635413"><a name="p1161011635413"></a><a name="p1161011635413"></a><strong id="b26101665540"><a name="b26101665540"></a><a name="b26101665540"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="32.056794320567946%" id="mcps1.1.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row146815169448"><td class="cellrowborder" valign="top" width="18.94810518948105%" headers="mcps1.1.5.1.1 "><p id="p19390163034918"><a name="p19390163034918"></a><a name="p19390163034918"></a>pqDistanceTable</p>
</td>
<td class="cellrowborder" valign="top" width="17.408259174082595%" headers="mcps1.1.5.1.2 "><p id="p11390103044916"><a name="p11390103044916"></a><a name="p11390103044916"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="31.586841315868412%" headers="mcps1.1.5.1.3 "><p id="p1461013614543"><a name="p1461013614543"></a><a name="p1461013614543"></a>SDC distance table. It can also be used as an output value.</p>
</td>
<td class="cellrowborder" valign="top" width="32.056794320567946%" headers="mcps1.1.5.1.4 "><p id="p93901930134918"><a name="p93901930134918"></a><a name="p93901930134918"></a>The value cannot be null. The value is specified by <code>pqDistanceTable_size</code>, the length of the SDC distance table array.</p>
</td>
</tr>
<tr id="row1827017313116"><td class="cellrowborder" valign="top" width="18.94810518948105%" headers="mcps1.1.5.1.1 "><p id="p17270143818"><a name="p17270143818"></a><a name="p17270143818"></a>pqDistanceTable_size</p>
</td>
<td class="cellrowborder" valign="top" width="17.408259174082595%" headers="mcps1.1.5.1.2 "><p id="p32701332011"><a name="p32701332011"></a><a name="p32701332011"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="31.586841315868412%" headers="mcps1.1.5.1.3 "><p id="p18270031811"><a name="p18270031811"></a><a name="p18270031811"></a>Length of the SDC distance table array.</p>
</td>
<td class="cellrowborder" valign="top" width="32.056794320567946%" headers="mcps1.1.5.1.4 "><p id="p2270133219"><a name="p2270133219"></a><a name="p2270133219"></a>The value is specified by <code>pqM</code> × <code>pqKsub</code> × <code>pqKsub</code>, where <code>pqM</code> and <code>pqKsub</code> are fields in the <code>PQParams</code> structure, respectively indicating the number of subspaces and the number of cluster centroids in these subspaces.</p>
</td>
</tr>
<tr id="row18468216154410"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p129318508517"><a name="p129318508517"></a><a name="p129318508517"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p550413473510"><a name="p550413473510"></a><a name="p550413473510"></a>const PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p107381649203819"><a name="p107381649203819"></a><a name="p107381649203819"></a>For details, see <a href="#table11706934103516">PQParams field description.</a></p>
</td>
</tr>
</tbody>
</table>

**Return Value<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>Data Type</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>The value <code>0</code> is returned when the system runs properly, and the value <code>-1</code> is returned when the system exits abnormally.</p>
</td>
</tr>
</tbody>
</table>

### Example

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"

int main() {
    // Assume that the PQ codebook has been obtained by calling ComputePQTable
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // Initialize PQParams (assuming that pqTable has been populated with data).
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = 1;  // L2 distance
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    // ... Assume that pqTable has been filled by calling ComputePQTable ...

    // Calculate the size of the SDC distance table and allocate memory.
    // The SDC table stores the distance between all cluster center pairs in each subspace.
    size_t sdcTableSize = pqM * pqKsub * pqKsub;
    float* sdcDistanceTable = (float*)malloc(sdcTableSize * sizeof(float));
    if (sdcDistanceTable == NULL) {
        printf("Failed to allocate memory for the SDC distance table.\n");
        free(params.pqTable);
        return -1;
    }

    // Calculate the SDC distance table.
    int ret = GetPQDistanceTableSdc(&params, sdcDistanceTable, sdcTableSize);

    if (ret != 0) {
        printf("Failed to calculate the SDC distance table. Error code: %d\n", ret);
        free(sdcDistanceTable);
        free(params.pqTable);
        return -1;
    }

    printf("The SDC distance table is successfully calculated.\n");
    printf(" - Distance table size: %zu\n", sdcTableSize);
    printf(" - Distance between the first subspace center 0 and center 1: %f\n", sdcDistanceTable[1]);

    //...Use the SDC distance table for subsequent distance calculations ...

    // Free resources.
    free(sdcDistanceTable);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistanceTableAdc

**API Definition<a name="section172317194488"></a>**

int GetPQDistanceTableAdc\(float\* vector, const PQParams \*params, float \*pqDistanceTable, size\_t pqDistanceTable\_size\);

**Function<a name="section1153124784912"></a>**

Calculates the PQ ADC distance table, that is, calculates the distance between the query vector and the cluster centroids in each subspace.

**Parameters<a name="section157501312135019"></a>**

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="18.34%" id="mcps1.1.5.1.1"><p id="p1035755516441"><a name="p1035755516441"></a><a name="p1035755516441"></a><strong id="b535775554413"><a name="b535775554413"></a><a name="b535775554413"></a> Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="16.11%" id="mcps1.1.5.1.2"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a> Data Type</strong></p>
</th>
<th class="cellrowborder" valign="top" width="35.23%" id="mcps1.1.5.1.3"><p id="p11531628175416"><a name="p11531628175416"></a><a name="p11531628175416"></a><strong id="b15372812545"><a name="b15372812545"></a><a name="b15372812545"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="30.320000000000004%" id="mcps1.1.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row146815169448"><td class="cellrowborder" valign="top" width="18.34%" headers="mcps1.1.5.1.1 "><p id="p3391114550"><a name="p3391114550"></a><a name="p3391114550"></a>vector</p>
</td>
<td class="cellrowborder" valign="top" width="16.11%" headers="mcps1.1.5.1.2 "><p id="p1539161116559"><a name="p1539161116559"></a><a name="p1539161116559"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="35.23%" headers="mcps1.1.5.1.3 "><p id="p19533285546"><a name="p19533285546"></a><a name="p19533285546"></a>Original vector.</p>
</td>
<td class="cellrowborder" valign="top" width="30.320000000000004%" headers="mcps1.1.5.1.4 "><p id="p153918116557"><a name="p153918116557"></a><a name="p153918116557"></a>The value cannot be null.</p>
</td>
</tr>
<tr id="row18468216154410"><td class="cellrowborder" valign="top" width="18.34%" headers="mcps1.1.5.1.1 "><p id="p939711155514"><a name="p939711155514"></a><a name="p939711155514"></a>pqDistanceTable</p>
</td>
<td class="cellrowborder" valign="top" width="16.11%" headers="mcps1.1.5.1.2 "><p id="p439181115515"><a name="p439181115515"></a><a name="p439181115515"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="35.23%" headers="mcps1.1.5.1.3 "><p id="p45318284546"><a name="p45318284546"></a><a name="p45318284546"></a>ADC distance table. It can also be used as an output value.</p>
</td>
<td class="cellrowborder" valign="top" width="30.320000000000004%" headers="mcps1.1.5.1.4 "><p id="p143911120557"><a name="p143911120557"></a><a name="p143911120557"></a>The value cannot be null. The value is specified by <code>pqDistanceTable_size</code>, the length of the ADC distance table array.</p>
</td>
</tr>
<tr id="row44811238446"><td class="cellrowborder" valign="top" width="18.34%" headers="mcps1.1.5.1.1 "><p id="p17270143818"><a name="p17270143818"></a><a name="p17270143818"></a>pqDistanceTable_size</p>
</td>
<td class="cellrowborder" valign="top" width="16.11%" headers="mcps1.1.5.1.2 "><p id="p32701332011"><a name="p32701332011"></a><a name="p32701332011"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.23%" headers="mcps1.1.5.1.3 "><p id="p18270031811"><a name="p18270031811"></a><a name="p18270031811"></a>Length of the ADC distance table array.</p>
</td>
<td class="cellrowborder" valign="top" width="30.320000000000004%" headers="mcps1.1.5.1.4 "><p id="p2270133219"><a name="p2270133219"></a><a name="p2270133219"></a>The value is specified by <code>pqM</code> × <code>pqKsub</code> × <code>pqKsub</code>, where <code>pqM</code> and <code>pqKsub</code> are fields in the <code>PQParams</code> structure, respectively indicating the number of subspaces and the number of cluster centroids in these subspaces.</p>
</td>
</tr>
<tr id="row746811684410"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p26190151167"><a name="p26190151167"></a><a name="p26190151167"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p674585615524"><a name="p674585615524"></a><a name="p674585615524"></a>const PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p184692620448"><a name="p184692620448"></a><a name="p184692620448"></a>For details, see <a href="#table11706934103516">PQParams field description.</a></p>
</td>
</tr>
</tbody>
</table>

**Return Value<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>Data Type</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>The value <code>0</code> is returned when the system runs properly, and the value <code>-1</code> is returned when the system exits abnormally.</p>
</td>
</tr>
</tbody>
</table>

### Example

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"

int main() {
    // Assume that the PQ codebook has been obtained by calling ComputePQTable
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // Initialize PQParams (assuming that pqTable has been populated with data).
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = 1;  // L2 distance
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    // ... Assume that pqTable has been filled by calling ComputePQTable ...

    // Prepare the query vector.
    float* queryVector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        queryVector[i] = (float)rand() / RAND_MAX; // Example data
    }

    // Calculate the size of the ADC distance table and allocate memory.
    // The ADC table stores the distance between the query vector and all cluster centers in each subspace.
    size_t adcTableSize = pqM * pqKsub;
    float* adcDistanceTable = (float*)malloc(adcTableSize * sizeof(float));
    if (adcDistanceTable == NULL) {
        printf("Failed to allocate memory for the ADC distance table.\n");
        free(queryVector);
        free(params.pqTable);
        return -1;
    }

    // Calculate the ADC distance table.
    int ret = GetPQDistanceTableAdc(queryVector, &params, adcDistanceTable, adcTableSize);

    if (ret != 0) {
        printf("Failed to calculate the ADC distance table. Error code: %d\n", ret);
        free(adcDistanceTable);
        free(queryVector);
        free(params.pqTable);
        return -1;
    }

    printf("The ADC distance table is successfully calculated.\n");
    printf(" - Distance table size: %zu\n", adcTableSize);
    printf(" - Distance between the query vector and the center of subspace 0: %f\n", adcDistanceTable[0]);

    //...Use the ADC distance table for subsequent distance calculations ...

    // Free resources.
    free(adcDistanceTable);
    free(queryVector);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistance

**API Definition<a name="section172317194488"></a>**

int GetPQDistance\(const unsigned char \*basecode, const unsigned char \*querycode, const PQParams \*params, const float \*pqDistanceTable, float \*PQDistance, size\_t basecode\_size, size\_t querycode\_size, size\_t pqDistanceTable\_size, size\_t pqDistance\_size\);

**Function<a name="section1153124784912"></a>**

Calculates the PQ ADC or SDC distance. If querycode == NULL, the ADC distance is calculated. If querycode != NULL, the SDC distance is calculated.

**Parameters<a name="section157501312135019"></a>**

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="17.588241175882413%" id="mcps1.1.5.1.1"><p id="p1035755516441"><a name="p1035755516441"></a><a name="p1035755516441"></a><strong id="b535775554413"><a name="b535775554413"></a><a name="b535775554413"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="21.18788121187881%" id="mcps1.1.5.1.2"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a> Data Type</strong></p>
</th>
<th class="cellrowborder" valign="top" width="35.24647535246475%" id="mcps1.1.5.1.3"><p id="p11785165413"><a name="p11785165413"></a><a name="p11785165413"></a><strong id="b177251165410"><a name="b177251165410"></a><a name="b177251165410"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="25.977402259774017%" id="mcps1.1.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row146815169448"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p1563124410561"><a name="p1563124410561"></a><a name="p1563124410561"></a>basecode</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p956394495618"><a name="p956394495618"></a><a name="p956394495618"></a>unsigned char*</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p9755115414"><a name="p9755115414"></a><a name="p9755115414"></a>Quantized base.</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p156334415617"><a name="p156334415617"></a><a name="p156334415617"></a>The value cannot be null.</p>
</td>
</tr>
<tr id="row18468216154410"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p125631744155611"><a name="p125631744155611"></a><a name="p125631744155611"></a>querycode</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p1956313447562"><a name="p1956313447562"></a><a name="p1956313447562"></a>unsigned char*</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p379518542"><a name="p379518542"></a><a name="p379518542"></a>Quantized query.</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p215516591885"><a name="p215516591885"></a><a name="p215516591885"></a>-</p>
</td>
</tr>
<tr id="row746811684410"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p1056334411567"><a name="p1056334411567"></a><a name="p1056334411567"></a>pqDistanceTable</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p11563544205617"><a name="p11563544205617"></a><a name="p11563544205617"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p15835185413"><a name="p15835185413"></a><a name="p15835185413"></a>SDC or ADC distance table.</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p6563174415562"><a name="p6563174415562"></a><a name="p6563174415562"></a>The value cannot be null.</p>
</td>
</tr>
<tr id="row84681167446"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p2563444175617"><a name="p2563444175617"></a><a name="p2563444175617"></a>PQDistance</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p8563164416569"><a name="p8563164416569"></a><a name="p8563164416569"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p118155155413"><a name="p118155155413"></a><a name="p118155155413"></a>SDC or ADC distance.</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p17563744115619"><a name="p17563744115619"></a><a name="p17563744115619"></a>The value cannot be null.</p>
</td>
</tr>
<tr id="row7632211969"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p147365121966"><a name="p147365121966"></a><a name="p147365121966"></a>basecode_size</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p196328113620"><a name="p196328113620"></a><a name="p196328113620"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p6632711166"><a name="p6632711166"></a><a name="p6632711166"></a>Length of the quantized base array.</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p46321611562"><a name="p46321611562"></a><a name="p46321611562"></a>The value is specified by <code>pqM</code>, which is a field in the <code>PQParams</code> structure and indicates the number of subspaces.</p>
</td>
</tr>
<tr id="row7553121017617"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p1173613121166"><a name="p1173613121166"></a><a name="p1173613121166"></a>querycode_size</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p155310101968"><a name="p155310101968"></a><a name="p155310101968"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p135531100620"><a name="p135531100620"></a><a name="p135531100620"></a>Length of the quantized query array.</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p11553151016614"><a name="p11553151016614"></a><a name="p11553151016614"></a>If <code>querycode</code> is not null, the value is specified by <code>pqM</code>, where <code>querycode</code> indicates the quantized query.</p>
</td>
</tr>
<tr id="row13989131111620"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p137361312160"><a name="p137361312160"></a><a name="p137361312160"></a>pqDistanceTable_size</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p159891111464"><a name="p159891111464"></a><a name="p159891111464"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p39890111161"><a name="p39890111161"></a><a name="p39890111161"></a>Length of the SDC or ADC distance table array.</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p189890111611"><a name="p189890111611"></a><a name="p189890111611"></a>If <code>querycode</code> is null, the value is specified by <code>pqM</code> × <code>pqKsub</code>. If <code>querycode</code> is not null, the value is specified by <code>pqM</code> × <code>pqKsub</code> × <code>pqKsub</code>, where <code>querycode</code> indicates the quantized query, <code>pqKsub</code> is a field in the <code>PQParams</code> structure and indicates the number of cluster centroids in the subspaces.</p>
</td>
</tr>
<tr id="row8727198062"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p19736201215610"><a name="p19736201215610"></a><a name="p19736201215610"></a>PQDistance_size</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p20727681562"><a name="p20727681562"></a><a name="p20727681562"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p67271482618"><a name="p67271482618"></a><a name="p67271482618"></a>Length of the SDC or ADC distance array.</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p197271781460"><a name="p197271781460"></a><a name="p197271781460"></a>The value is <code>1</code>.</p>
</td>
</tr>
<tr id="row13649153083811"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p18649930173810"><a name="p18649930173810"></a><a name="p18649930173810"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p1358611261262"><a name="p1358611261262"></a><a name="p1358611261262"></a>const PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p107381649203819"><a name="p107381649203819"></a><a name="p107381649203819"></a>For details, see <a href="#table11706934103516">PQParams field description.</a></p>
</td>
</tr>
</tbody>
</table>

**Return Value<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>Data Type</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>The value <code>0</code> is returned when the system runs properly, and the value <code>-1</code> is returned when the system exits abnormally.</p>
</td>
</tr>
</tbody>
</table>

### Example

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"

int main() {
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // Initialize PQParams (assuming that pqTable has been populated with data).
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = 1;  // L2 distance
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    // ... Assume that pqTable has been filled by calling ComputePQTable ...

    // Prepare the PQ codes of the base and query vectors (assuming that the codes have been obtained by calling ComputeVectorPQCode).
    unsigned char* basecode = (unsigned char*)malloc(pqM);
    unsigned char* querycode = (unsigned char*)malloc(pqM);
    for (int i = 0; i < pqM; i++) {
        basecode[i] = rand() % pqKsub;
        querycode[i] = rand() % pqKsub;
    }

    // Prepare the query vector (for ADC distance calculation).
    float* queryVector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        queryVector[i] = (float)rand() / RAND_MAX;
    }

    float pqDistance = 0.0f;
    int ret;

    // ========== Method 1: Calculate the ADC distance (querycode is NULL) ==========
    // Size of the ADC distance table: pqM * pqKsub
    size_t adcTableSize = pqM * pqKsub;
    float* adcDistanceTable = (float*)malloc(adcTableSize * sizeof(float));
    GetPQDistanceTableAdc(queryVector, &params, adcDistanceTable, adcTableSize);

    ret = GetPQDistance(
        basecode,           // Quantized base
        NULL,               // The querycode is NULL, and the ADC distance is calculated.
        &params,
        adcDistanceTable,
        &pqDistance,
        pqM,                // basecode_size
        0,                  // querycode_size (invalid when querycode is NULL)
        adcTableSize,       // Size of the ADC distance table
        1                  // Size of the output distance array
    );

    if (ret == 0) {
        printf("ADC distance: %f\n", pqDistance);
    }

    // ========== Method 2: Calculate the SDC distance (querycode is not NULL) ==========
    // Size of the SDC distance table: pqM * pqKsub * pqKsub
    size_t sdcTableSize = pqM * pqKsub * pqKsub;
    float* sdcDistanceTable = (float*)malloc(sdcTableSize * sizeof(float));
    GetPQDistanceTableSdc(&params, sdcDistanceTable, sdcTableSize);

    ret = GetPQDistance(
        basecode,           // Quantized base
        querycode,          // If the query code is not NULL, the SDC distance is calculated.
        &params,
        sdcDistanceTable,
        &pqDistance,
        pqM,                // basecode_size
        pqM,                // querycode_size
        sdcTableSize,       // Size of the SDC distance table
        1                   // Size of the output distance array
    );

    if (ret == 0) {
        printf("SDC distance: %f\n", pqDistance);
    }

    // Free resources.
    free(queryVector);
    free(adcDistanceTable);
    free(sdcDistanceTable);
    free(basecode);
    free(querycode);
    free(params.pqTable);

    return 0;
}
```
