#include "../include/KeyboardSimulator.h"
#include <windows.h>

using namespace WindowsAPI;

namespace KeyboardSimulator {

// 内部辅助函数
namespace {
    // 构建键盘消息的LPARAM
    LPARAM MakeKeyLParam(UINT scanCode, bool keyUp = false, bool extended = false) {
        LPARAM lParam = 1; // 重复计数
        lParam |= (scanCode & 0xFF) << 16; // 扫描码
        if (extended) lParam |= 0x01000000; // 扩展键标志
        if (keyUp) lParam |= 0x80000000; // 键释放标志
        lParam |= 0x20000000; // 前一个键状态（假设之前未按下）
        return lParam;
    }
    
    // 获取虚拟键码的扫描码
    UINT GetScanCode(UINT virtualKey) {
        return MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
    }
    
    // 检查是否为扩展键
    bool IsExtendedKey(UINT virtualKey) {
        switch (virtualKey) {
            case VK_INSERT:
            case VK_DELETE:
            case VK_HOME:
            case VK_END:
            case VK_PRIOR: // Page Up
            case VK_NEXT:  // Page Down
            case VK_LEFT:
            case VK_RIGHT:
            case VK_UP:
            case VK_DOWN:
            case VK_RCONTROL:
            case VK_RMENU: // Right Alt
            case VK_LWIN:
            case VK_RWIN:
            case VK_APPS:
                return true;
            default:
                return false;
        }
    }
}

// ============ 基础按键操作 ============

Result<bool> KeyDown(HWND windowHandle, UINT virtualKey) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    UINT scanCode = GetScanCode(virtualKey);
    bool extended = IsExtendedKey(virtualKey);
    LPARAM lParam = MakeKeyLParam(scanCode, false, extended);
    
    SendMessage(windowHandle, WM_KEYDOWN, virtualKey, lParam);
    
    return Result<bool>::Success(true);
}

Result<bool> KeyUp(HWND windowHandle, UINT virtualKey) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    UINT scanCode = GetScanCode(virtualKey);
    bool extended = IsExtendedKey(virtualKey);
    LPARAM lParam = MakeKeyLParam(scanCode, true, extended);
    
    SendMessage(windowHandle, WM_KEYUP, virtualKey, lParam);
    
    return Result<bool>::Success(true);
}

// ============ 文本输入 ============

Result<bool> SendChar(HWND windowHandle, wchar_t character) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    // 使用WM_CHAR消息发送字符
    SendMessage(windowHandle, WM_CHAR, character, 1);
    
    return Result<bool>::Success(true);
}

Result<bool> SendText(HWND windowHandle, const std::wstring& text) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    for (wchar_t ch : text) {
        auto result = SendChar(windowHandle, ch);
        if (!result.IsSuccess()) {
            return result;
        }
        Sleep(10); // 字符间延迟
    }
    
    return Result<bool>::Success(true);
}

// ============ 键盘状态 ============

Result<bool> IsKeyPressed(UINT virtualKey) {
    SHORT keyState = GetAsyncKeyState(virtualKey);
    bool pressed = (keyState & 0x8000) != 0;
    return Result<bool>::Success(pressed);
}

Result<bool> IsCapsLockOn() {
    SHORT keyState = GetKeyState(VK_CAPITAL);
    bool capsLockOn = (keyState & 0x0001) != 0;
    return Result<bool>::Success(capsLockOn);
}

Result<bool> IsNumLockOn() {
    SHORT keyState = GetKeyState(VK_NUMLOCK);
    bool numLockOn = (keyState & 0x0001) != 0;
    return Result<bool>::Success(numLockOn);
}

}  // namespace KeyboardSimulator