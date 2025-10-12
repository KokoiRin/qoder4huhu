cmake_minimum_required(VERSION 3.16)

# 测试项目配置
project(WindowsAPITests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用测试
enable_testing()

# 添加头文件目录
include_directories(
    ${CMAKE_SOURCE_DIR}/Common/include
    ${CMAKE_SOURCE_DIR}/DataLayer/include
    ${CMAKE_SOURCE_DIR}/ServiceLayer/include
    ${CMAKE_SOURCE_DIR}/PresentationLayer/include
    ${CMAKE_SOURCE_DIR}/UILayer/include
)

# 基础冒烟测试 - 使用GTest框架
add_executable(SmokeTest SmokeTest.cpp)
target_link_libraries(SmokeTest
    DataLayer
    Common
    gtest_main
    gtest
    user32
    gdi32
    kernel32
)

# 注册测试用例
include(GoogleTest)
gtest_discover_tests(SmokeTest)