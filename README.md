# 项目介绍<a name="ZH-CN_TOPIC_0000002476052341"></a>

KVecTurbo是鲲鹏自研的向量检索加速组件，对接openGauss向量数据库使用。KVecTurbo通过将高维向量量化压缩，快速获取query的近邻，同时使用SIMD指令集加速距离计算，用于多维向量最近邻搜索。

KVecTurbo适用于鲲鹏920 7282C处理器，支持NEON指令（128位宽）。

# 环境部署<a name="ZH-CN_TOPIC_0000002442695624"></a>



## 已验证环境<a name="ZH-CN_TOPIC_0000002476055617"></a>

<a name="table1913120528271"></a>
<table><thead align="left"><tr id="row1113114528275"><th class="cellrowborder" valign="top" width="20%" id="mcps1.1.6.1.1"><p id="p131317527275"><a name="p131317527275"></a><a name="p131317527275"></a>操作系统</p>
</th>
<th class="cellrowborder" valign="top" width="20%" id="mcps1.1.6.1.2"><p id="p1613114528270"><a name="p1613114528270"></a><a name="p1613114528270"></a>CPU类型</p>
</th>
<th class="cellrowborder" valign="top" width="20%" id="mcps1.1.6.1.3"><p id="p51311452102718"><a name="p51311452102718"></a><a name="p51311452102718"></a>内存</p>
</th>
<th class="cellrowborder" valign="top" width="20%" id="mcps1.1.6.1.4"><p id="p12131185218275"><a name="p12131185218275"></a><a name="p12131185218275"></a>编译器</p>
</th>
<th class="cellrowborder" valign="top" width="20%" id="mcps1.1.6.1.5"><p id="p113118527276"><a name="p113118527276"></a><a name="p113118527276"></a>其他依赖</p>
</th>
</tr>
</thead>
<tbody><tr id="row151311552122719"><td class="cellrowborder" valign="top" width="20%" headers="mcps1.1.6.1.1 "><p id="p1896879284"><a name="p1896879284"></a><a name="p1896879284"></a>openEuler 22.03 LTS SP3</p>
</td>
<td class="cellrowborder" rowspan="2" valign="top" width="20%" headers="mcps1.1.6.1.2 "><p id="p0896478288"><a name="p0896478288"></a><a name="p0896478288"></a>鲲鹏920 7282C处理器</p>
<p id="p14131105272718"><a name="p14131105272718"></a><a name="p14131105272718"></a></p>
</td>
<td class="cellrowborder" rowspan="2" valign="top" width="20%" headers="mcps1.1.6.1.3 "><p id="p1489612782811"><a name="p1489612782811"></a><a name="p1489612782811"></a>16 * 32G</p>
<p id="p2131052152710"><a name="p2131052152710"></a><a name="p2131052152710"></a></p>
</td>
<td class="cellrowborder" rowspan="2" valign="top" width="20%" headers="mcps1.1.6.1.4 "><p id="p1389619711289"><a name="p1389619711289"></a><a name="p1389619711289"></a>GCC 10.3.1</p>
<p id="p61311952162717"><a name="p61311952162717"></a><a name="p61311952162717"></a></p>
</td>
<td class="cellrowborder" rowspan="2" valign="top" width="20%" headers="mcps1.1.6.1.5 "><p id="p3896871288"><a name="p3896871288"></a><a name="p3896871288"></a>CMake&gt;=3.22.0</p>
<p id="p913115526277"><a name="p913115526277"></a><a name="p913115526277"></a></p>
</td>
</tr>
<tr id="row41311552102717"><td class="cellrowborder" valign="top" headers="mcps1.1.6.1.1 "><p id="p913145220273"><a name="p913145220273"></a><a name="p913145220273"></a>openEuler 20.03 LTS SP4</p>
</td>
</tr>
</tbody>
</table>

## 源码编译<a name="ZH-CN_TOPIC_0000002442855500"></a>

1.  安装环境依赖。

    ```
    yum install gcc cmake libgomp
    ```

2.  获取KVecTurbo依赖的openEuler第三方库Huawei\_Secure\_C软件包并解压。假设存放路径为“/path/to/binarylibs“。

    ```
    cd /path/to/binarylibs
    wget https://opengauss.obs.cn-south-1.myhuaweicloud.com/latest/binarylibs/gcc10.3/openGauss-third_party_binarylibs_openEuler_2203_arm.tar.gz --no-check-certificate
    tar -zxvf openGauss-third_party_binarylibs_openEuler_2203_arm.tar.gz
    ```

3.  执行编译。 假设仓库源代码存放于/path/to/kvecturbo，通过源码编译得到libkvecturbo.so。生成的so位于/path/to/kvecturbo/out/lib目录下。

    ```
    export BINARYLIBS=/path/to/binarylibs/openGauss-third_party_binarylibs_openEuler_2203_arm
    cd /path/to/kvecturbo
    sh build.sh
    ```

# 快速上手<a name="ZH-CN_TOPIC_0000002476135421"></a>




## UT测试（可选）<a name="ZH-CN_TOPIC_0000002442695628"></a>

执行下方指令，用于看护编译及运行环境是否正常，函数功能是否正确。

```
cd /path/to/kvecturbo/test/ut_test
sh test.sh
```

## 使用示例<a name="ZH-CN_TOPIC_0000002476055621"></a>

KVecTurbo量化算法可对接openGauss（7.0.0 RC1及后续版本）数据库使用，提高HNSW（Hierarchical Navigable Small World）图算法的性能。 openGauss社区文档中心提供了KVecTurbo量化算法使用示例可供参考。

1.  安装openGauss。请参见《[openGauss极简版安装教程](https://docs.opengauss.org/zh/docs/latest/docs/InstallationGuide/%E6%9E%81%E7%AE%80%E7%89%88%E5%AE%89%E8%A3%85.html)》进行安装。
2.  使用openGauss DataVec向量数据库。请参见《[DataVec向量数据库快速入门](https://docs.opengauss.org/zh/docs/latest/docs/DataVec/DataVec-quickstart.html)》使用，其中从**向量索引创建**章节开始请跳转步骤[3](#li19663161713104)。
3.  使用KVecTurbo算法。请参见《[PQ特性](https://docs.opengauss.org/zh/docs/latest/docs/DataVec/PQ.html)》使用。

## API参考<a name="ZH-CN_TOPIC_0000002442855504"></a>

<a name="table1455031553915"></a>
<table><thead align="left"><tr id="row1551191513391"><th class="cellrowborder" valign="top" width="34.260000000000005%" id="mcps1.1.3.1.1"><p id="p4551151511399"><a name="p4551151511399"></a><a name="p4551151511399"></a>接口名称</p>
</th>
<th class="cellrowborder" valign="top" width="65.74%" id="mcps1.1.3.1.2"><p id="p1355112154395"><a name="p1355112154395"></a><a name="p1355112154395"></a>接口作用</p>
</th>
</tr>
</thead>
<tbody><tr id="row1855121518399"><td class="cellrowborder" valign="top" width="34.260000000000005%" headers="mcps1.1.3.1.1 "><p id="p175614110399"><a name="p175614110399"></a><a name="p175614110399"></a>ComputePQTable</p>
</td>
<td class="cellrowborder" valign="top" width="65.74%" headers="mcps1.1.3.1.2 "><p id="p45664183913"><a name="p45664183913"></a><a name="p45664183913"></a>计算PQ码本。</p>
</td>
</tr>
<tr id="row15551201533910"><td class="cellrowborder" valign="top" width="34.260000000000005%" headers="mcps1.1.3.1.1 "><p id="p15649104420393"><a name="p15649104420393"></a><a name="p15649104420393"></a>ComputeVectorPQCode</p>
</td>
<td class="cellrowborder" valign="top" width="65.74%" headers="mcps1.1.3.1.2 "><p id="p6649744133912"><a name="p6649744133912"></a><a name="p6649744133912"></a>根据PQ码本，量化输入向量。</p>
</td>
</tr>
<tr id="row9551181563910"><td class="cellrowborder" valign="top" width="34.260000000000005%" headers="mcps1.1.3.1.1 "><p id="p16630174820393"><a name="p16630174820393"></a><a name="p16630174820393"></a>GetPQDistanceTableSdc</p>
</td>
<td class="cellrowborder" valign="top" width="65.74%" headers="mcps1.1.3.1.2 "><p id="p1763024815395"><a name="p1763024815395"></a><a name="p1763024815395"></a>计算PQ SDC距离表，即计算各个子空间内聚类中心之间的距离。</p>
</td>
</tr>
<tr id="row255110155390"><td class="cellrowborder" valign="top" width="34.260000000000005%" headers="mcps1.1.3.1.1 "><p id="p1152117529398"><a name="p1152117529398"></a><a name="p1152117529398"></a>GetPQDistanceTableAdc</p>
</td>
<td class="cellrowborder" valign="top" width="65.74%" headers="mcps1.1.3.1.2 "><p id="p1521135215395"><a name="p1521135215395"></a><a name="p1521135215395"></a>计算PQ ADC距离表，即计算查询向量和各个子空间内聚类中心的距离。</p>
</td>
</tr>
<tr id="row14551315123913"><td class="cellrowborder" valign="top" width="34.260000000000005%" headers="mcps1.1.3.1.1 "><p id="p1021713569395"><a name="p1021713569395"></a><a name="p1021713569395"></a>GetPQDistance</p>
</td>
<td class="cellrowborder" valign="top" width="65.74%" headers="mcps1.1.3.1.2 "><p id="p2051813513408"><a name="p2051813513408"></a><a name="p2051813513408"></a>计算PQ ADC或SDC距离。若querycode == NULL，计算的是ADC距离；若querycode != NULL，计算的是SDC距离。</p>
</td>
</tr>
</tbody>
</table>

# 贡献指南<a name="ZH-CN_TOPIC_0000002476135425"></a>

如果使用过程中有任何问题，或者需要反馈特性需求和bug报告，可以提交issues联系我们，具体贡献方法可参考[这里](https://gitcode.com/boostkit/community/blob/master/docs/contributor/contributing.md)。

# 免责声明<a name="ZH-CN_TOPIC_0000002442695632"></a>

此代码仓计划参与OpenGauss社区开源，仅作用于向量检索加速，编码风格遵照原生开源软件，继承原生开源软件安全设计，不破坏原生开源软件设计及编码风格和方式，软件的任何漏洞与安全问题，均由相应的上游社区根据其漏洞和安全响应机制解决。请密切关注上游社区发布的通知和版本更新。鲲鹏计算社区对软件的漏洞及安全问题不承担任何责任。

# 许可证书<a name="ZH-CN_TOPIC_0000002476055625"></a>

KVecTurbo采用 Apache 2.0 License 许可证授权，支持修改代码和再开源。

