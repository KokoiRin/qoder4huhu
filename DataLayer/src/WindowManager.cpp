#include "../include/WindowManager.h"
#include <windows.h>

namespace WindowManager {

// ============ 窗口查找 ============

Result<HWND> FindWindowByTitle(const std::wstring& title) {
    HWND hwnd = FindWindowW(NULL, title.c_str());
    if (hwnd == NULL) {
        return Result<HWND>::Error(ErrorCode::WINDOW_NOT_FOUND, L"Window not found: " + title);
    }
    return Result<HWND>::Success(hwnd);
}

Result<HWND> FindWindowByProcessId(DWORD processId) {
    struct EnumData {
        DWORD targetProcessId;
        HWND resultHwnd;
    };
    
    EnumData enumData = { processId, NULL };
    
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        EnumData* data = reinterpret_cast<EnumData*>(lParam);
        DWORD windowProcessId;
        GetWindowThreadProcessId(hwnd, &windowProcessId);
        
        if (windowProcessId == data->targetProcessId && ::IsWindowVisible(hwnd)) {
            data->resultHwnd = hwnd;
            return FALSE; // 停止枚举
        }
        return TRUE; // 继续枚举
    }, reinterpret_cast<LPARAM>(&enumData));
    
    if (enumData.resultHwnd == NULL) {
        return Result<HWND>::Error(ErrorCode::WINDOW_NOT_FOUND, L"Window not found for process ID");
    }
    
    return Result<HWND>::Success(enumData.resultHwnd);
}

Result<HWND> GetActiveWindow() {
    HWND hwnd = ::GetActiveWindow();
    if (hwnd == NULL) {
        return Result<HWND>::Error(ErrorCode::WINDOW_NOT_FOUND, L"No active window");
    }
    return Result<HWND>::Success(hwnd);
}

Result<HWND> GetForegroundWindow() {
    HWND hwnd = ::GetForegroundWindow();
    if (hwnd == NULL) {
        return Result<HWND>::Error(ErrorCode::WINDOW_NOT_FOUND, L"No foreground window");
    }
    return Result<HWND>::Success(hwnd);
}

// ============ 窗口信息 ============

Result<std::wstring> GetWindowTitle(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<std::wstring>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    int length = GetWindowTextLengthW(windowHandle);
    if (length == 0) {
        return Result<std::wstring>::Success(L"");
    }
    
    std::wstring title(length + 1, L'\0');
    int actualLength = GetWindowTextW(windowHandle, &title[0], length + 1);
    title.resize(actualLength);
    
    return Result<std::wstring>::Success(title);
}

Result<std::wstring> GetWindowClassName(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<std::wstring>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    wchar_t className[256];
    int length = GetClassNameW(windowHandle, className, 256);
    if (length == 0) {
        return Result<std::wstring>::Error(ErrorCode::OPERATION_FAILED, L"Failed to get class name");
    }
    
    return Result<std::wstring>::Success(std::wstring(className, length));
}

Result<WindowsAPI::Rectangle> GetWindowRect(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<WindowsAPI::Rectangle>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    RECT rect;
    if (!::GetWindowRect(windowHandle, &rect)) {
        return Result<WindowsAPI::Rectangle>::Error(ErrorCode::OPERATION_FAILED, L"Failed to get window rect");
    }
    
    WindowsAPI::Rectangle result(rect.left, rect.top, rect.right, rect.bottom);
    return Result<WindowsAPI::Rectangle>::Success(result);
}

Result<WindowsAPI::Rectangle> GetClientRect(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<WindowsAPI::Rectangle>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    RECT rect;
    if (!::GetClientRect(windowHandle, &rect)) {
        return Result<WindowsAPI::Rectangle>::Error(ErrorCode::OPERATION_FAILED, L"Failed to get client rect");
    }
    
    WindowsAPI::Rectangle result(rect.left, rect.top, rect.right, rect.bottom);
    return Result<WindowsAPI::Rectangle>::Success(result);
}

Result<DWORD> GetWindowProcessId(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<DWORD>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    DWORD processId;
    GetWindowThreadProcessId(windowHandle, &processId);
    
    return Result<DWORD>::Success(processId);
}

// ============ 基础窗口控制 ============

Result<bool> ShowWindow(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    ::ShowWindow(windowHandle, SW_SHOW);
    return Result<bool>::Success(true);
}

Result<bool> HideWindow(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    ::ShowWindow(windowHandle, SW_HIDE);
    return Result<bool>::Success(true);
}

Result<bool> SetForegroundWindow(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    if (!::SetForegroundWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::OPERATION_FAILED, L"Failed to set foreground window");
    }
    
    return Result<bool>::Success(true);
}

bool IsValidWindow(HWND windowHandle) {
    return IsWindow(windowHandle) != FALSE;
}

Result<bool> IsWindowVisible(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    bool visible = ::IsWindowVisible(windowHandle) != FALSE;
    return Result<bool>::Success(visible);
}

Result<bool> SetWindowPosition(HWND windowHandle, int x, int y) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    if (!SetWindowPos(windowHandle, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)) {
        return Result<bool>::Error(ErrorCode::OPERATION_FAILED, L"Failed to set window position");
    }
    
    return Result<bool>::Success(true);
}

Result<bool> SetWindowSize(HWND windowHandle, int width, int height) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    if (!SetWindowPos(windowHandle, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER)) {
        return Result<bool>::Error(ErrorCode::OPERATION_FAILED, L"Failed to set window size");
    }
    
    return Result<bool>::Success(true);
}

Result<bool> MinimizeWindow(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    ::ShowWindow(windowHandle, SW_MINIMIZE);
    return Result<bool>::Success(true);
}

Result<bool> MaximizeWindow(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    ::ShowWindow(windowHandle, SW_MAXIMIZE);
    return Result<bool>::Success(true);
}

Result<bool> RestoreWindow(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    ::ShowWindow(windowHandle, SW_RESTORE);
    return Result<bool>::Success(true);
}

// ============ 窗口状态检查 ============

Result<bool> IsWindowMinimized(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    bool minimized = ::IsIconic(windowHandle) != FALSE;
    return Result<bool>::Success(minimized);
}

Result<bool> IsWindowMaximized(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    bool maximized = ::IsZoomed(windowHandle) != FALSE;
    return Result<bool>::Success(maximized);
}

Result<bool> IsWindowNormal(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    bool minimized = ::IsIconic(windowHandle) != FALSE;
    bool maximized = ::IsZoomed(windowHandle) != FALSE;
    bool normal = !minimized && !maximized;
    
    return Result<bool>::Success(normal);
}

}  // namespace WindowManager