cmake_minimum_required(VERSION 3.16)
project(WindowsAPIProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加头文件目录
include_directories(
    ${CMAKE_SOURCE_DIR}/Common/include
    ${CMAKE_SOURCE_DIR}/DataLayer/include
    ${CMAKE_SOURCE_DIR}/ServiceLayer/include
    ${CMAKE_SOURCE_DIR}/PresentationLayer/include
    ${CMAKE_SOURCE_DIR}/UILayer/include
)

# 添加子目录
add_subdirectory(Common)
add_subdirectory(DataLayer)
add_subdirectory(ServiceLayer)
add_subdirectory(PresentationLayer)
add_subdirectory(UILayer)

# 主可执行文件
add_executable(WindowsAPIApp main.cpp)

# 链接库
target_link_libraries(WindowsAPIApp
    UILayer
    PresentationLayer
    ServiceLayer
    DataLayer
    Common
    user32
    gdi32
    kernel32
)