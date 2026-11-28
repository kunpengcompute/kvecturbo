# Copyright (c) 2024 Huawei Technologies Co., Ltd.
# kvecturbo is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the Mulan PSL v2 for more details.

rm -rf build
mkdir build

cd build
cmake ..
cmake --build .
./test_main --gtest_output=xml:./

cd ../
rm  coverage.info
rm -r coverage_report
lcov --directory ./build/CMakeFiles/test_main.dir/ --capture --output-file coverage.info --rc lcov_branch_coverage=1
lcov --remove coverage.info '*gcc*' '*10.3.1*' '*gtest*' '*test*' --output-file coverage.info --rc lcov_branch_coverage=1
genhtml coverage.info --output-directory coverage_report --rc lcov_branch_coverage=1