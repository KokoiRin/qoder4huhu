#!/bin/bash

# Windows API 项目 MinGW 构建脚本 (Bash版本)

echo "======================================="
echo "Windows API 项目构建脚本"
echo "======================================="
echo

BUILD_DIR="build"

echo "[1/4] 检查工具链..."
if ! command -v gcc &> /dev/null; then
    echo "错误：未找到gcc，请确保MinGW已添加到PATH环境变量中"
    exit 1
fi

if ! command -v qmake &> /dev/null; then
    echo "错误：未找到qmake，请确保Qt6已正确安装并添加到PATH"
    exit 1
fi

echo "✓ 工具链检查完成"

echo "[2/4] 清理和配置..."
if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
fi

if [ -f "$BUILD_DIR/CMakeCache.txt" ]; then
    rm -f "$BUILD_DIR/CMakeCache.txt"
fi

cd "$BUILD_DIR"
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if [ $? -ne 0 ]; then
    echo "错误：CMake配置失败！"
    cd ..
    exit 1
fi

echo "[3/4] 编译项目..."
cmake --build . --parallel
if [ $? -ne 0 ]; then
    echo "编译失败！"
    cd ..
    exit 1
fi

cd ..

echo "[4/4] 检查结果..."
if [ -f "$BUILD_DIR/bin/WindowsAPIApp.exe" ]; then
    echo "✓ 主程序编译成功: $BUILD_DIR/bin/WindowsAPIApp.exe"
else
    echo "✗ 主程序编译失败"
fi

echo "
构建完成！运行: ./$BUILD_DIR/bin/WindowsAPIApp.exe"