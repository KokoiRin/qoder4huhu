#pragma once

#include "CommonTypes.h"


/**
 * @namespace KeyboardSimulator
 * @brief 键盘输入基础功能
 * 
 * 提供最基础的键盘输入功能：
 * - 单个按键操作
 * - 基础文本输入
 * - 键盘状态检查
 */
namespace KeyboardSimulator {

// ============ 基础按键操作 ============

/**
 * @brief 模拟按键按下
 * @param windowHandle 目标窗口句柄
 * @param virtualKey 虚拟键码
 * @return 操作结果
 */
Result<bool> KeyDown(HWND windowHandle, UINT virtualKey);

/**
 * @brief 模拟按键释放
 * @param windowHandle 目标窗口句柄
 * @param virtualKey 虚拟键码
 * @return 操作结果
 */
Result<bool> KeyUp(HWND windowHandle, UINT virtualKey);

// ============ 文本输入 ============

/**
 * @brief 输入单个字符
 * @param windowHandle 目标窗口句柄
 * @param character 要输入的字符
 * @return 操作结果
 */
Result<bool> SendChar(HWND windowHandle, wchar_t character);

/**
 * @brief 输入文本字符串
 * @param windowHandle 目标窗口句柄
 * @param text 要输入的文本
 * @return 操作结果
 */
Result<bool> SendText(HWND windowHandle, const std::wstring& text);

// ============ 键盘状态 ============

/**
 * @brief 检查按键是否按下
 * @param virtualKey 虚拟键码
 * @return 按键状态
 */
Result<bool> IsKeyPressed(UINT virtualKey);

/**
 * @brief 检查CapsLock状态
 * @return CapsLock是否开启
 */
Result<bool> IsCapsLockOn();

/**
 * @brief 检查NumLock状态
 * @return NumLock是否开启
 */
Result<bool> IsNumLockOn();

}  // namespace KeyboardSimulator
