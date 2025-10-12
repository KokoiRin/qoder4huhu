#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMessageBox>
#include <QtCore/QTimer>
#include "WindowController.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGetWindowListClicked();
    void onBindWindowClicked();
    void onWindowSelectionChanged();

private:
    void setupUI();
    void connectSignals();

    // UI 组件
    QWidget* m_centralWidget;
    QVBoxLayout* m_mainLayout;
    
    // 控制区域
    QGroupBox* m_controlGroup;
    QVBoxLayout* m_controlLayout;
    QHBoxLayout* m_buttonLayout;
    QPushButton* m_getWindowListButton;
    QPushButton* m_bindWindowButton;
    QLabel* m_statusLabel;
    
    // 窗口列表区域
    QGroupBox* m_windowListGroup;
    QVBoxLayout* m_windowListLayout;
    QListWidget* m_windowListWidget;
    
    // 绑定信息区域
    QGroupBox* m_bindInfoGroup;
    QVBoxLayout* m_bindInfoLayout;
    QLabel* m_bindInfoLabel;
    
    // 状态栏信息
    QLabel* m_windowCountLabel;
    
    // 业务控制器
    WindowController* m_windowController;
    
    // 当前窗口列表数据
    std::vector<WindowController::WindowListItem> m_currentWindowList;
};