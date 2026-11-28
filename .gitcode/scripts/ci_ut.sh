#!/bin/bash
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# kvecturbo is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the Mulan PSL v2 for more details.
set -e
lcov --version
export BINARYLIBS=/opt/buildtools/binarylibs/openGauss-third_party_binarylibs_openEuler_2203_arm
sh build.sh
export LD_LIBRARY_PATH=${BINARYLIBS}/kernel/platform/Huawei_Secure_C/Dynamic_Lib/:$LD_LIBRARY_PATH
export LIBRARY_PATH=${BINARYLIBS}/kernel/platform/Huawei_Secure_C/Dynamic_Lib/:$LIBRARY_PATH
export C_INCLUDE_PATH=${BINARYLIBS}/kernel/platform/Huawei_Secure_C/comm/include/:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=${BINARYLIBS}/kernel/platform/Huawei_Secure_C/comm/include/:$CPLUS_INCLUDE_PATH
pushd test/ut_test
sh test.sh
popd