#pragma once

#include "CommonTypes.h"


/**
 * @namespace MouseSimulator
 * @brief 鼠标操作模拟的基础功能（与窗口句柄绑定）
 * 
 * 所有鼠标操作都与指定窗口句柄绑定：
 * - 窗口内移动和点击
 * - 窗口内拖拽操作
 * - 窗口内滚轮操作
 */
namespace MouseSimulator {

// ============ 获取鼠标窗口内位置 ============

/**
 * @brief 获取鼠标在窗口内的相对位置
 * @param windowHandle 目标窗口句柄
 * @return 相对位置
 */
Result<Point> GetPositionInWindow(HWND windowHandle);

// ============ 窗口内点击操作 ============

/**
 * @brief 在窗口客户区内按下鼠标按键
 * @param windowHandle 目标窗口句柄
 * @param x 客户区X坐标
 * @param y 客户区Y坐标
 * @param button 鼠标按键
 * @return 操作结果
 */
Result<bool> MouseButtonDownInWindow(HWND windowHandle, int x, int y, MouseButton button);

/**
 * @brief 在窗口客户区内释放鼠标按键
 * @param windowHandle 目标窗口句柄
 * @param x 客户区X坐标
 * @param y 客户区Y坐标
 * @param button 鼠标按键
 * @return 操作结果
 */
Result<bool> MouseButtonUpInWindow(HWND windowHandle, int x, int y, MouseButton button);

// ============ 窗口内移动操作 ============

/**
 * @brief 在窗口客户区内移动
 * @param windowHandle 目标窗口句柄
 * @param endX 结束X坐标（客户区坐标）
 * @param endY 结束Y坐标（客户区坐标）
 * @param button 使用的鼠标按键
 * @return 操作结果
 */
Result<bool> MoveInWindow(HWND windowHandle, int endX, int endY, MouseButton button);

// ============ 窗口内滚轮操作 ============

/**
 * @brief 在窗口客户区内滚动
 * @param windowHandle 目标窗口句柄
 * @param x 客户区X坐标
 * @param y 客户区Y坐标
 * @param delta 滚动量（正值向上，负值向下）
 * @return 操作结果
 */
Result<bool> ScrollInWindow(HWND windowHandle, int x, int y, int delta);

}  // namespace MouseSimulator