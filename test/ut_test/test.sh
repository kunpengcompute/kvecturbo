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