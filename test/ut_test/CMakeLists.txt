cmake_minimum_required(VERSION 3.22)

# 项目名称
project(KVecturboTest)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)

# 获取openEuler第三方库
set(BINARYLIBS_PATH "$ENV{BINARYLIBS}")

# 查找 OpenMP 包
find_package(OpenMP REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/../../include)

# 添加源代码文件
add_executable(test_main test.cpp ${PROJECT_SOURCE_DIR}/../../src/kvecturbo.cpp)

# 查找 GTest 包
find_package(GTest REQUIRED)

enable_testing()

target_compile_options(test_main PRIVATE
    -fprofile-arcs      # 启用代码覆盖率
    -ftest-coverage     # 启用代码覆盖率
)

# 链接gtest库
target_link_libraries(test_main PRIVATE ${OpenMP_CXX_LIBRARIES} gtest gtest_main gcov -L${BINARYLIBS_PATH}/kernel/platform/Huawei_Secure_C/comm/lib/ -lsecurec)