cmake_minimum_required(VERSION 3.16)
project(WindowsAPIProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成编译数据库用于 clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# MinGW特定设置
if(MINGW)
    message(STATUS "Configuring for MinGW")
    # 启用静态链接，避免运行时依赖问题
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    # 设置Windows版本
    add_definitions(-DWINVER=0x0601 -D_WIN32_WINNT=0x0601)
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Google Test 集成
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 添加头文件目录
include_directories(
    ${CMAKE_SOURCE_DIR}/Common/include
    ${CMAKE_SOURCE_DIR}/DataLayer/include
    ${CMAKE_SOURCE_DIR}/ServiceLayer/include
    ${CMAKE_SOURCE_DIR}/PresentationLayer/include
#    ${CMAKE_SOURCE_DIR}/UILayer/include
)

# 添加子目录
add_subdirectory(Common)
add_subdirectory(DataLayer)
add_subdirectory(ServiceLayer)
add_subdirectory(PresentationLayer)
add_subdirectory(UILayer)

# 添加测试目录
add_subdirectory(test)