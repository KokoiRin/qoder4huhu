#include "../include/ScreenCapture.h"
#include <windows.h>

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
    
    // 使用PrintWindow捕获窗口
    Result<ImageData> CaptureUsingPrintWindow(HWND windowHandle, int width, int height, DWORD flags = 0) {
        HDC windowDC = GetDC(NULL);
        if (!windowDC) {
            return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to get screen DC");
        }
        
        HDC memDC = CreateCompatibleDC(windowDC);
        if (!memDC) {
            ReleaseDC(NULL, windowDC);
            return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to create memory DC");
        }
        
        HBITMAP hBitmap = CreateCompatibleBitmap(windowDC, width, height);
        if (!hBitmap) {
            DeleteDC(memDC);
            ReleaseDC(NULL, windowDC);
            return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to create bitmap");
        }
        
        HGDIOBJ oldBitmap = SelectObject(memDC, hBitmap);
        
        if (!PrintWindow(windowHandle, memDC, flags)) {
            SelectObject(memDC, oldBitmap);
            DeleteObject(hBitmap);
            DeleteDC(memDC);
            ReleaseDC(NULL, windowDC);
            return Result<ImageData>::Error(ErrorCode::CAPTURE_FAILED, L"Failed to print window");
        }
        
        auto result = ExtractImageDataFromBitmap(hBitmap, memDC, width, height);
        
        SelectObject(memDC, oldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(memDC);
        ReleaseDC(NULL, windowDC);
        
        return result;
    }
    
    // 使用BitBlt捕获屏幕区域（仅用于屏幕捕获）
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
    
    // 使用PrintWindow捕获窗口
    return CaptureUsingPrintWindow(windowHandle, width, height);
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
    
    // 使用PrintWindow捕获窗口客户区
    return CaptureUsingPrintWindow(windowHandle, width, height, PW_CLIENTONLY);
}

Result<ImageData> CaptureRegion(HWND windowHandle, int x, int y, int width, int height) {
    if (!IsWindow(windowHandle)) {
        return Result<ImageData>::Error(ErrorCode::INVALID_HANDLE, L"Invalid window handle");
    }
    
    if (width <= 0 || height <= 0) {
        return Result<ImageData>::Error(ErrorCode::INVALID_PARAMETER, L"Invalid region dimensions");
    }
    
    // 获取窗口尺寸
    RECT windowRect;
    if (!GetWindowRect(windowHandle, &windowRect)) {
        return Result<ImageData>::Error(ErrorCode::OPERATION_FAILED, L"Failed to get window rect");
    }
    
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;
    
    // 检查区域是否超出窗口范围
    if (x + width > windowWidth || y + height > windowHeight) {
        return Result<ImageData>::Error(ErrorCode::INVALID_PARAMETER, L"Region extends beyond window bounds");
    }
    
    // 先捕获整个窗口
    auto fullWindowResult = CaptureUsingPrintWindow(windowHandle, windowWidth, windowHeight);
    if (!fullWindowResult.IsSuccess()) {
        return fullWindowResult;
    }
    
    auto fullImage = fullWindowResult.GetData();
    
    // 裁剪出指定区域
    ImageData regionImage;
    regionImage.width = width;
    regionImage.height = height;
    regionImage.bitsPerPixel = fullImage.bitsPerPixel;
    regionImage.stride = width * 4; // 32位每像素
    
    int regionDataSize = regionImage.stride * height;
    regionImage.data.resize(regionDataSize);
    
    // 复制指定区域的数据
    for (int row = 0; row < height; row++) {
        int srcRowOffset = (y + row) * fullImage.stride + x * 4;
        int dstRowOffset = row * regionImage.stride;
        
        if (srcRowOffset + width * 4 <= (int)fullImage.data.size()) {
            memcpy(&regionImage.data[dstRowOffset], &fullImage.data[srcRowOffset], width * 4);
        }
    }
    
    return Result<ImageData>::Success(regionImage);
}

}  // namespace ScreenCapture