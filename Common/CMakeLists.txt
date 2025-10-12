# Common CMakeLists.txt

# 设置通用层源文件
set(COMMON_SOURCES
    src/CommonTypes.cpp
)

# 设置通用层头文件
set(COMMON_HEADERS
    include/CommonTypes.h
)

# 创建通用层静态库
add_library(Common STATIC ${COMMON_SOURCES} ${COMMON_HEADERS})

# 设置头文件目录
target_include_directories(Common PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接库
target_link_libraries(Common
    kernel32
)

# 设置编译属性
target_compile_definitions(Common PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

# 设置C++标准
set_target_properties(Common PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)