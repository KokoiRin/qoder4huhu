#include <windows.h>
#include <iostream>
#include <memory>

// 包含各层头文件
#include "CommonTypes.h"
#include "WindowManager.h"
#include "KeyboardSimulator.h"
#include "MouseSimulator.h"
#include "ScreenCapture.h"

using namespace WindowsAPI;

/**
 * @brief 主函数 - Windows API项目入口点
 */
int main(int argc, char* argv[])
{
    // 设置控制台输出为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    
    std::wcout << L"Windows API 四层架构项目启动中..." << std::endl;
    
    try 
    {
        std::wcout << L"\n正在进行基本功能测试..." << std::endl;
        
        // 测试窗口管理功能 - 直接调用命名空间函数
        auto activeWindow = WindowManager::GetActiveWindow();
        if (activeWindow.IsSuccess()) {
            std::wcout << L"✓ 获取到活动窗口" << std::endl;
            
            // 演示窗口位置和大小设置（注释掉避免实际操作）
            // WindowManager::SetWindowPosition(activeWindow.GetData(), 100, 100);
            // WindowManager::SetWindowSize(activeWindow.GetData(), 800, 600);
            // WindowManager::MinimizeWindow(activeWindow.GetData());
            // WindowManager::MaximizeWindow(activeWindow.GetData());
            // WindowManager::RestoreWindow(activeWindow.GetData());
            
            // 检查窗口状态
            auto isMaximized = WindowManager::IsWindowMaximized(activeWindow.GetData());
            auto isMinimized = WindowManager::IsWindowMinimized(activeWindow.GetData());
            auto isNormal = WindowManager::IsWindowNormal(activeWindow.GetData());
            
            if (isMaximized.IsSuccess() && isMinimized.IsSuccess() && isNormal.IsSuccess()) {
                std::wcout << L"✓ 窗口状态: ";
                if (isMaximized.GetData()) std::wcout << L"最大化 ";
                if (isMinimized.GetData()) std::wcout << L"最小化 ";
                if (isNormal.GetData()) std::wcout << L"正常 ";
                std::wcout << std::endl;
            }
            
            auto windowRect = WindowManager::GetWindowRect(activeWindow.GetData());
            if (windowRect.IsSuccess()) {
                auto rect = windowRect.GetData();
                std::wcout << L"✓ 窗口位置: (" << rect.left << L", " << rect.top 
                          << L"), 大小: " << rect.width() << L"x" << rect.height() << std::endl;
            }
        }
        
        // 测试屏幕捕获功能
        std::wcout << L"正在测试屏幕捕获功能..." << std::endl;
        
        // 演示捕获指定区域（注释掉避免实际捕获）
        // auto regionCapture = ScreenCapture::CaptureRegion(0, 0, 100, 100);
        // if (regionCapture.IsSuccess()) {
        //     std::wcout << L"✓ 成功捕获屏幕区域 (0,0,100,100)" << std::endl;
        // }
        
        // 测试鼠标在窗口内的操作
        if (activeWindow.IsSuccess()) {
            auto mouseInWindow = MouseSimulator::GetPositionInWindow(activeWindow.GetData());
            if (mouseInWindow.IsSuccess()) {
                auto pos = mouseInWindow.GetData();
                std::wcout << L"✓ 鼠标在活动窗口内的位置: (" << pos.x << L", " << pos.y << L")" << std::endl;
            }
            
            // 演示窗口内鼠标操作（注释掉避免实际操作）
            // MouseSimulator::ClickInWindow(activeWindow.GetData(), 50, 50, MouseButton::LEFT);
            // MouseSimulator::ScrollInWindow(activeWindow.GetData(), 100, 100, 3);
        }
        
        // 测试查找记事本窗口（如果存在）
        auto notepadWindow = WindowManager::FindWindowByTitle(L"记事本");
        if (notepadWindow.IsSuccess()) {
            std::wcout << L"✓ 找到记事本窗口" << std::endl;
            
            // 演示键盘输入（注释掉避免实际输入）
            // KeyboardSimulator::SendText(notepadWindow.GetData(), L"Hello from WindowsAPI!");
            
            // 演示鼠标在记事本窗口内的操作
            // MouseSimulator::ClickInWindow(notepadWindow.GetData(), 100, 100, MouseButton::LEFT);
        } else {
            std::wcout << L"ℹ 未找到记事本窗口（正常现象）" << std::endl;
        }
        
        std::wcout << L"\n基本功能测试完成！" << std::endl;
        std::wcout << L"\n=== 使用示例 ===" << std::endl;
        std::wcout << L"现在您可以直接使用以下命名空间中的函数：" << std::endl;
        std::wcout << L"- WindowsAPI::WindowManager::* (窗口管理)" << std::endl;
        std::wcout << L"- WindowsAPI::KeyboardSimulator::* (键盘模拟)" << std::endl;
        std::wcout << L"- WindowsAPI::MouseSimulator::* (鼠标模拟)" << std::endl;
        std::wcout << L"- WindowsAPI::ScreenCapture::* (屏幕捕获)" << std::endl;
        std::wcout << L"\n所有函数都可以直接调用，无需初始化或清理！" << std::endl;
        std::wcout << L"\n按任意键退出..." << std::endl;
        
        // 等待用户输入
        std::wcin.get();
        
        std::wcout << L"程序正常退出。" << std::endl;
        
    }
    catch (const std::exception& e) 
    {
        std::wcerr << L"程序运行时发生异常: " << e.what() << std::endl;
        return -1;
    }
    catch (...) 
    {
        std::wcerr << L"程序运行时发生未知异常" << std::endl;
        return -1;
    }
    
    return 0;
}