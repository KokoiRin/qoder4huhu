#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QListWidgetItem>
#include <QtCore/QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_controlGroup(nullptr)
    , m_controlLayout(nullptr)
    , m_buttonLayout(nullptr)
    , m_getWindowListButton(nullptr)
    , m_bindWindowButton(nullptr)
    , m_statusLabel(nullptr)
    , m_windowListGroup(nullptr)
    , m_windowListLayout(nullptr)
    , m_windowListWidget(nullptr)
    , m_bindInfoGroup(nullptr)
    , m_bindInfoLayout(nullptr)
    , m_bindInfoLabel(nullptr)
    , m_windowCountLabel(nullptr)
    , m_windowController(nullptr)
{
    // 初始化业务控制器
    m_windowController = new WindowController();
    
    setupUI();
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete m_windowController;
}

void MainWindow::setupUI()
{
    // 设置窗口属性
    setWindowTitle("窗口管理器 - Windows API 工具");
    setMinimumSize(900, 700);
    resize(1100, 800);

    // 创建中央部件
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    // 创建主布局
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(10);

    // 创建控制区域
    m_controlGroup = new QGroupBox("操作控制", this);
    m_controlLayout = new QVBoxLayout(m_controlGroup);
    
    // 按钮布局
    m_buttonLayout = new QHBoxLayout();
    
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
    
    m_bindWindowButton = new QPushButton("绑定选中窗口", this);
    m_bindWindowButton->setMinimumHeight(40);
    m_bindWindowButton->setEnabled(false);  // 初始状态不可用
    m_bindWindowButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #28a745;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #218838;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #1e7e34;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #6c757d;"
        "    color: #adb5bd;"
        "}"
    );
    
    m_buttonLayout->addWidget(m_getWindowListButton);
    m_buttonLayout->addWidget(m_bindWindowButton);
    m_buttonLayout->addStretch();
    
    m_statusLabel = new QLabel("准备就绪", this);
    m_statusLabel->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 12px;"
        "    padding: 5px;"
        "}"
    );
    
    m_controlLayout->addLayout(m_buttonLayout);
    m_controlLayout->addWidget(m_statusLabel);

    // 创建窗口列表区域
    m_windowListGroup = new QGroupBox("窗口列表（双击选择窗口）", this);
    m_windowListLayout = new QVBoxLayout(m_windowListGroup);
    
    m_windowListWidget = new QListWidget(this);
    m_windowListWidget->setAlternatingRowColors(true);
    m_windowListWidget->setStyleSheet(
        "QListWidget {"
        "    background-color: #f8f9fa;"
        "    border: 1px solid #dee2e6;"
        "    border-radius: 4px;"
        "    selection-background-color: #007bff;"
        "    selection-color: white;"
        "}"
        "QListWidget::item {"
        "    padding: 8px;"
        "    border-bottom: 1px solid #e9ecef;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #007bff;"
        "    color: white;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #e9ecef;"
        "}"
    );
    
    m_windowListLayout->addWidget(m_windowListWidget);

    // 创建绑定信息区域
    m_bindInfoGroup = new QGroupBox("绑定信息", this);
    m_bindInfoLayout = new QVBoxLayout(m_bindInfoGroup);
    
    m_bindInfoLabel = new QLabel("当前没有绑定任何窗口", this);
    m_bindInfoLabel->setStyleSheet(
        "QLabel {"
        "    color: #6c757d;"
        "    font-size: 12px;"
        "    padding: 10px;"
        "    background-color: #f8f9fa;"
        "    border: 1px solid #dee2e6;"
        "    border-radius: 4px;"
        "}"
    );
    m_bindInfoLabel->setWordWrap(true);
    
    m_bindInfoLayout->addWidget(m_bindInfoLabel);

    // 添加到主布局
    m_mainLayout->addWidget(m_controlGroup);
    m_mainLayout->addWidget(m_windowListGroup, 2); // 窗口列表占据主要空间
    m_mainLayout->addWidget(m_bindInfoGroup);

    // 创建状态栏
    m_windowCountLabel = new QLabel("窗口数量: 0", this);
    statusBar()->addWidget(m_windowCountLabel);
    statusBar()->showMessage("准备就绪");
}

void MainWindow::connectSignals()
{
    connect(m_getWindowListButton, &QPushButton::clicked, 
            this, &MainWindow::onGetWindowListClicked);
    
    connect(m_bindWindowButton, &QPushButton::clicked,
            this, &MainWindow::onBindWindowClicked);
    
    connect(m_windowListWidget, &QListWidget::itemSelectionChanged,
            this, &MainWindow::onWindowSelectionChanged);
}

void MainWindow::onGetWindowListClicked()
{
    m_statusLabel->setText("正在获取窗口列表...");
    m_getWindowListButton->setEnabled(false);
    m_windowListWidget->clear();
    m_currentWindowList.clear();
    
    // 调用WindowController获取窗口列表
    auto result = m_windowController->GetTopLevelWindowList();
    
    if (result.IsSuccess()) {
        const auto& windowList = result.GetData();
        m_currentWindowList = windowList;
        
        // 在UI中显示窗口列表
        for (size_t i = 0; i < windowList.size(); ++i) {
            const auto& window = windowList[i];
            
            // 创建列表项
            QListWidgetItem* item = new QListWidgetItem();
            
            // 设置显示文本（使用QString::fromStdWString转换）
            QString displayText = QString::fromStdWString(window.displayText);
            item->setText(displayText);
            
            // 将索引存储在item的data中
            item->setData(Qt::UserRole, static_cast<int>(i));
            
            // 添加到列表中
            m_windowListWidget->addItem(item);
        }
        
        // 更新状态
        m_statusLabel->setText("获取完成");
        m_windowCountLabel->setText(QString("窗口数量: %1").arg(windowList.size()));
        statusBar()->showMessage(QString("已获取 %1 个窗口信息").arg(windowList.size()));
        
    } else {
        // 处理错误
        QString errorMsg = QString::fromStdWString(result.GetErrorMessage());
        m_statusLabel->setText("获取失败: " + errorMsg);
        
        QMessageBox::warning(this, "错误", 
                           "获取窗口列表失败:\n" + errorMsg);
        
        statusBar()->showMessage("获取窗口列表失败");
    }
    
    m_getWindowListButton->setEnabled(true);
}

void MainWindow::onWindowSelectionChanged()
{
    // 检查是否有选中的窗口
    QListWidgetItem* currentItem = m_windowListWidget->currentItem();
    m_bindWindowButton->setEnabled(currentItem != nullptr);
}

void MainWindow::onBindWindowClicked()
{
    QListWidgetItem* currentItem = m_windowListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "警告", "请先选择一个窗口！");
        return;
    }
    
    // 获取选中窗口的索引
    int windowIndex = currentItem->data(Qt::UserRole).toInt();
    if (windowIndex < 0 || windowIndex >= static_cast<int>(m_currentWindowList.size())) {
        QMessageBox::warning(this, "错误", "无效的窗口选择！");
        return;
    }
    
    const auto& selectedWindow = m_currentWindowList[windowIndex];
    
    m_statusLabel->setText("正在绑定窗口...");
    m_bindWindowButton->setEnabled(false);
    
    // 调用WindowController绑定窗口
    auto bindResult = m_windowController->BindSelectedWindow(selectedWindow.handle);
    
    if (bindResult.IsSuccess()) {
        // 绑定成功，获取绑定信息
        auto infoResult = m_windowController->GetBoundWindowInfo();
        if (infoResult.IsSuccess()) {
            QString bindInfo = QString::fromStdWString(infoResult.GetData());
            m_bindInfoLabel->setText(bindInfo);
            m_bindInfoLabel->setStyleSheet(
                "QLabel {"
                "    color: #28a745;"
                "    font-size: 12px;"
                "    padding: 10px;"
                "    background-color: #d4edda;"
                "    border: 1px solid #c3e6cb;"
                "    border-radius: 4px;"
                "}"
            );
            
            m_statusLabel->setText("绑定成功！");
            statusBar()->showMessage("窗口绑定成功");
            
            // 显示成功消息
            QMessageBox::information(this, "成功", 
                                   "窗口绑定成功！\n\n" + bindInfo);
        } else {
            m_bindInfoLabel->setText("绑定成功，但获取信息失败");
            m_statusLabel->setText("绑定成功");
        }
    } else {
        // 绑定失败
        QString errorMsg = QString::fromStdWString(bindResult.GetErrorMessage());
        m_bindInfoLabel->setText("绑定失败: " + errorMsg);
        m_bindInfoLabel->setStyleSheet(
            "QLabel {"
            "    color: #dc3545;"
            "    font-size: 12px;"
            "    padding: 10px;"
            "    background-color: #f8d7da;"
            "    border: 1px solid #f5c6cb;"
            "    border-radius: 4px;"
            "}"
        );
        
        m_statusLabel->setText("绑定失败");
        statusBar()->showMessage("窗口绑定失败");
        
        QMessageBox::warning(this, "错误", 
                           "绑定窗口失败:\n" + errorMsg);
    }
    
    m_bindWindowButton->setEnabled(true);
}