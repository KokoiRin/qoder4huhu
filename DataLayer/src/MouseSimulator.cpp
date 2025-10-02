#include "../include/MouseSimulator.h"
#include <windows.h>

using namespace WindowsAPI;

namespace MouseSimulator {

// 内部辅助函数
namespace {
    // 将MouseButton转换为Windows消息
    UINT GetMouseDownMessage(MouseButton button) {
        switch (button) {
            case MouseButton::LEFT: return WM_LBUTTONDOWN;
            case MouseButton::RIGHT: return WM_RBUTTONDOWN;
            case MouseButton::MIDDLE: return WM_MBUTTONDOWN;
            case MouseButton::X1: return WM_XBUTTONDOWN;
            case MouseButton::X2: return WM_XBUTTONDOWN;
            default: return WM_LBUTTONDOWN;
        }
    }
    
    UINT GetMouseUpMessage(MouseButton button) {
        switch (button) {
            case MouseButton::LEFT: return WM_LBUTTONUP;
            case MouseButton::RIGHT: return WM_RBUTTONUP;
            case MouseButton::MIDDLE: return WM_MBUTTONUP;
            case MouseButton::X1: return WM_XBUTTONUP;
            case MouseButton::X2: return WM_XBUTTONUP;
            default: return WM_LBUTTONUP;
        }
    }
    
    // 构建LPARAM参数（包含坐标信息）
    LPARAM MakeLParam(int x, int y) {
        return MAKELPARAM(x, y);
    }
    
    // 构建鼠标消息的WPARAM参数（包含修饰键和鼠标按钮状态）
    WPARAM BuildMouseWParam(MouseButton button) {
        WPARAM wParam = 0;
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) wParam |= MK_CONTROL;
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000) wParam |= MK_SHIFT;
        
        switch (button) {
            case MouseButton::LEFT: wParam |= MK_LBUTTON; break;
            case MouseButton::RIGHT: wParam |= MK_RBUTTON; break;
            case MouseButton::MIDDLE: wParam |= MK_MBUTTON; break;
            case MouseButton::X1: wParam |= MK_XBUTTON1; break;
            case MouseButton::X2: wParam |= MK_XBUTTON2; break;
        }
        
        return wParam;
    }
    
    // 获取X按钮的附加信息
    WPARAM GetXButtonWParam(MouseButton button) {
        WPARAM wParam = BuildMouseWParam(button);
        if (button == MouseButton::X1) {
            wParam |= MAKEWPARAM(0, XBUTTON1);
        } else if (button == MouseButton::X2) {
            wParam |= MAKEWPARAM(0, XBUTTON2);
        }
        return wParam;
    }
}

// ============ 获取鼠标窗口内位置 ============

Result<Point> GetPositionInWindow(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<Point>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    POINT cursorPos;
    if (!GetCursorPos(&cursorPos)) {
        return Result<Point>::Error(ErrorCode::OPERATION_FAILED, L"Failed to get cursor position");
    }
    
    if (!ScreenToClient(windowHandle, &cursorPos)) {
        return Result<Point>::Error(ErrorCode::OPERATION_FAILED, L"Failed to convert to client coordinates");
    }
    
    Point result(cursorPos.x, cursorPos.y);
    return Result<Point>::Success(result);
}

// ============ 窗口内点击操作 ============

Result<bool> MouseButtonDownInWindow(HWND windowHandle, int x, int y, MouseButton button) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    UINT message = GetMouseDownMessage(button);
    WPARAM wParam;
    
    if (button == MouseButton::X1 || button == MouseButton::X2) {
        wParam = GetXButtonWParam(button);
    } else {
        wParam = BuildMouseWParam(button);
    }
    
    LPARAM lParam = MakeLParam(x, y);
    
    SendMessage(windowHandle, message, wParam, lParam);
    
    return Result<bool>::Success(true);
}

Result<bool> MouseButtonUpInWindow(HWND windowHandle, int x, int y, MouseButton button) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    UINT message = GetMouseUpMessage(button);
    WPARAM wParam;
    
    if (button == MouseButton::X1 || button == MouseButton::X2) {
        wParam = GetXButtonWParam(button);
    } else {
        wParam = BuildMouseWParam(button);
    }
    
    LPARAM lParam = MakeLParam(x, y);
    
    SendMessage(windowHandle, message, wParam, lParam);
    
    return Result<bool>::Success(true);
}

// ============ 窗口内移动操作 ============

Result<bool> MoveInWindow(HWND windowHandle, int endX, int endY, MouseButton button) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    // 发送鼠标移动消息
    WPARAM wParam = BuildMouseWParam(button);
    LPARAM lParam = MakeLParam(endX, endY);
    
    SendMessage(windowHandle, WM_MOUSEMOVE, wParam, lParam);
    
    return Result<bool>::Success(true);
}

// ============ 窗口内滚轮操作 ============

Result<bool> ScrollInWindow(HWND windowHandle, int x, int y, int delta) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    // 发送滚轮消息
    WPARAM wParam = MAKEWPARAM(0, delta * WHEEL_DELTA);
    LPARAM lParam = MakeLParam(x, y);
    
    SendMessage(windowHandle, WM_MOUSEWHEEL, wParam, lParam);
    
    return Result<bool>::Success(true);
}

}  // namespace MouseSimulator