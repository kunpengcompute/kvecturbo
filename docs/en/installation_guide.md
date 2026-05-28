# Installation Guide

## Verified Environments

**Table 1** Verified environments of KVecTurbo<a id="verified-environments-of-kvecturbo"></a>

<a name="table59918346913"></a>
<table><thead align="left"><tr id="zh-cn_topic_0000002483307829_row1169294312212"><th class="cellrowborder" valign="top" width="21.8%" id="mcps1.2.6.1.1"><p id="zh-cn_topic_0000002483307829_p12692144313211"><a name="zh-cn_topic_0000002483307829_p12692144313211"></a><a name="zh-cn_topic_0000002483307829_p12692144313211"></a>OS</p>
</th>
<th class="cellrowborder" valign="top" width="19.91%" id="mcps1.2.6.1.2"><p id="zh-cn_topic_0000002483307829_p06926438214"><a name="zh-cn_topic_0000002483307829_p06926438214"></a><a name="zh-cn_topic_0000002483307829_p06926438214"></a>CPU</p>
</th>
<th class="cellrowborder" valign="top" width="13.700000000000001%" id="mcps1.2.6.1.3"><p id="zh-cn_topic_0000002483307829_p269284310216"><a name="zh-cn_topic_0000002483307829_p269284310216"></a><a name="zh-cn_topic_0000002483307829_p269284310216"></a>Memory</p>
</th>
<th class="cellrowborder" valign="top" width="17.34%" id="mcps1.2.6.1.4"><p id="zh-cn_topic_0000002483307829_p196922434215"><a name="zh-cn_topic_0000002483307829_p196922434215"></a><a name="zh-cn_topic_0000002483307829_p196922434215"></a>Compiler</p>
</th>
Other <th class="cellrowborder" valign="top" width="27.250000000000004%" id="mcps1.2.6.1.5"><p id="zh-cn_topic_0000002483307829_p1769219435210"><a name="zh-cn_topic_0000002483307829_p1769219435210"></a><a name="zh-cn_topic_0000002483307829_p1769219435210"></a>Remarks</p>
</th>
</tr>
</thead>
<tbody><tr id="zh-cn_topic_0000002483307829_row069394311217"><td class="cellrowborder" valign="top" width="21.8%" headers="mcps1.2.6.1.1 "><p id="zh-cn_topic_0000002483307829_p1490510151227"><a name="zh-cn_topic_0000002483307829_p1490510151227"></a><a name="zh-cn_topic_0000002483307829_p1490510151227"></a>openEuler 22.03 LTS SP3<br>openEuler 20.03 LTS SP4</p>
</td>
<td class="cellrowborder" valign="top" width="19.91%" headers="mcps1.2.6.1.2 "><p id="zh-cn_topic_0000002483307829_p199164284117"><a name="zh-cn_topic_0000002483307829_p199164284117"></a><a name="zh-cn_topic_0000002483307829_p199164284117"></a>New Kunpeng 920 processor model</p>
</td>
<td class="cellrowborder" valign="top" width="13.700000000000001%" headers="mcps1.2.6.1.3 "><p id="zh-cn_topic_0000002483307829_p1859394516475"><a name="zh-cn_topic_0000002483307829_p1859394516475"></a><a name="zh-cn_topic_0000002483307829_p1859394516475"></a>16 × 32 GB</p>
</td>
<td class="cellrowborder" valign="top" width="17.34%" headers="mcps1.2.6.1.4 "><p id="zh-cn_topic_0000002483307829_p16693164362119"><a name="zh-cn_topic_0000002483307829_p16693164362119"></a><a name="zh-cn_topic_0000002483307829_p16693164362119"></a>GCC 10.3.1</p>
</td>
<td class="cellrowborder" valign="top" width="27.250000000000004%" headers="mcps1.2.6.1.5 "><p id="zh-cn_topic_0000002483307829_p8852457817"><a name="zh-cn_topic_0000002483307829_p8852457817"></a><a name="zh-cn_topic_0000002483307829_p8852457817"></a>CMake&gt;=3.22.0</p>
</td>
</tr>
</tbody>
</table>

## Compiling KVecTurbo

Obtain the KVecTurbo open-source code from GitCode, install the required dependencies, and then compile KVecTurbo.

1. Obtain the KVecTurbo open-source code. The tag is `v1.1.0`. Assume that the code is stored in `/path/to/kvecturbo`.

    ```bash
    git clone --branch v1.1.0 https://gitcode.com/boostkit/kvecturbo.git
    ```

2. Install GCC 10.3, OpenMP, CMake, and Make.

    ```bash
    yum install gcc g++ cmake libgomp make
    ```

3. KVecTurbo depends on the openEuler third-party library `Huawei_Secure_C`. Obtain the software archive and decompress it. Assume that the directory is `/path/to/binarylibs`.

    ```bash
    cd /path/to/binarylibs
    wget https://opengauss.obs.cn-south-1.myhuaweicloud.com/latest/binarylibs/gcc10.3/openGauss-third_party_binarylibs_openEuler_2203_arm.tar.gz --no-check-certificate
    tar -zxvf openGauss-third_party_binarylibs_openEuler_2203_arm.tar.gz
    ```

4. Compile KVecTurbo.

    ```bash
    export BINARYLIBS=/path/to/binarylibs/openGauss-third_party_binarylibs_openEuler_2203_arm
    export CPLUS_INCLUDE_PATH=${BINARYLIBS}/kernel/platform/Huawei_Secure_C/comm/include/:$CPLUS_INCLUDE_PATH
    cd /path/to/kvecturbo
    sh build.sh
    ```

    The generated dynamic library file is `libkvecturbo.so`. `_xxxx_` is stored in the `out/lib` folder, and the header file is stored in the `out/include` folder. `_xxxx_` indicates the version number.
