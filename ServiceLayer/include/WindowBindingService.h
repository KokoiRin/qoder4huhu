#pragma once

#include "CommonTypes.h"
#include "BoundWindow.h"
#include <vector>
#include <memory>

using namespace WindowsAPI;

/**
 * @brief 窗口绑定服务
 * 
 * 负责枚举桌面窗口并管理绑定的窗口对象
 */
class WindowBindingService {
public:
    /**
     * @brief 窗口显示信息（用于列表展示）
     */
    struct WindowDisplayInfo {
        HWND handle;
        std::wstring title;
        
        WindowDisplayInfo() : handle(nullptr) {}
        WindowDisplayInfo(HWND h, const std::wstring& t) : handle(h), title(t) {}
    };

public:
    WindowBindingService() = default;
    ~WindowBindingService() = default;

    /**
     * @brief 获取所有桌面窗口列表（仅句柄和标题）
     */
    Result<std::vector<WindowDisplayInfo>> GetAllDesktopWindows();

    /**
     * @brief 绑定指定窗口
     */
    Result<bool> BindWindow(HWND windowHandle);

    /**
     * @brief 获取当前绑定的窗口对象
     */
    std::shared_ptr<BoundWindow> GetBoundWindow();

    /**
     * @brief 检查是否已绑定窗口
     */
    bool HasBoundWindow() const;

private:
    std::shared_ptr<BoundWindow> m_boundWindow;
};
