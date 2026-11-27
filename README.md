# KVecTurbo介绍

简体中文|[English](./README_en.md)

本文档介绍KVecTurbo，支持千万以上底库向量，通过将高维向量量化压缩，快速获取query的近邻，同时使用SIMD指令集加速距离计算，适用于多维向量最近邻搜索的用户。

## 最新消息

- \[2025-09-30\]：新增支持千万以上底库向量。
- \[2025-03-30\]：新增鲲鹏自研的向量检索加速组件KVecTurbo，对接openGauss向量数据库使用。将高维向量量化压缩，快速获取query的近邻，同时使用SIMD指令集加速距离计算。

## 项目介绍

KVecTurbo是鲲鹏自研的向量检索加速组件，可对接openGauss向量数据库使用。KVecTurbo通过将高维向量量化压缩，快速获取query的近邻，同时使用SIMD指令集加速距离计算，用于多维向量最近邻搜索。

KVecTurbo适用于鲲鹏920 7282C处理器，支持NEON指令（128位宽）。

## 目录结构

KVecTurbo开源仓项目全量目录层级介绍如下：

```text
kvecturbo
├── include
│   └── kvecturbo.h          // 对外声明的API、结构体、宏定义
├── src
│   └── kvecturbo.cpp        // K‑means、PQ编码/搜索、SIMD加速等
├── test                     // ut测试
└── docs
 ├──zh
   ├── public_sys-resources
   ├── api_reference.md             // API参考
   ├── installation_guide.md        // 安装指南
   ├── quick_start.md               // 快速上手
   ├── release_notes.md             // 版本说明书
└── LICENSE
```

## 版本说明

关于KVecTurbo的版本更新情况请参见《[版本说明书](./docs/zh/release_notes.md)》。

## 学习文档

| 学习资源名称 | 学习资源简介 |
| --- | --- |
| 《[版本说明书](./docs/zh/release_notes.md)》 | 提供KVecTurbo每个发布版本的基础信息和特性更新信息。 |
| 《[快速入门](./docs/zh/quick_start.md)》 | 提供KVecTurbo快速入门指导。 |
| 《[安装指南](./docs/zh/installation_guide.md)》 | 提供KVecTurbo编译安装方法指导。 |
| 《[API参考](./docs/zh/api_reference.md)》 | 提供KVecTurbo的API接口定义和接口说明。 |

## 免责声明

此代码仓计划参与OpenGauss社区开源，仅作用于向量检索加速，编码风格遵照开源软件，继承开源软件安全设计，不破坏开源软件设计及编码风格和方式，软件的任何漏洞与安全问题，均由相应的上游社区根据其漏洞和安全响应机制解决。请密切关注上游社区发布的通知和版本更新。鲲鹏计算社区对软件的漏洞及安全问题不承担任何责任。

## License

KVecTurbo采用Mulan PSL v2许可证授权，支持修改代码和再开源，具体请参见[LICENSE](./LICENSE)文件。

本项目的文档适用CC-BY 4.0许可证，具体请参见[LICENSE](./docs/LICENSE)文件。

## 贡献声明

欢迎大家为社区做贡献，如果使用过程中有任何问题/建议，或者需要反馈特性需求和bug报告，可以提交[Issues](https://gitcode.com/boostkit/community/blob/master/docs/contributor/issue-submit.md)联系我们，具体贡献方法可参考[贡献指南](https://gitcode.com/boostkit/community/blob/master/docs/contributor/contributing.md)。同时也欢迎大家在[讨论专区](https://gitcode.com/boostkit/community/discussions)展开讨论交流。感谢您的支持。

## 致谢

感谢来自社区的每一个PR，欢迎贡献KVecTurbo！
