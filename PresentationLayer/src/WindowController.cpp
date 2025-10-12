#include "WindowController.h"
#include <sstream>
#include <iomanip>

using namespace WindowsAPI;

// ============ WindowController::WindowListItem 实现 ============

std::wstring WindowController::WindowListItem::FormatDisplayText(HWND handle, const std::wstring& title) {
    std::wostringstream oss;
    
    // 格式化为 "窗口标题 (句柄: 0x12345678)"
    oss << title;
    if (!title.empty()) {
        oss << L" ";
    }
    oss << L"(句柄: 0x" << std::hex << std::uppercase 
        << reinterpret_cast<uintptr_t>(handle) << L")";
    
    return oss.str();
}

// ============ WindowController 实现 ============

WindowController::WindowController() 
    : m_windowBindingService(std::make_unique<WindowBindingService>()) {
}

Result<std::vector<WindowController::WindowListItem>> WindowController::GetTopLevelWindowList() {
    // 调用ServiceLayer获取窗口列表
    auto result = m_windowBindingService->GetAllDesktopWindows();
    
    if (result.IsError()) {
        return Result<std::vector<WindowListItem>>::Error(
            result.GetErrorCode(), 
            L"获取窗口列表失败: " + result.GetErrorMessage()
        );
    }

    // 转换为PresentationLayer的数据格式
    std::vector<WindowListItem> windowList;
    const auto& serviceWindowList = result.GetData();
    
    windowList.reserve(serviceWindowList.size());
    for (const auto& serviceWindow : serviceWindowList) {
        windowList.emplace_back(serviceWindow.handle, serviceWindow.title);
    }

    return Result<std::vector<WindowListItem>>::Success(std::move(windowList));
}

Result<bool> WindowController::BindSelectedWindow(HWND windowHandle) {
    // 调用ServiceLayer进行窗口绑定
    auto result = m_windowBindingService->BindWindow(windowHandle);
    
    if (result.IsError()) {
        return Result<bool>::Error(
            result.GetErrorCode(),
            L"绑定窗口失败: " + result.GetErrorMessage()
        );
    }

    // 绑定成功
    return Result<bool>::Success(true);
}

bool WindowController::HasBoundWindow() const {
    return m_windowBindingService->HasBoundWindow();
}

Result<std::wstring> WindowController::GetBoundWindowInfo() const {
    if (!HasBoundWindow()) {
        return Result<std::wstring>::Error(
            ErrorCode::OPERATION_FAILED,
            L"当前没有绑定任何窗口"
        );
    }

    auto boundWindow = m_windowBindingService->GetBoundWindow();
    if (!boundWindow) {
        return Result<std::wstring>::Error(
            ErrorCode::OPERATION_FAILED,
            L"获取绑定窗口信息失败"
        );
    }

    // 格式化绑定窗口信息
    std::wostringstream oss;
    oss << L"已绑定窗口: \"" << boundWindow->GetTitle() << L"\""
        << L" (句柄: 0x" << std::hex << std::uppercase 
        << reinterpret_cast<uintptr_t>(boundWindow->GetHandle()) << L")"
        << L" 位置: (" << boundWindow->GetX() << L", " << boundWindow->GetY() << L")"
        << L" 大小: " << boundWindow->GetWidth() << L"x" << boundWindow->GetHeight();

    return Result<std::wstring>::Success(oss.str());
}