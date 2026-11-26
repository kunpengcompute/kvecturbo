# Copyright 2024 Huawei Technologies Co., Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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