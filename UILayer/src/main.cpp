#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("Windows API 工具");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Your Organization");

    // 创建并显示主窗口
    MainWindow window;
    window.show();

    return app.exec();
}