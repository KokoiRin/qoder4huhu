#pragma once

#include "CommonTypes.h"
#include "WindowBindingService.h"
#include <memory>
#include <vector>

using namespace WindowsAPI;

/**
 * @brief 窗口控制器
 * 
 * PresentationLayer层的控制器类，负责处理UI层的窗口管理请求
 * 调用ServiceLayer层的WindowBindingService来完成具体的业务逻辑
 */
class WindowController {
public:
    /**
     * @brief 窗口选择项（用于UI显示）
     */
    struct WindowListItem {
        HWND handle;
        std::wstring title;
        std::wstring displayText;  // 格式化后的显示文本
        
        WindowListItem() : handle(nullptr) {}
        WindowListItem(HWND h, const std::wstring& t) 
            : handle(h), title(t), displayText(FormatDisplayText(h, t)) {}
        
    private:
        static std::wstring FormatDisplayText(HWND handle, const std::wstring& title);
    };

public:
    WindowController();
    ~WindowController() = default;

    /**
     * @brief 获取顶级窗口列表
     * @return 窗口列表结果，包含窗口句柄、标题和格式化显示文本
     */
    Result<std::vector<WindowListItem>> GetTopLevelWindowList();

    /**
     * @brief 绑定选中的窗口
     * @param windowHandle 选中的窗口句柄
     * @return 绑定结果，成功返回true，失败返回false并包含错误信息
     */
    Result<bool> BindSelectedWindow(HWND windowHandle);

    /**
     * @brief 检查是否已绑定窗口
     * @return 是否已绑定窗口
     */
    bool HasBoundWindow() const;

    /**
     * @brief 获取当前绑定窗口的信息
     * @return 绑定窗口信息，如果未绑定则返回错误
     */
    Result<std::wstring> GetBoundWindowInfo() const;

private:
    std::unique_ptr<WindowBindingService> m_windowBindingService;
};