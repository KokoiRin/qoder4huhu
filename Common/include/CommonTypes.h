#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

// 通用类型定义
namespace WindowsAPI {
    // 错误代码定义
    enum class ErrorCode {
        SUCCESS = 0,
        WINDOW_NOT_FOUND,
        INVALID_HANDLE,
        OPERATION_FAILED,
        PERMISSION_DENIED,
        INVALID_PARAMETER,
        MEMORY_ALLOCATION_FAILED,
        CAPTURE_FAILED,
        INPUT_SIMULATION_FAILED
    };

    // 窗口信息结构
    struct WindowInfo {
        HWND handle;
        std::wstring className;
        std::wstring windowTitle;
        RECT windowRect;
        bool isVisible;
        bool isMinimized;
        bool isMaximized;
        DWORD processId;
        DWORD threadId;
    };

    // 点坐标结构
    struct Point {
        int x;
        int y;
        
        Point() : x(0), y(0) {}
        Point(int x, int y) : x(x), y(y) {}
    };

    // 矩形区域结构
    struct Rectangle {
        int left;
        int top;
        int right;
        int bottom;
        
        Rectangle() : left(0), top(0), right(0), bottom(0) {}
        Rectangle(int l, int t, int r, int b) : left(l), top(t), right(r), bottom(b) {}
        
        int width() const { return right - left; }
        int height() const { return bottom - top; }
    };

    // 图像数据结构
    struct ImageData {
        std::vector<BYTE> data;
        int width;
        int height;
        int bitsPerPixel;
        int stride;
        
        ImageData() : width(0), height(0), bitsPerPixel(0), stride(0) {}
    };

    // 鼠标按键枚举
    enum class MouseButton {
        LEFT,
        RIGHT,
        MIDDLE,
        X1,
        X2
    };

    // 鼠标事件类型
    enum class MouseEventType {
        MOVE,
        LEFT_DOWN,
        LEFT_UP,
        RIGHT_DOWN,
        RIGHT_UP,
        MIDDLE_DOWN,
        MIDDLE_UP,
        WHEEL,
    };

    // 键盘修饰键
    enum class ModifierKey {
        NONE = 0,
        CTRL = 1,
        ALT = 2,
        SHIFT = 4,
        WIN = 8
    };

    // 操作结果结构
    template<typename T>
    class Result {
    private:
        ErrorCode errorCode;
        T data;
        std::wstring errorMessage;
        
    public:
        Result() : errorCode(ErrorCode::SUCCESS) {}
        Result(ErrorCode code, const std::wstring& message = L"") 
            : errorCode(code), errorMessage(message) {}
        Result(const T& value) : errorCode(ErrorCode::SUCCESS), data(value) {}
        
        bool IsSuccess() const { return errorCode == ErrorCode::SUCCESS; }
        bool IsError() const { return errorCode != ErrorCode::SUCCESS; }
        
        const T& GetData() const { return data; }
        T& GetData() { return data; }
        
        ErrorCode GetErrorCode() const { return errorCode; }
        const std::wstring& GetErrorMessage() const { return errorMessage; }
        
        // 静态创建方法
        static Result<T> Success(const T& value) {
            return Result<T>(value);
        }
        
        static Result<T> Error(ErrorCode code, const std::wstring& message = L"") {
            return Result<T>(code, message);
        }
    };

    // 窗口枚举回调函数类型
    using WindowEnumCallback = std::function<bool(const WindowInfo&)>;
    
    // 日志级别
    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR_LEVEL
    };

}  // namespace WindowsAPI
