#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_controlGroup(nullptr)
    , m_controlLayout(nullptr)
    , m_getWindowListButton(nullptr)
    , m_statusLabel(nullptr)
    , m_resultGroup(nullptr)
    , m_resultLayout(nullptr)
    , m_resultTextEdit(nullptr)
    , m_windowCountLabel(nullptr)
{
    setupUI();
    connectSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // 设置窗口属性
    setWindowTitle("Windows API 工具 - 窗口管理器");
    setMinimumSize(800, 600);
    resize(1000, 700);

    // 创建中央部件
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    // 创建主布局
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(10);

    // 创建控制区域
    m_controlGroup = new QGroupBox("操作控制", this);
    m_controlLayout = new QHBoxLayout(m_controlGroup);
    
    m_getWindowListButton = new QPushButton("获取窗口列表", this);
    m_getWindowListButton->setMinimumHeight(40);
    m_getWindowListButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #0078d4;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #106ebe;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #005a9e;"
        "}"
    );
    
    m_statusLabel = new QLabel("准备就绪", this);
    m_statusLabel->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 12px;"
        "    padding: 5px;"
        "}"
    );
    
    m_controlLayout->addWidget(m_getWindowListButton);
    m_controlLayout->addWidget(m_statusLabel);
    m_controlLayout->addStretch();

    // 创建结果显示区域
    m_resultGroup = new QGroupBox("窗口列表", this);
    m_resultLayout = new QVBoxLayout(m_resultGroup);
    
    m_resultTextEdit = new QTextEdit(this);
    m_resultTextEdit->setReadOnly(true);
    m_resultTextEdit->setFont(QFont("Consolas", 9));
    m_resultTextEdit->setStyleSheet(
        "QTextEdit {"
        "    background-color: #f8f9fa;"
        "    border: 1px solid #dee2e6;"
        "    border-radius: 4px;"
        "    padding: 8px;"
        "}"
    );
    m_resultTextEdit->setPlaceholderText("点击\"获取窗口列表\"按钮来显示当前桌面上的所有窗口信息...");
    
    m_resultLayout->addWidget(m_resultTextEdit);

    // 添加到主布局
    m_mainLayout->addWidget(m_controlGroup);
    m_mainLayout->addWidget(m_resultGroup, 1); // 结果区域占据剩余空间

    // 创建状态栏
    m_windowCountLabel = new QLabel("窗口数量: 0", this);
    statusBar()->addWidget(m_windowCountLabel);
    statusBar()->showMessage("准备就绪");
}

void MainWindow::connectSignals()
{
    connect(m_getWindowListButton, &QPushButton::clicked, 
            this, &MainWindow::onGetWindowListClicked);
}

void MainWindow::onGetWindowListClicked()
{
    // TODO: 在这里实现获取窗口列表的逻辑
    // 目前只是显示占位符信息
    
    m_statusLabel->setText("正在获取窗口列表...");
    m_getWindowListButton->setEnabled(false);
    
    // 模拟数据 - 实际实现时会调用 DataLayer 的接口
    QString mockData = QString(
        "=== 桌面窗口列表 ===\n\n"
        "句柄: 0x12345678\n"
        "标题: 记事本\n"
        "类名: Notepad\n"
        "进程ID: 1234\n"
        "可见: 是\n"
        "位置: (100, 100) 大小: 800x600\n"
        "---\n\n"
        "句柄: 0x87654321\n"
        "标题: 计算器\n"
        "类名: ApplicationFrameWindow\n"
        "进程ID: 5678\n"
        "可见: 是\n"
        "位置: (200, 200) 大小: 400x300\n"
        "---\n\n"
        "句柄: 0xABCDEF00\n"
        "标题: Visual Studio Code\n"
        "类名: Chrome_WidgetWin_1\n"
        "进程ID: 9012\n"
        "可见: 是\n"
        "位置: (50, 50) 大小: 1200x800\n"
        "---\n"
    );
    
    m_resultTextEdit->setPlainText(mockData);
    
    // 更新状态
    m_statusLabel->setText("获取完成");
    m_windowCountLabel->setText("窗口数量: 3");
    statusBar()->showMessage("已获取 3 个窗口信息");
    
    m_getWindowListButton->setEnabled(true);
}