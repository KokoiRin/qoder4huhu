# 测试结果文件夹

此文件夹用于存储 Google Test 生成的 XML 格式测试报告。

## 测试报告文件
- `smoke_test_results.xml` - SmokeTest 基础功能验证测试结果
- `window_manager_test_results.xml` - WindowManager 模块测试结果
- `keyboard_simulator_test_results.xml` - KeyboardSimulator 模块测试结果
- `mouse_simulator_test_results.xml` - MouseSimulator 模块测试结果
- `screen_capture_test_results.xml` - ScreenCapture 模块测试结果

## 查看测试报告
这些 XML 文件可以被各种工具解析和可视化：
- CI/CD 系统（如 Jenkins、GitHub Actions）
- 测试报告查看器
- XML 解析工具

## 手动运行单个测试
```bash
# 运行单个测试并生成报告
./build/bin/SmokeTest_GTest --gtest_output=xml:test_results/smoke_test_results.xml

# 运行测试并显示详细输出
./build/bin/WindowManagerTest_GTest --gtest_verbose
```