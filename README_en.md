# Introduction to KVecTurbo

## Latest Updates

- [2025.09.30]: Added support for datasets with over ten million base vectors
- [2025.03.30]: Introduced KVecTurbo, a vector retrieval acceleration component developed by Kunpeng. It works with the openGauss vector database. It quantizes and compresses high-dimensional vectors to quickly obtain the near neighbors of a query, and uses the SIMD instructions to accelerate distance calculation.

## Project Introduction

KVecTurbo is a proprietary vector retrieval acceleration component and can work with the openGauss vector database. It quantifies and compresses high-dimensional vectors to quickly obtain the near neighbors of a query. In addition, KVecTurbo uses the SIMD instructions to accelerate distance calculation for multidimensional vector nearest neighbor search.

KVecTurbo is applicable to Kunpeng 920 new model processor and supports NEON instructions (128-bit width).

## Directory Structure

The full directory structure of the KVecTurbo open-source repository is as follows:

```text
kvecturbo
├── include
│   └── kvecturbo.h          // Public APIs, structures, and macro definitions
├── src
│   └── kvecturbo.cpp        // K-means, PQ encoding/search, and SIMD acceleration
├── test                     // Unit test (UT)
└── docs
 ├──en
   ├── public_sys-resources
   ├── api_reference.md             // API reference
   ├── installation_guide.md        // Installation guide
   ├── quick_start.md               // Quick start
   ├── release_notes.md             // Release notes
 └── LICENSE
```

## Release Notes

[Release Notes](./docs/en/release_notes.md) provides details about the version updates of KVecTurbo.

## Documents

<table>
<thead align="left">
<tr id="row1291816372202">
<th class="cellrowborder" valign="top" width="9.780978097809781%" id="mcps1.1.4.1.1"><p id="p291823714205">Resource Type</p></th>
<th class="cellrowborder" valign="top" width="17.64176417641764%" id="mcps1.1.4.1.2"><p id="p13918183762016">Resource Name</p></th>
<th class="cellrowborder" valign="top" width="72.57725772577258%" id="mcps1.1.4.1.3"><p id="p89181437152019">Resource Description</p></th>
</tr>
</thead>
<tbody>
<tr id="row179181137112015">
<td class="cellrowborder" valign="top" width="9.780978097809781%" headers="mcps1.1.4.1.1"><p id="p1918123710208">Document</p></td>
<td class="cellrowborder" valign="top" width="17.64176417641764%" headers="mcps1.1.4.1.2"><p id="p2091893722011"><a href="./docs/en/release_notes.md">Release Notes</a></p></td>
<td class="cellrowborder" valign="top" width="72.57725772577258%" headers="mcps1.1.4.1.3"><p id="p491893752010">Provides basic information and feature updates for each KVecTurbo version.</p></td>
</tr>
<tr id="row939116371143">
<td class="cellrowborder" valign="top" width="9.780978097809781%" headers="mcps1.1.4.1.1"><p id="p1039163711413">Document</p></td>
<td class="cellrowborder" valign="top" width="17.64176417641764%" headers="mcps1.1.4.1.2"><p id="p03913372046"><a href="./docs/en/quick_start.md">Quick Start</a></p></td>
<td class="cellrowborder" valign="top" width="72.57725772577258%" headers="mcps1.1.4.1.3"><p id="p1139217371746">Provides guidance for getting started with KVecTurbo.</p></td>
</tr>
<tr id="row2918153732017">
<td class="cellrowborder" valign="top" width="9.780978097809781%" headers="mcps1.1.4.1.1"><p id="p598512211214">Document</p></td>
<td class="cellrowborder" valign="top" width="17.64176417641764%" headers="mcps1.1.4.1.2"><p id="p17918337172020"><a href="./docs/en/installation_guide.md">Installation Guide</a></p></td>
<td class="cellrowborder" valign="top" width="72.57725772577258%" headers="mcps1.1.4.1.3"><p id="p15918183742018">Provides guidance for compiling and installing KVecTurbo.</p></td>
</tr>
<tr id="row12311255193916">
<td class="cellrowborder" valign="top" width="9.780978097809781%" headers="mcps1.1.4.1.1"><p id="p1176012581392">Document</p></td>
<td class="cellrowborder" valign="top" width="17.64176417641764%" headers="mcps1.1.4.1.2"><p id="p13760358183920"><a href="./docs/en/api_reference.md">API Reference</a></p></td>
<td class="cellrowborder" valign="top" width="72.57725772577258%" headers="mcps1.1.4.1.3"><p id="p1776019584395">Provides definitions and descriptions of KVecTurbo APIs.</p></td>
</tr>
</tbody>
</table>

## Disclaimer

This code repository contributes to the openGauss community's open-source projects solely for vector retrieval acceleration. It strictly adheres to the coding style and methods, as well as security design of the native open-source software. Any vulnerability and security issues of the software shall be resolved by the corresponding upstream communities according to their response mechanisms. Please pay attention to the notifications and version updates released by the upstream communities. The Kunpeng computing community does not assume any responsibility for software vulnerabilities and security issues.

## License

KVecTurbo is licensed under the Apache 2.0 license, which allows modification and redistribution of derivative works as open source. For details, see [LICENSE](./docs/LICENSE).

The documents of this project are licensed under CC-BY 4.0. For details, see [LICENSE](./docs/LICENSE).

## Contribution Statement

We welcome your contributions to the community. If you have any questions/suggestions or want to provide feedback on feature requirements and bug reports, you can submit [issues](https://gitcode.com/boostkit/community/blob/master/docs/contributor/issue-submit.md). For details, see [Contribution Guideline](https://gitcode.com/boostkit/community/blob/master/docs/contributor/contributing.md). You are also welcome to share insights in the [Discussions](https://gitcode.com/boostkit/community/discussions). Thank you for your support.

## Acknowledgments

Thank you to everyone in the community for your PRs. We warmly welcome contributions to KVecTurbo!
