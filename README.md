# Windows API 四层架构 C++ 项目

## 项目概述

这是一个基于Windows API的C++项目，采用四层架构设计：
- **数据层 (DataLayer)**: 直接调用Windows API的底层实现
- **服务层 (ServiceLayer)**: 业务逻辑处理和数据层的封装
- **表现层 (PresentationLayer)**: 数据格式化和命令处理
- **UI层 (UILayer)**: 用户界面和交互

## 目录结构

```
qoder4huhu/
├── Common/                    # 通用组件
│   ├── include/
│   │   └── CommonTypes.h     # 通用类型定义
│   └── src/
├── DataLayer/                 # 数据层
│   ├── include/
│   │   ├── WindowManager.h   # 窗口管理
│   │   ├── KeyboardSimulator.h  # 键盘输入模拟
│   │   ├── MouseSimulator.h  # 鼠标操作模拟
│   │   └── ScreenCapture.h   # 屏幕捕获
│   └── src/
├── ServiceLayer/             # 服务层
│   ├── include/
│   └── src/
├── PresentationLayer/        # 表现层
│   ├── include/
│   └── src/
├── UILayer/                  # UI层
│   ├── include/
│   └── src/
├── CMakeLists.txt           # 主构建文件
└── main.cpp                 # 程序入口
```

## 数据层功能概述

数据层采用简化设计，所有功能都是基础、快速、无阻塞的Windows API调用：

### WindowManager（窗口管理）
- **窗口查找**：按标题、进程ID查找窗口
- **窗口信息**：获取标题、类名、位置、大小等
- **窗口控制**：显示/隐藏、设置前台、最小化/最大化/还原
- **窗口调整**：设置位置、大小、位置和大小
- **状态检查**：检查窗口是否可见、最小化、最大化、正常状态

### MouseSimulator（鼠标模拟）
**注意：所有鼠标操作都与窗口句柄绑定**
- **窗口内移动**：在指定窗口客户区内移动鼠标
- **窗口内点击**：按下、释放、单击、双击
- **窗口内拖拽**：在窗口客户区内进行拖拽操作
- **窗口内滚轮**：在窗口内滚动

### KeyboardSimulator（键盘模拟）
- **基础输入**：按键按下、释放、发送字符
- **文本输入**：发送文本到指定窗口
- **组合键**：Ctrl、Alt、Shift组合
- **特殊键**：回车、退格、方向键等

### ScreenCapture（屏幕捕获）
- **全屏捕获**：捕获整个屏幕
- **区域捕获**：根据坐标捕获指定区域
- **窗口捕获**：捕获指定窗口或客户区
- **文件操作**：保存到文件、从文件加载
- **剪贴板**：与系统剪贴板交互

## 设计特点

### 1. 统一的错误处理
- 使用 `Result<T>` 模板类统一处理操作结果和错误
- 详细的错误码定义和错误信息
- 支持链式调用和错误传播

### 2. 简化的函数式设计
- 采用命名空间管理函数的方式，而非类的设计
- 所有函数可独立调用，无需初始化或清理
- 减少了复杂的对象生命周期管理
- 更直观的API使用方式

### 3. 类型安全
- 强类型枚举定义（MouseButton、KeyModifier、ImageFormat等）
- 明确的参数类型和返回值类型
- 编译时类型检查

### 4. 资源管理
- 明确的初始化和清理流程
- 统一的资源管理接口
- 避免资源泄漏

### 5. 扩展性
- 清晰的层次分离，便于功能扩展
- 回调函数支持自定义处理逻辑
- 灵活的配置选项

### 6. 调试支持
- 内置调试模式
- 详细的操作日志
- 错误追踪和统计信息

- **编译器**: MinGW-w64 GCC 8.0+ (推荐) 或 Visual Studio 2019+
- **C++标准**: C++17
- **系统要求**: Windows 10+
- **依赖库**: Windows SDK、GDI+

## 构建说明

### 快速开始

**使用 Shell 脚本**:
```bash
# 构建项目
./build.sh

# 运行主程序
./build/bin/WindowsAPIApp.exe
```

### 手动构建

1. 使用CMake生成项目文件：
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
```

2. 编译项目：
```bash
cmake --build . --parallel
```

3. 运行程序：
```bash
./bin/WindowsAPIApp.exe
./bin/SmokeTest.exe
```

### 环境要求

- **编译器**: MinGW-w64 GCC 8.0+ (推荐) 或 Visual Studio 2019+
- **构建工具**: CMake 3.16+
- **C++标准**: C++17
- **系统要求**: Windows 10+
- **依赖库**: Windows SDK、Google Test (自动下载)

详细构建说明请参考 [`BUILD_GUIDE.md`](BUILD_GUIDE.md)

## 使用示例

```cpp
// 无需初始化，直接使用各个命名空间中的函数

// 1. 查找窗口
var result = WindowManager::FindWindowByTitle(L"记事本");
if (result.IsSuccess()) {
    HWND notepadWindow = result.GetData();
    
    // 2. 窗口状态控制
    WindowManager::SetWindowPosition(notepadWindow, 100, 100);
    WindowManager::SetWindowSize(notepadWindow, 800, 600);
    WindowManager::MaximizeWindow(notepadWindow);
    WindowManager::MinimizeWindow(notepadWindow);
    WindowManager::RestoreWindow(notepadWindow);
    
    // 3. 检查窗口状态
    auto isMaximized = WindowManager::IsWindowMaximized(notepadWindow);
    auto isMinimized = WindowManager::IsWindowMinimized(notepadWindow);
    auto isVisible = WindowManager::IsWindowVisible(notepadWindow);
    
    if (isMaximized.IsSuccess() && isMaximized.GetData()) {
        std::wcout << L"窗口已最大化" << std::endl;
    }
    
    // 4. 模拟键盘输入
    KeyboardSimulator::SendText(notepadWindow, L"Hello, World!");
    
    // 5. 鼠标在窗口内操作（所有鼠标操作都与窗口句柄绑定）
    MouseSimulator::ClickInWindow(notepadWindow, 100, 100, MouseButton::LEFT);
    MouseSimulator::ScrollInWindow(notepadWindow, 200, 200, 3);
    MouseSimulator::DragInWindow(notepadWindow, 50, 50, 150, 150, MouseButton::LEFT);
    
    // 6. 窗口截图
    auto imageData = ScreenCapture::CaptureWindow(notepadWindow);
    if (imageData.IsSuccess()) {
        ScreenCapture::SaveToFile(imageData.GetData(), L"notepad_screenshot.png");
    }
}

// 7. 屏幕区域捕获（根据坐标）
auto regionCapture = ScreenCapture::CaptureRegion(0, 0, 400, 300);
if (regionCapture.IsSuccess()) {
    ScreenCapture::SaveToFile(regionCapture.GetData(), L"region_screenshot.png");
}

// 8. 获取窗口信息
if (result.IsSuccess()) {
    auto windowRect = WindowManager::GetWindowRect(result.GetData());
    if (windowRect.IsSuccess()) {
        auto rect = windowRect.GetData();
        std::wcout << L"窗口位置: (" << rect.x << L", " << rect.y 
                  << L"), 大小: " << rect.width << L"x" << rect.height << std::endl;
    }
}
```

## 后续开发计划

1. 完善服务层业务逻辑封装
2. 实现表现层命令处理和数据格式化
3. 开发UI层用户界面
4. 添加配置文件支持
5. 实现插件系统
6. 添加单元测试

## 注意事项

- 确保程序具有足够的权限进行窗口操作
- 某些受保护的窗口可能无法进行输入模拟
- 屏幕捕获功能需要注意性能影响
- 建议在实际使用前进行充分测试