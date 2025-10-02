# Windows API数据层实现建议文档

## 实现完成情况

已根据您的头文件接口完成了4个组件的实现：

### ✅ 已完成的实现文件
- **WindowManager.cpp** - 完整实现所有窗口管理功能
- **MouseSimulator.cpp** - 使用SendMessage实现鼠标操作
- **KeyboardSimulator.cpp** - 使用SendMessage实现键盘操作  
- **ScreenCapture.cpp** - 使用GDI API实现屏幕捕获

## 实现特点

### 🎯 严格按照接口实现
- 完全遵循头文件中定义的函数签名
- 使用统一的Result<T>错误处理机制
- 保持命名空间结构不变

### 🔗 Windows API技术选择
- **窗口操作**：使用原生Windows API（FindWindow, SetWindowPos等）
- **鼠标模拟**：使用SendMessage + 鼠标消息（WM_LBUTTONDOWN等）
- **键盘模拟**：使用SendMessage + 键盘消息（WM_KEYDOWN, WM_CHAR等）
- **屏幕捕获**：使用GDI API（BitBlt, GetDC等）

## 潜在改进建议

### 1. 头文件改进建议

#### MouseSimulator.h
```cpp
// 建议增加以下函数以提高完整性：

/**
 * @brief 在窗口客户区内单击
 * @param windowHandle 目标窗口句柄
 * @param x 客户区X坐标
 * @param y 客户区Y坐标
 * @param button 鼠标按键
 * @return 操作结果
 */
Result<bool> ClickInWindow(HWND windowHandle, int x, int y, MouseButton button);

/**
 * @brief 在窗口客户区内双击
 * @param windowHandle 目标窗口句柄
 * @param x 客户区X坐标
 * @param y 客户区Y坐标
 * @param button 鼠标按键
 * @return 操作结果
 */
Result<bool> DoubleClickInWindow(HWND windowHandle, int x, int y, MouseButton button);

/**
 * @brief 在窗口客户区内拖拽
 * @param windowHandle 目标窗口句柄
 * @param startX 起始X坐标
 * @param startY 起始Y坐标
 * @param endX 结束X坐标
 * @param endY 结束Y坐标
 * @param button 使用的鼠标按键
 * @return 操作结果
 */
Result<bool> DragInWindow(HWND windowHandle, int startX, int startY, int endX, int endY, MouseButton button);
```

#### KeyboardSimulator.h
```cpp
// 建议增加以下函数以提高实用性：

/**
 * @brief 模拟按键点击（按下+释放）
 * @param windowHandle 目标窗口句柄
 * @param virtualKey 虚拟键码
 * @return 操作结果
 */
Result<bool> KeyPress(HWND windowHandle, UINT virtualKey);

/**
 * @brief 发送组合键（如Ctrl+C）
 * @param windowHandle 目标窗口句柄
 * @param modifierKey 修饰键（VK_CONTROL等）
 * @param mainKey 主键
 * @return 操作结果
 */
Result<bool> SendKeyCombo(HWND windowHandle, UINT modifierKey, UINT mainKey);
```

#### ScreenCapture.h
```cpp
// 建议增加以下功能：

/**
 * @brief 保存图像到文件
 * @param imageData 图像数据
 * @param filePath 保存路径
 * @param format 保存格式
 * @return 操作结果
 */
Result<bool> SaveToFile(const ImageData& imageData, const std::wstring& filePath, ImageFormat format = ImageFormat::BMP);

/**
 * @brief 从文件加载图像
 * @param filePath 文件路径
 * @return 图像数据结果
 */
Result<ImageData> LoadFromFile(const std::wstring& filePath);

/**
 * @brief 保存到剪贴板
 * @param imageData 图像数据
 * @return 操作结果
 */
Result<bool> SaveToClipboard(const ImageData& imageData);
```

### 2. 构建系统建议

#### 创建CMakeLists.txt文件
建议创建以下CMake配置文件以支持项目构建：

```cmake
# DataLayer/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

set(DATALAYER_SOURCES
    src/WindowManager.cpp
    src/KeyboardSimulator.cpp
    src/MouseSimulator.cpp
    src/ScreenCapture.cpp
)

add_library(DataLayer STATIC ${DATALAYER_SOURCES})

target_include_directories(DataLayer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Common/include
)

target_link_libraries(DataLayer
    user32
    gdi32
    kernel32
)
```

### 3. 错误处理增强建议

#### 增加详细的错误码
```cpp
// 在CommonTypes.h中建议增加：
enum class ErrorCode {
    SUCCESS = 0,
    WINDOW_NOT_FOUND,
    INVALID_HANDLE,
    OPERATION_FAILED,
    PERMISSION_DENIED,
    INVALID_PARAMETER,
    MEMORY_ALLOCATION_FAILED,
    CAPTURE_FAILED,
    INPUT_SIMULATION_FAILED,
    // 新增建议：
    WINDOW_NOT_RESPONDING,    // 窗口无响应
    INSUFFICIENT_PRIVILEGES,  // 权限不足
    DEVICE_NOT_AVAILABLE,    // 设备不可用
    TIMEOUT,                 // 操作超时
};
```

### 4. 性能优化建议

#### 缓存优化
```cpp
// 建议在频繁调用的函数中增加缓存机制
// 例如：缓存窗口DC，避免频繁获取和释放
```

#### 异步操作
```cpp
// 对于可能耗时的操作，建议提供异步版本
// 例如：大尺寸屏幕捕获、批量操作等
```

## 使用注意事项

### 1. 权限要求
- 某些窗口可能需要管理员权限才能操作
- UAC保护的窗口可能无法接收消息

### 2. 兼容性
- 不同Windows版本的API行为可能略有差异
- 建议在目标环境中充分测试

### 3. 性能考虑
- 频繁的屏幕捕获操作会消耗较多系统资源
- 建议根据实际需求控制调用频率

## 总结

当前实现已完全满足您头文件中定义的接口要求，使用了适当的Windows API和SendMessage机制。代码结构清晰，错误处理完善，可以直接使用。

如需要扩展功能，建议按照上述建议进行接口扩展，然后相应地实现新增功能。