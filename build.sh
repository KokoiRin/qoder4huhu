#!/bin/bash

# Windows API 项目 MinGW 构建脚本 (Bash版本)

echo "========================================"
echo "Windows API 项目 MinGW 构建脚本"
echo "========================================"
echo

BUILD_DIR="build"

# 检查MinGW是否在PATH中
echo "[0/4] 检查MinGW工具链..."
if ! command -v gcc &> /dev/null; then
    echo "错误：未找到gcc，请确保MinGW已添加到PATH环境变量中"
    echo "常见MinGW路径：/c/MinGW/bin 或 /c/msys64/mingw64/bin"
    exit 1
fi

if command -v mingw32-make &> /dev/null; then
    MAKE_TOOL="mingw32-make"
elif command -v make &> /dev/null; then
    MAKE_TOOL="make"
else
    echo "错误：未找到make工具（mingw32-make或make）"
    exit 1
fi

echo "使用构建工具：$MAKE_TOOL"
echo "使用编译器："
gcc --version | head -1
echo

echo "[1/4] 检查构建环境..."
if [ ! -d "$BUILD_DIR" ]; then
    echo "创建构建目录..."
    mkdir -p "$BUILD_DIR"
fi

echo "[2/4] 清理之前的构建缓存..."
if [ -f "$BUILD_DIR/CMakeCache.txt" ]; then
    echo "清理CMake缓存..."
    rm -f "$BUILD_DIR/CMakeCache.txt"
fi

echo "[3/4] 配置项目..."
cd "$BUILD_DIR"
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if [ $? -ne 0 ]; then
    echo "错误：CMake配置失败！"
    echo "请检查："
    echo "1. MinGW是否正确安装"
    echo "2. CMake是否正确安装"
    echo "3. PATH环境变量是否包含MinGW和CMake路径"
    cd ..
    exit 1
fi

echo "[4/4] 编译项目..."
echo "开始并行编译..."
cmake --build . --parallel
if [ $? -ne 0 ]; then
    echo "并行编译失败，尝试单线程编译..."
    $MAKE_TOOL
    if [ $? -ne 0 ]; then
        echo "编译失败！请检查源代码和依赖"
        cd ..
        exit 1
    fi
fi

cd ..

echo
echo "========================================"
echo "构建完成！"
echo "========================================"
echo "构建结果保存在 $BUILD_DIR 目录"
echo "可执行文件位置："
echo "- 主程序：$BUILD_DIR/bin/WindowsAPIApp.exe"
echo "- 测试程序：$BUILD_DIR/bin/SmokeTest.exe"
echo

# 检查生成的文件
if [ -f "$BUILD_DIR/bin/WindowsAPIApp.exe" ]; then
    echo "✓ 主程序编译成功"
else
    echo "✗ 主程序编译失败"
fi

if [ -f "$BUILD_DIR/bin/SmokeTest.exe" ]; then
    echo "✓ 测试程序编译成功"
else
    echo "✗ 测试程序编译失败"
fi

echo
read -p "按回车键退出..."