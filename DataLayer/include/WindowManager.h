#pragma once

#include "CommonTypes.h"

using namespace WindowsAPI;


/**
 * @namespace WindowManager
 * @brief 窗口管理基础功能
 * 
 * 提供最基础的Windows窗口操作功能：
 * - 窗口查找
 * - 窗口信息获取
 * - 基础窗口控制
 */
namespace WindowManager {

// ============ 窗口枚举 ============

/**
 * @brief 枚举所有桌面窗口
 * @return 窗口句柄列表
 */
Result<std::vector<HWND>> EnumerateWindows();

// ============ 窗口查找 ============

/**
 * @brief 根据窗口标题查找窗口
 * @param title 窗口标题
 * @return 窗口句柄结果
 */
Result<HWND> FindWindowByTitle(const std::wstring& title);

/**
 * @brief 获取当前活动窗口
 * @return 活动窗口句柄
 */
Result<HWND> GetActiveWindow();

/**
 * @brief 获取前台窗口
 * @return 前台窗口句柄
 */
Result<HWND> GetForegroundWindow();

// ============ 窗口信息 ============

/**
 * @brief 获取窗口标题
 * @param windowHandle 窗口句柄
 * @return 窗口标题
 */
Result<std::wstring> GetWindowTitle(HWND windowHandle);

/**
 * @brief 获取窗口类名
 * @param windowHandle 窗口句柄
 * @return 窗口类名
 */
Result<std::wstring> GetWindowClassName(HWND windowHandle);

/**
 * @brief 获取窗口矩形区域
 * @param windowHandle 窗口句柄
 * @return 窗口矩形
 */
Result<WindowsAPI::Rectangle> GetWindowRect(HWND windowHandle);

/**
 * @brief 获取窗口客户区矩形
 * @param windowHandle 窗口句柄
 * @return 客户区矩形
 */
Result<WindowsAPI::Rectangle> GetClientRect(HWND windowHandle);

/**
 * @brief 获取窗口进程ID
 * @param windowHandle 窗口句柄
 * @return 进程ID
 */
Result<DWORD> GetWindowProcessId(HWND windowHandle);

// ============ 基础窗口控制 ============

/**
 * @brief 显示窗口
 * @param windowHandle 窗口句柄
 * @return 操作结果
 */
Result<bool> ShowWindow(HWND windowHandle);

/**
 * @brief 隐藏窗口
 * @param windowHandle 窗口句柄
 * @return 操作结果
 */
Result<bool> HideWindow(HWND windowHandle);

/**
 * @brief 设置窗口为前台窗口
 * @param windowHandle 窗口句柄
 * @return 操作结果
 */
Result<bool> SetForegroundWindow(HWND windowHandle);

/**
 * @brief 验证窗口句柄是否有效
 * @param windowHandle 窗口句柄
 * @return 是否有效
 */
bool IsValidWindow(HWND windowHandle);

/**
 * @brief 检查窗口是否可见
 * @param windowHandle 窗口句柄
 * @return 是否可见
 */
Result<bool> IsWindowVisible(HWND windowHandle);

/**
 * @brief 设置窗口位置
 * @param windowHandle 窗口句柄
 * @param x 新的X坐标
 * @param y 新的Y坐标
 * @return 操作结果
 */
Result<bool> SetWindowPosition(HWND windowHandle, int x, int y);

/**
 * @brief 设置窗口大小
 * @param windowHandle 窗口句柄
 * @param width 新的宽度
 * @param height 新的高度
 * @return 操作结果
 */
Result<bool> SetWindowSize(HWND windowHandle, int width, int height);

/**
 * @brief 最小化窗口
 * @param windowHandle 窗口句柄
 * @return 操作结果
 */
Result<bool> MinimizeWindow(HWND windowHandle);

/**
 * @brief 最大化窗口
 * @param windowHandle 窗口句柄
 * @return 操作结果
 */
Result<bool> MaximizeWindow(HWND windowHandle);

/**
 * @brief 还原窗口（从最小化或最大化状态还原到正常状态）
 * @param windowHandle 窗口句柄
 * @return 操作结果
 */
Result<bool> RestoreWindow(HWND windowHandle);

// ============ 窗口状态检查 ============

/**
 * @brief 检查窗口是否最小化
 * @param windowHandle 窗口句柄
 * @return 是否最小化
 */
Result<bool> IsWindowMinimized(HWND windowHandle);

/**
 * @brief 检查窗口是否最大化
 * @param windowHandle 窗口句柄
 * @return 是否最大化
 */
Result<bool> IsWindowMaximized(HWND windowHandle);

/**
 * @brief 检查窗口是否处于正常状态（既不最小化也不最大化）
 * @param windowHandle 窗口句柄
 * @return 是否正常状态
 */
Result<bool> IsWindowNormal(HWND windowHandle);

}  // namespace WindowManager