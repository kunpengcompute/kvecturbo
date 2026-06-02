# 添加共享库kvecturbo，包含kvecturbo.cpp
add_library(kvecturbo SHARED src/kvecturbo.cpp)

# 获取openEuler第三方库
set(BINARYLIBS_PATH "$ENV{BINARYLIBS}")

# 查找并使用OpenMP
find_package(OpenMP REQUIRED)

target_include_directories(kvecturbo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${BINARYLIBS_PATH}/kernel/platform/Huawei_Secure_C/comm/include)

# 添加编译选项
target_compile_options(kvecturbo PRIVATE
    -Wall                               # 启用所有警告
    -Wextra                             # 启用额外警告
    -O3                                 # 优化编译
    -fPIC                               # 生成位置无关代码（PIC），用于共享库
    ${OpenMP_CXX_FLAGS}                 # 添加 OpenMP 编译标志
    -Wl,-z,relro,-z,now,-z,noexecstack  # 设置链接器选项以增强安全性
    -fstack-protector-strong            # 启用栈保护
    -ftrapv                             # 整数溢出检测
    -D_FORTIFY_SOURCE=2                 # 缓冲区溢出防护
    -fvisibility=hidden                 # 隐藏非对外接口
)

# 设置链接选项
target_link_options(kvecturbo PUBLIC -s -Wl,-z,relro,-z,now,-z,noexecstack -L${BINARYLIBS_PATH}/kernel/platform/Huawei_Secure_C/comm/lib/ -lsecurec)

# 链接 OpenMP 库
target_link_libraries(kvecturbo PRIVATE OpenMP::OpenMP_CXX)

# 设置安装路径
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/out)

# 安装共享库到 out/lib 文件夹
install(TARGETS kvecturbo
    LIBRARY DESTINATION lib
)

# 安装头文件到 out/include 文件夹
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# 设置版本号
set_target_properties(kvecturbo PROPERTIES VERSION 1.1.0 SOVERSION 1)
