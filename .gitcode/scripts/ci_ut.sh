#!/bin/bash
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