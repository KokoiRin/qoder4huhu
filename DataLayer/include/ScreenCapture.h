#pragma once

#include "CommonTypes.h"

/**
 * @namespace ScreenCapture
 * @brief 屏幕捕获的基础功能
 * 
 * 提供简单、快速的屏幕捕获功能：
 * - 基础屏幕截图
 * - 基础窗口截图
 * - 基础文件操作
 */
namespace ScreenCapture {

/**
 * @brief 图像格式枚举
 */
enum class ImageFormat {
    BMP,        // Windows位图
    PNG,        // PNG格式
    JPEG        // JPEG格式
};

// ============ 基础截图功能 ============

/**
 * @brief 捕获整个屏幕
 * @return 图像数据结果
 */
Result<ImageData> CaptureScreen();

// ============ 窗口截图功能 ============

/**
 * @brief 捕获指定窗口
 * @param windowHandle 窗口句柄
 * @return 图像数据结果
 */
Result<ImageData> CaptureWindow(HWND windowHandle);

/**
 * @brief 捕获窗口客户区
 * @param windowHandle 窗口句柄
 * @return 图像数据结果
 */
Result<ImageData> CaptureWindowClient(HWND windowHandle);

/**
 * @brief 捕获窗口指定区域
 * @param windowHandle 窗口句柄
 * @param x 起始X坐标
 * @param y 起始Y坐标
 * @param width 宽度
 * @param height 高度
 * @return 图像数据结果
 */
Result<ImageData> CaptureRegion(HWND windowHandle, int x, int y, int width, int height);

}  // namespace ScreenCapture
