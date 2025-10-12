# UILayer CMakeLists.txt

# 查找Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# 启用Qt6的MOC、UIC、RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 设置UI层源文件
set(UILAYER_SOURCES
    src/MainWindow.cpp
    src/main.cpp
)

# 设置UI层头文件
set(UILAYER_HEADERS
    include/MainWindow.h
)

# 创建主程序（Qt GUI）
add_executable(WindowsAPIApp ${UILAYER_SOURCES} ${UILAYER_HEADERS})

# 设置头文件目录
target_include_directories(WindowsAPIApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Common/include
    ${CMAKE_SOURCE_DIR}/DataLayer/include
    ${CMAKE_SOURCE_DIR}/ServiceLayer/include
    ${CMAKE_SOURCE_DIR}/PresentationLayer/include
)

# 链接Qt6库
target_link_libraries(WindowsAPIApp
    Qt6::Core
    Qt6::Widgets
    PresentationLayer
    ServiceLayer
    DataLayer
    Common
    user32
    gdi32
    kernel32
    comctl32
    shell32
)

# 设置编译属性
target_compile_definitions(WindowsAPIApp PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

# 设置C++标准
set_target_properties(WindowsAPIApp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    WIN32_EXECUTABLE TRUE
)