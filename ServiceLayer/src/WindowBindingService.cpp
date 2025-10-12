#include "WindowBindingService.h"
#include "WindowManager.h"

using namespace WindowsAPI;

// ============ WindowBindingService 实现 ============

Result<std::vector<WindowBindingService::WindowDisplayInfo>> WindowBindingService::GetAllDesktopWindows() {
    // 调用DataLayer获取所有窗口句柄
    auto windowHandlesResult = WindowManager::EnumerateWindows();
    if (windowHandlesResult.IsError()) {
        return Result<std::vector<WindowDisplayInfo>>::Error(
            windowHandlesResult.GetErrorCode(),
            L"枚举窗口失败: " + windowHandlesResult.GetErrorMessage()
        );
    }

    const auto& windowHandles = windowHandlesResult.GetData();
    std::vector<WindowDisplayInfo> windowList;
    windowList.reserve(windowHandles.size());

    // 遍历每个窗口句柄，获取窗口信息
    for (HWND handle : windowHandles) {
        // 检查窗口是否有效
        if (!WindowManager::IsValidWindow(handle)) {
            continue;
        }

        // 检查窗口是否可见
        auto visibilityResult = WindowManager::IsWindowVisible(handle);
        if (visibilityResult.IsError() || !visibilityResult.GetData()) {
            continue;
        }

        // 获取窗口标题
        auto titleResult = WindowManager::GetWindowTitle(handle);
        if (titleResult.IsError()) {
            continue;  // 跳过无法获取标题的窗口
        }

        const std::wstring& title = titleResult.GetData();
        
        // 过滤掉没有标题的窗口（通常是系统窗口）
        if (title.empty()) {
            continue;
        }

        // 添加到列表中
        windowList.emplace_back(handle, title);
    }

    return Result<std::vector<WindowDisplayInfo>>::Success(std::move(windowList));
}

Result<bool> WindowBindingService::BindWindow(HWND windowHandle) {
    // 验证窗口句柄有效性
    if (!WindowManager::IsValidWindow(windowHandle)) {
        return Result<bool>::Error(
            ErrorCode::INVALID_HANDLE,
            L"无效的窗口句柄"
        );
    }

    // 创建绑定窗口对象
    try {
        m_boundWindow = std::make_shared<BoundWindow>(windowHandle);
        
        // 刷新窗口信息
        auto refreshResult = m_boundWindow->Refresh();
        if (refreshResult.IsError()) {
            m_boundWindow.reset();  // 清除无效的绑定
            return Result<bool>::Error(
                refreshResult.GetErrorCode(),
                L"刷新窗口信息失败: " + refreshResult.GetErrorMessage()
            );
        }

        return Result<bool>::Success(true);
    } catch (const std::exception&) {
        m_boundWindow.reset();
        return Result<bool>::Error(
            ErrorCode::OPERATION_FAILED,
            L"创建绑定窗口对象失败"
        );
    }
}

std::shared_ptr<BoundWindow> WindowBindingService::GetBoundWindow() {
    return m_boundWindow;
}

bool WindowBindingService::HasBoundWindow() const {
    return m_boundWindow != nullptr && m_boundWindow->IsValid();
}