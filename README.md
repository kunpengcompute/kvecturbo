# KVecTurbo介绍

## 什么是KVecTurbo
KVecTurbo是鲲鹏自研的向量检索加速组件，对接openGauss向量数据库使用。KVecTurbo通过将高维向量量化压缩，快速获取query的近邻，同时使用SIMD指令集加速距离计算，用于多维向量最近邻搜索。
KRL适用于鲲鹏920新型号处理器，支持NEON指令（128位宽）和SVE指令（256位宽）。

## 接口说明

<table>
    <tr>
        <td>接口名称</td>
        <td>接口作用 </td>
    </tr>
    <tr>
        <td>ComputePQTable</td>
        <td>计算PQ码本。 </td>
    </tr>
    <tr>
        <td>ComputeVectorPQCode</td>
        <td>根据PQ码本，量化输入向量。 </td>
    </tr>
    <tr>
        <td>GetPQDistanceTableSdc</td>
        <td>计算PQ SDC距离表，即计算各个子空间内聚类中心之间的距离。 </td>
    </tr>
    <tr>
        <td>GetPQDistanceTableAdc</td>
        <td>计算PQ ADC距离表，即计算查询向量和各个子空间内聚类中心的距离。 </td>
    </tr>
    <tr>
        <td>GetPQDistance</td>
        <td>计算PQ ADC或SDC距离。若querycode == NULL，计算的是ADC距离；若querycode != NULL，计算的是SDC距离。 </td>
    </tr>
    
</table>

## 安装说明

### 已验证环境

<table>
    <tr>
        <th>操作系统</th>
        <th>CPU类型</th>
        <th>内存</th>
        <th>编译器</th>
        <th>其他依赖</th>
    </tr>
    <tr>
        <td rowspan="1">openEuler 22.03 LTS SP4</td>
        <td rowspan="3">鲲鹏920新型号处理器</td>
        <td rowspan="3">16 * 32G</td>
        <td rowspan="3">GCC 10.3.1</td>
        <td rowspan="3">CMake&gt;=3.22.0</td>
    </tr>
    <tr></tr>
    <tr>
        <td rowspan="1">openEuler 20.03 LTS SP3</td>
    </tr>
</table>


### 源码编译

- 安装环境依赖。

```sh
yum install gcc cmake libgomp
```
- KVecTurbo依赖openEuler第三方库Huawei_Secure_C，获取软件包并解压。假设存放路径为`/path/to/binarylibs`。

```sh
cd /path/to/binarylibs
wget https://opengauss.obs.cn-south-1.myhuaweicloud.com/latest/binarylibs/gcc10.3/openGauss-third_party_binarylibs_openEuler_2203_arm.tar.gz --no-check-certificate
tar -zxvf openGauss-third_party_binarylibs_openEuler_2203_arm.tar.gz
```
- 执行编译。
假设仓库源代码存放于`/path/to/KVecTurbo`，通过源码编译得到libkvecturbo.so。生成的so位于`/path/to/KVecTurbo/out/lib`目录下。

```sh
export BINARYLIBS=/path/to/binarylibs/openGauss-third_party_binarylibs_openEuler_2203_arm
export CPLUS_INCLUDE_PATH=${BINARYLIBS}/kernel/platform/Huawei_Secure_C/comm/include/:$CPLUS_INCLUDE_PATH
cd /path/to/kvecturbo
sh build.sh
```

## 使用说明

### 测试示例
KVecTurbo量化算法可对接openGauss（7.0.0 RC1及后续版本）数据库使用，提高HNSW（Hierarchical Navigable Small World）图算法的性能。
openGauss社区文档中心提供了KVecTurbo量化算法使用示例可供参考。
- 安装openGauss。
请参见[《openGauss极简版安装教程》](https://docs.opengauss.org/zh/docs/latest/docs/InstallationGuide/%E6%9E%81%E7%AE%80%E7%89%88%E5%AE%89%E8%A3%85.html)进行安装。

- 使用openGauss DataVec向量数据库。
请参见[《DataVec向量数据库快速入门》](https://docs.opengauss.org/zh/docs/latest/docs/DataVec/DataVec-quickstart.html)使用，其中从向量索引创建章节开始请跳转下一步使用。

- 使用KVecTurbo算法。
请参见[《PQ特性》](https://docs.opengauss.org/zh/docs/latest/docs/DataVec/PQ.html)使用。