# UILayer CMakeLists.txt

# 设置UI层源文件
set(UILAYER_SOURCES
    src/MainWindow.cpp
    src/ControlPanel.cpp
    src/StatusBar.cpp
    src/MenuHandler.cpp
)

# 设置UI层头文件
set(UILAYER_HEADERS
    include/MainWindow.h
    include/ControlPanel.h
    include/StatusBar.h
    include/MenuHandler.h
)

# 创建UI层静态库
add_library(UILayer STATIC ${UILAYER_SOURCES} ${UILAYER_HEADERS})

# 设置头文件目录
target_include_directories(UILayer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Common/include
    ${CMAKE_SOURCE_DIR}/DataLayer/include
    ${CMAKE_SOURCE_DIR}/ServiceLayer/include
    ${CMAKE_SOURCE_DIR}/PresentationLayer/include
)

# 链接依赖库
target_link_libraries(UILayer
    PresentationLayer
    ServiceLayer
    DataLayer
    Common
    comctl32
    shell32
)

# 设置编译属性
target_compile_definitions(UILayer PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

# 设置C++标准
set_target_properties(UILayer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)