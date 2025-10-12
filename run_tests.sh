#!/bin/bash

# Windows API 项目 Google Test 测试运行器 (Linux/macOS)

echo "========================================"
echo "Windows API 项目 Google Test 测试运行器"
echo "========================================"
echo

BUILD_DIR="build"
TEST_DIR="$BUILD_DIR/bin"

echo "[1/4] 检查构建环境..."
if [ ! -d "$BUILD_DIR" ]; then
    echo "创建构建目录..."
    mkdir -p "$BUILD_DIR"
fi

echo "[2/4] 配置项目..."
cd "$BUILD_DIR"
cmake .. -G "Unix Makefiles"
if [ $? -ne 0 ]; then
    echo "错误：CMake配置失败！"
    exit 1
fi

echo "[3/4] 编译项目..."
cmake --build .
if [ $? -ne 0 ]; then
    echo "错误：编译失败！"
    exit 1
fi

echo "[4/4] 运行测试..."
cd ..

# 创建测试结果目录
mkdir -p test_results

echo
echo "========================================"
echo "开始执行Google Test测试套件"
echo "========================================"

run_test() {
    local test_name=$1
    local executable="$TEST_DIR/${test_name}_GTest"
    local output_file="test_results/${test_name,,}_test_results.xml"
    
    echo
    echo "--- $test_name 模块测试 ---"
    if [ -f "$executable" ]; then
        "$executable" --gtest_output="xml:$output_file"
    else
        echo "${test_name}_GTest 未找到，跳过..."
    fi
}

# 运行所有测试
run_test "SmokeTest"
run_test "WindowManagerTest"
run_test "KeyboardSimulatorTest"
run_test "MouseSimulatorTest"
run_test "ScreenCaptureTest"

echo
echo "========================================"
echo "测试完成！"
echo "========================================"
echo "测试结果XML文件已保存到 test_results 目录"
echo

read -p "按回车键退出..."