# 安装指南<a name="ZH-CN_TOPIC_0000002553561419"></a>

## 已验证环境<a name="ZH-CN_TOPIC_0000002553561323"></a>

**表 1** KVecturbo已验证环境<a id="KVecturbo已验证环境"></a>

<a name="table59918346913"></a>
<table><thead align="left"><tr id="zh-cn_topic_0000002483307829_row1169294312212"><th class="cellrowborder" valign="top" width="21.8%" id="mcps1.2.6.1.1"><p id="zh-cn_topic_0000002483307829_p12692144313211"><a name="zh-cn_topic_0000002483307829_p12692144313211"></a><a name="zh-cn_topic_0000002483307829_p12692144313211"></a>操作系统</p>
</th>
<th class="cellrowborder" valign="top" width="19.91%" id="mcps1.2.6.1.2"><p id="zh-cn_topic_0000002483307829_p06926438214"><a name="zh-cn_topic_0000002483307829_p06926438214"></a><a name="zh-cn_topic_0000002483307829_p06926438214"></a>CPU类型</p>
</th>
<th class="cellrowborder" valign="top" width="13.700000000000001%" id="mcps1.2.6.1.3"><p id="zh-cn_topic_0000002483307829_p269284310216"><a name="zh-cn_topic_0000002483307829_p269284310216"></a><a name="zh-cn_topic_0000002483307829_p269284310216"></a>内存</p>
</th>
<th class="cellrowborder" valign="top" width="17.34%" id="mcps1.2.6.1.4"><p id="zh-cn_topic_0000002483307829_p196922434215"><a name="zh-cn_topic_0000002483307829_p196922434215"></a><a name="zh-cn_topic_0000002483307829_p196922434215"></a>编译器</p>
</th>
<th class="cellrowborder" valign="top" width="27.250000000000004%" id="mcps1.2.6.1.5"><p id="zh-cn_topic_0000002483307829_p1769219435210"><a name="zh-cn_topic_0000002483307829_p1769219435210"></a><a name="zh-cn_topic_0000002483307829_p1769219435210"></a>其他</p>
</th>
</tr>
</thead>
<tbody><tr id="zh-cn_topic_0000002483307829_row069394311217"><td class="cellrowborder" valign="top" width="21.8%" headers="mcps1.2.6.1.1 "><p id="zh-cn_topic_0000002483307829_p1490510151227"><a name="zh-cn_topic_0000002483307829_p1490510151227"></a><a name="zh-cn_topic_0000002483307829_p1490510151227"></a>openEuler 22.03 LTS SP3</p>
</td>
<td class="cellrowborder" valign="top" width="19.91%" headers="mcps1.2.6.1.2 "><p id="zh-cn_topic_0000002483307829_p199164284117"><a name="zh-cn_topic_0000002483307829_p199164284117"></a><a name="zh-cn_topic_0000002483307829_p199164284117"></a>鲲鹏920 7282C处理器</p>
</td>
<td class="cellrowborder" valign="top" width="13.700000000000001%" headers="mcps1.2.6.1.3 "><p id="zh-cn_topic_0000002483307829_p1859394516475"><a name="zh-cn_topic_0000002483307829_p1859394516475"></a><a name="zh-cn_topic_0000002483307829_p1859394516475"></a>16 * 32GB</p>
</td>
<td class="cellrowborder" valign="top" width="17.34%" headers="mcps1.2.6.1.4 "><p id="zh-cn_topic_0000002483307829_p16693164362119"><a name="zh-cn_topic_0000002483307829_p16693164362119"></a><a name="zh-cn_topic_0000002483307829_p16693164362119"></a>GCC 10.3.1</p>
</td>
<td class="cellrowborder" valign="top" width="27.250000000000004%" headers="mcps1.2.6.1.5 "><p id="zh-cn_topic_0000002483307829_p8852457817"><a name="zh-cn_topic_0000002483307829_p8852457817"></a><a name="zh-cn_topic_0000002483307829_p8852457817"></a>CMake&gt;=3.22.0</p>
</td>
</tr>
<tr id="zh-cn_topic_0000002483307829_row1915713414447"><td class="cellrowborder" valign="top" width="21.8%" headers="mcps1.2.6.1.1 "><p id="zh-cn_topic_0000002483307829_p11394750164417"><a name="zh-cn_topic_0000002483307829_p11394750164417"></a><a name="zh-cn_topic_0000002483307829_p11394750164417"></a>openEuler 20.03 LTS SP4</p>
</td>
<td class="cellrowborder" valign="top" width="19.91%" headers="mcps1.2.6.1.2 "><p id="p778074410122"><a name="p778074410122"></a><a name="p778074410122"></a>鲲鹏920 7282C处理器</p>
</td>
<td class="cellrowborder" valign="top" width="13.700000000000001%" headers="mcps1.2.6.1.3 "><p id="p1239184911121"><a name="p1239184911121"></a><a name="p1239184911121"></a>16 * 32GB</p>
</td>
<td class="cellrowborder" valign="top" width="17.34%" headers="mcps1.2.6.1.4 "><p id="p0854125515122"><a name="p0854125515122"></a><a name="p0854125515122"></a>GCC 10.3.1</p>
</td>
<td class="cellrowborder" valign="top" width="27.250000000000004%" headers="mcps1.2.6.1.5 "><p id="p1187940131316"><a name="p1187940131316"></a><a name="p1187940131316"></a>CMake&gt;=3.22.0</p>
</td>
</tr>
</tbody>
</table>

## 编译KVecTurbo<a name="ZH-CN_TOPIC_0000002553681205"></a>

从GitCode获取KVecTurbo开源代码，安装必要的依赖工具后编译KVecTurbo。

1. 获取KVecTurbo开源代码，标签为**v1.1.0**。假设代码存放于“/path/to/kvecturbo“。

    ```bash
    git clone --branch v1.1.0 https://gitcode.com/boostkit/kvecturbo.git
    ```

2. 安装GCC 10.3、OpenMP、CMake、Make。

    ```bash
    yum install gcc g++ cmake libgomp make
    ```

3. KVecTurbo依赖openEuler第三方库Huawei\_Secure\_C，获取软件包并解压。假设存放路径为“/path/to/binarylibs“。

    ```bash
    cd /path/to/binarylibs
    wget https://opengauss.obs.cn-south-1.myhuaweicloud.com/latest/binarylibs/gcc10.3/openGauss-third_party_binarylibs_openEuler_2203_arm.tar.gz --no-check-certificate
    tar -zxvf openGauss-third_party_binarylibs_openEuler_2203_arm.tar.gz
    ```

4. 编译KVecTurbo。

    ```bash
    export BINARYLIBS=/path/to/binarylibs/openGauss-third_party_binarylibs_openEuler_2203_arm
    export CPLUS_INCLUDE_PATH=${BINARYLIBS}/kernel/platform/Huawei_Secure_C/comm/include/:$CPLUS_INCLUDE_PATH
    cd /path/to/kvecturbo
    sh build.sh
    ```

    生成的动态库文件libkvecturbo.so. **_xxxx_** 位于“out/lib“文件夹下，头文件位于“out/include“文件夹下。其中 **_xxxx_** 表示版本号。
