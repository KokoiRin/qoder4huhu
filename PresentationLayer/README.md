# PresentationLayer WindowController 使用说明

## 概述

`WindowController` 是 PresentationLayer 中的控制器类，作为 UI 层和 ServiceLayer 之间的中介，负责处理窗口相关的用户操作。

## 功能特性

1. **获取顶级窗口列表** - 枚举并显示所有桌面顶级窗口
2. **窗口选择与绑定** - 选择特定窗口并进行绑定操作
3. **绑定状态管理** - 显示当前绑定窗口的详细信息
4. **错误处理** - 完善的错误提示和状态反馈

## 架构设计

```
UILayer (MainWindow)
    ↓ 调用
PresentationLayer (WindowController)
    ↓ 调用
ServiceLayer (WindowBindingService)
    ↓ 调用
DataLayer (WindowManager)
```

## 主要类和接口

### WindowController

**位置**: `PresentationLayer/include/WindowController.h`

**主要方法**:
- `GetTopLevelWindowList()` - 获取所有顶级窗口列表
- `BindSelectedWindow(HWND)` - 绑定指定窗口
- `GetCurrentBoundWindow()` - 获取当前绑定的窗口对象
- `HasBoundWindow()` - 检查是否已绑定窗口
- `UnbindCurrentWindow()` - 解除当前窗口绑定

### WindowBindingService

**位置**: `ServiceLayer/include/WindowBindingService.h`

**主要方法**:
- `GetAllDesktopWindows()` - 枚举桌面窗口
- `BindWindow(HWND)` - 执行窗口绑定
- `GetBoundWindow()` - 获取绑定的窗口对象
- `HasBoundWindow()` - 检查绑定状态

### BoundWindow

**位置**: `ServiceLayer/include/BoundWindow.h`

**主要方法**:
- `GetHandle()` - 获取窗口句柄
- `GetTitle()` - 获取窗口标题
- `GetPosition()` - 获取窗口位置
- `GetWidth()/GetHeight()` - 获取窗口尺寸
- `IsValid()` - 检查窗口有效性

## UI 层使用示例

在 `MainWindow` 中的使用方式：

```cpp
// 1. 创建控制器实例
m_windowController = std::make_unique<WindowsAPI::WindowController>();

// 2. 获取窗口列表
auto result = m_windowController->GetTopLevelWindowList();
if (result.IsSuccess()) {
    const auto& windowList = result.GetData();
    // 显示窗口列表供用户选择
}

// 3. 绑定选中的窗口
auto bindResult = m_windowController->BindSelectedWindow(windowHandle);
if (bindResult.success) {
    // 绑定成功，显示成功信息
}

// 4. 解除绑定
auto unbindResult = m_windowController->UnbindCurrentWindow();
```

## 用户操作流程

1. **启动应用** - 运行 `WindowsAPIApp.exe`
2. **获取窗口列表** - 点击"获取窗口列表"按钮
3. **选择窗口** - 在窗口列表中双击要绑定的窗口
4. **查看绑定信息** - 在右侧面板查看绑定窗口的详细信息
5. **解除绑定** - 点击"解除绑定"按钮取消当前绑定

## 错误处理

- **无效句柄** - 自动验证窗口句柄有效性
- **枚举失败** - 提供详细的错误信息反馈
- **绑定失败** - 显示具体的失败原因
- **内存分配** - 处理内存分配异常

## 扩展说明

当前实现为基础版本，后续可以在此基础上扩展：

1. **高级过滤** - 按进程名、窗口类名等过滤
2. **窗口操作** - 移动、调整大小、最小化等操作
3. **批量绑定** - 支持多窗口同时绑定
4. **持久化** - 保存和恢复绑定配置

## 编译和运行

```bash
# 编译项目
./build.sh

# 运行应用
./build/bin/WindowsAPIApp.exe
```

## 注意事项

1. 项目遵循四层架构，每层只能调用上一层接口
2. 所有窗口操作使用Windows API的SendMessage函数
3. 错误处理使用Result模式，提供类型安全的错误信息
4. UI层使用Qt框架，支持现代化的用户界面