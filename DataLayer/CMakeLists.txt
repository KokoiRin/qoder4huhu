# DataLayer CMakeLists.txt

# 设置数据层源文件
set(DATALAYER_SOURCES
    src/WindowManager.cpp
    src/KeyboardSimulator.cpp
    src/MouseSimulator.cpp
    src/ScreenCapture.cpp
)

# 设置数据层头文件
set(DATALAYER_HEADERS
    include/WindowManager.h
    include/KeyboardSimulator.h
    include/MouseSimulator.h
    include/ScreenCapture.h
)

# 创建数据层静态库
add_library(DataLayer STATIC ${DATALAYER_SOURCES} ${DATALAYER_HEADERS})

# 设置头文件目录
target_include_directories(DataLayer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Common/include
)

# 链接Windows API库
target_link_libraries(DataLayer
    user32
    gdi32
    kernel32
    gdiplus
    dwmapi
    ole32
    oleaut32
    uuid
)

# 设置编译属性
target_compile_definitions(DataLayer PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

# 设置C++标准
set_target_properties(DataLayer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)