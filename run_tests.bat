@echo off
chcp 65001 > nul
echo ========================================
echo Windows API 项目 Google Test 测试运行器
echo ========================================
echo.

set "BUILD_DIR=build"
set "TEST_DIR=%BUILD_DIR%\bin"

echo [1/4] 检查构建环境...
if not exist "%BUILD_DIR%" (
    echo 创建构建目录...
    mkdir "%BUILD_DIR%"
)

echo [2/4] 配置项目...
cd "%BUILD_DIR%"
cmake .. -G "MinGW Makefiles"
if %ERRORLEVEL% neq 0 (
    echo 错误：CMake配置失败！
    pause
    exit /b 1
)

echo [3/4] 编译项目...
cmake --build .
if %ERRORLEVEL% neq 0 (
    echo 错误：编译失败！
    pause
    exit /b 1
)

echo [4/4] 运行测试...
cd ..

echo.
echo ========================================
echo 开始执行基础测试套件
echo ========================================

echo.
echo --- 基础功能验证测试 (SmokeTest) ---
if exist "%TEST_DIR%\SmokeTest.exe" (
    "%TEST_DIR%\SmokeTest.exe" --gtest_output=xml:test_results\smoke_test_results.xml
) else (
    echo SmokeTest.exe 未找到，跳过...
)

echo.
echo ========================================
echo 测试完成！
echo ========================================
echo 测试结果XML文件已保存到 test_results 目录
echo.

pause