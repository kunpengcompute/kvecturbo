# 安装指南

本文档为KVecTurbo安装指南，介绍已验证环境配置、依赖安装和编译步骤，适用于需要安装KVecTurbo的用户。

## 已验证环境

**表 1** KVecTurbo已验证环境<a id="KVecTurbo已验证环境"></a>

| 操作系统 | CPU类型 | 内存 | 编译器 | 其他 |
| --- | --- | --- | --- | --- |
| openEuler 22.03 LTS SP3；openEuler 20.03 LTS SP4 | 鲲鹏920 7282C处理器 | 16 * 32GB | GCC 10.3.1 | CMake 3.22.0及以上版本 |

## 编译KVecTurbo

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

## 修订记录

|文档版本|发布日期|修改说明|
|--|--|--|
|01|2025-09-30|第一次正式发布。|
