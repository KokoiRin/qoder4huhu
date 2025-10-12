#include "BoundWindow.h"
#include "WindowManager.h"


BoundWindow::BoundWindow(HWND handle) : m_handle(handle) {
    Refresh();
}

Result<bool> BoundWindow::Refresh() {
    if (!WindowManager::IsValidWindow(m_handle)) {
        return Result<bool>::Error(ErrorCode::INVALID_HANDLE, L"Window handle is invalid");
    }

    // 获取窗口标题
    auto titleResult = WindowManager::GetWindowTitle(m_handle);
    if (titleResult.IsSuccess()) {
        m_title = titleResult.GetData();
    }

    // 获取窗口位置和大小
    auto rectResult = WindowManager::GetWindowRect(m_handle);
    if (rectResult.IsSuccess()) {
        m_position = rectResult.GetData();
    }

    return Result<bool>::Success(true);
}

bool BoundWindow::IsValid() const {
    return WindowManager::IsValidWindow(m_handle);
}
