# PresentationLayer CMakeLists.txt

# 设置表现层源文件
set(PRESENTATIONLAYER_SOURCES
    src/CommandProcessor.cpp
    src/EventHandler.cpp
    src/DataFormatter.cpp
    src/ValidationEngine.cpp
)

# 设置表现层头文件
set(PRESENTATIONLAYER_HEADERS
    include/CommandProcessor.h
    include/EventHandler.h
    include/DataFormatter.h
    include/ValidationEngine.h
)

# 创建表现层静态库
add_library(PresentationLayer STATIC ${PRESENTATIONLAYER_SOURCES} ${PRESENTATIONLAYER_HEADERS})

# 设置头文件目录
target_include_directories(PresentationLayer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Common/include
    ${CMAKE_SOURCE_DIR}/DataLayer/include
    ${CMAKE_SOURCE_DIR}/ServiceLayer/include
)

# 链接依赖库
target_link_libraries(PresentationLayer
    ServiceLayer
    DataLayer
    Common
)

# 设置编译属性
target_compile_definitions(PresentationLayer PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

# 设置C++标准
set_target_properties(PresentationLayer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)