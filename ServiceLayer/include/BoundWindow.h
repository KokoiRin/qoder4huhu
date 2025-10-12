#pragma once

#include "CommonTypes.h"

using namespace WindowsAPI;

/**
 * @brief 绑定窗口类 - 精简版
 * 
 * 记录窗口的基本信息：句柄、标题、位置和大小
 */
class BoundWindow {
public:
    BoundWindow() = default;
    explicit BoundWindow(HWND handle);
    ~BoundWindow() = default;

    /**
     * @brief 刷新窗口信息
     */
    Result<bool> Refresh();

    /**
     * @brief 检查窗口是否有效
     */
    bool IsValid() const;

    // ============ 获取窗口信息 ============
    
    HWND GetHandle() const { return m_handle; }
    std::wstring GetTitle() const { return m_title; }
    
    WindowsAPI::Rectangle GetPosition() const { return m_position; }
    int GetX() const { return m_position.left; }
    int GetY() const { return m_position.top; }
    int GetWidth() const { return m_position.width(); }
    int GetHeight() const { return m_position.height(); }

private:
    HWND m_handle = nullptr;
    std::wstring m_title;
    WindowsAPI::Rectangle m_position;
};

