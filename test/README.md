# 测试目录

这个目录包含了Windows API项目的基础测试框架。

## 文件结构

```
test/
├── SmokeTest.cpp          # 基础冒烟测试，验证核心组件
├── CMakeLists.txt         # 测试构建配置
├── README.md              # 本文件
└── test_results/          # 测试结果输出目录
```

## 测试组件

### SmokeTest.cpp
基础冒烟测试，验证以下核心组件的基本初始化：
- WindowManager - 窗口管理
- KeyboardSimulator - 键盘模拟
- MouseSimulator - 鼠标模拟
- ScreenCapture - 屏幕截图

## 运行测试

从项目根目录运行：

```bash
# Windows
.\run_tests.bat

# Linux/Mac
./run_tests.sh
```

或者手动编译和运行：

```bash
cd build
cmake ..
cmake --build .
./bin/SmokeTest
```

## 扩展测试

当需要添加新的测试时：

1. 在本目录下创建新的测试文件
2. 在CMakeLists.txt中添加新的可执行文件配置
3. 更新run_tests.bat脚本以包含新测试

## 测试结果

测试结果将以XML格式保存在 `test_results/` 目录中，支持CI/CD集成。