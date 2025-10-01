#include "../include/ScreenCapture.h"
#include <windows.h>

using namespace WindowsAPI;

namespace ScreenCapture {

// 内部辅助函数
namespace {
    // 从HBITMAP提取图像数据
    Result<ImageData> ExtractImageDataFromBitmap(HBITMAP hBitmap, HDC hdc, int width, int height) {
        ImageData imageData;
        imageData.width = width;
        imageData.height = height;
        imageData.bitsPerPixel = 32; // 使用32位格式
        imageData.stride = width * 4; // 每行字节数
        
        // 分配内存
        int dataSize = imageData.stride * imageData.height;
        imageData.data.resize(dataSize);
        
        // 创建位图信息头
        BITMAPINFOHEADER bi = {};
        bi.biSize = sizeof(BITMAPINFOHEADER);
        bi.biWidth = width;
        bi.biHeight = -height; // 负值表示自上而下的位图
        bi.biPlanes = 1;
        bi.biBitCount = 32;
        bi.biCompression = BI_RGB;
        
        // 获取位图数据
        if (!GetDIBits(hdc, hBitmap, 0, height, imageData.data.data(),
                      (BITMAPINFO*)&bi, DIB_RGB_COLORS)) {
            return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to get bitmap bits");
        }
        
        return Result<ImageData>::Success(imageData);
    }
    
    // 使用BitBlt捕获指定区域
    Result<ImageData> CaptureUsingBitBlt(HDC sourceDC, int x, int y, int width, int height) {
        HDC memDC = CreateCompatibleDC(sourceDC);
        if (!memDC) {
            return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to create memory DC");
        }
        
        HBITMAP hBitmap = CreateCompatibleBitmap(sourceDC, width, height);
        if (!hBitmap) {
            DeleteDC(memDC);
            return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to create bitmap");
        }
        
        HGDIOBJ oldBitmap = SelectObject(memDC, hBitmap);
        
        if (!BitBlt(memDC, 0, 0, width, height, sourceDC, x, y, SRCCOPY)) {
            SelectObject(memDC, oldBitmap);
            DeleteObject(hBitmap);
            DeleteDC(memDC);
            return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to copy bitmap");
        }
        
        auto result = ExtractImageDataFromBitmap(hBitmap, memDC, width, height);
        
        SelectObject(memDC, oldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(memDC);
        
        return result;
    }
}

// ============ 基础截图功能 ============

Result<ImageData> CaptureScreen() {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    HDC screenDC = GetDC(NULL);
    if (!screenDC) {
        return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to get screen DC");
    }
    
    auto result = CaptureUsingBitBlt(screenDC, 0, 0, screenWidth, screenHeight);
    
    ReleaseDC(NULL, screenDC);
    
    return result;
}

// ============ 窗口截图功能 ============

Result<ImageData> CaptureWindow(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<ImageData>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    RECT windowRect;
    if (!GetWindowRect(windowHandle, &windowRect)) {
        return Result<ImageData>::Error(ErrorCode::OPERATION_FAILED, L"Failed to get window rect");
    }
    
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;
    
    if (width <= 0 || height <= 0) {
        return Result<ImageData>::Error(ErrorCode::INVALID_PARAMETER, L"Invalid window dimensions");
    }
    
    HDC windowDC = GetWindowDC(windowHandle);
    if (!windowDC) {
        return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to get window DC");
    }
    
    auto result = CaptureUsingBitBlt(windowDC, 0, 0, width, height);
    
    ReleaseDC(windowHandle, windowDC);
    
    return result;
}

Result<ImageData> CaptureWindowClient(HWND windowHandle) {
    if (!IsWindow(windowHandle)) {
        return Result<ImageData>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    RECT clientRect;
    if (!GetClientRect(windowHandle, &clientRect)) {
        return Result<ImageData>::Error(ErrorCode::OPERATION_FAILED, L"Failed to get client rect");
    }
    
    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;
    
    if (width <= 0 || height <= 0) {
        return Result<ImageData>::Error(ErrorCode::INVALID_PARAMETER, L"Invalid client dimensions");
    }
    
    HDC clientDC = GetDC(windowHandle);
    if (!clientDC) {
        return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to get client DC");
    }
    
    auto result = CaptureUsingBitBlt(clientDC, 0, 0, width, height);
    
    ReleaseDC(windowHandle, clientDC);
    
    return result;
}

Result<ImageData> CaptureRegion(HWND windowHandle, int x, int y, int width, int height) {
    if (!IsWindow(windowHandle)) {
        return Result<ImageData>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    if (width <= 0 || height <= 0) {
        return Result<ImageData>::Error(ErrorCode::INVALID_PARAMETER, L"Invalid region dimensions");
    }
    
    HDC windowDC = GetDC(windowHandle);
    if (!windowDC) {
        return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to get window DC");
    }
    
    auto result = CaptureUsingBitBlt(windowDC, x, y, width, height);
    
    ReleaseDC(windowHandle, windowDC);
    
    return result;
}

}  // namespace ScreenCapture