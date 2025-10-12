# ServiceLayer CMakeLists.txt

# 设置服务层源文件
set(SERVICELAYER_SOURCES 
    src/BoundWindow.cpp
    src/WindowBindingService.cpp
)

# 设置服务层头文件
set(SERVICELAYER_HEADERS
    include/BoundWindow.h
    include/WindowBindingService.h
)

# 创建服务层静态库
add_library(ServiceLayer STATIC ${SERVICELAYER_SOURCES} ${SERVICELAYER_HEADERS})

# 设置头文件目录
target_include_directories(ServiceLayer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Common/include
    ${CMAKE_SOURCE_DIR}/DataLayer/include
)

# 链接依赖库
target_link_libraries(ServiceLayer
    DataLayer
    Common
)

# 设置编译属性
target_compile_definitions(ServiceLayer PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

# 设置C++标准
set_target_properties(ServiceLayer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)