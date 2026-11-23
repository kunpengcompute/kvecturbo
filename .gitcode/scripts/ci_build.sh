#!/bin/bash
set -e
lcov --version
export BINARYLIBS=/opt/buildtools/binarylibs/openGauss-third_party_binarylibs_openEuler_2203_arm
sh build.sh
