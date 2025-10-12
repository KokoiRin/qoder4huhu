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
#include <QtCore/QTimer>

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

private:
    void setupUI();
    void connectSignals();

    // UI 组件
    QWidget* m_centralWidget;
    QVBoxLayout* m_mainLayout;
    
    // 控制区域
    QGroupBox* m_controlGroup;
    QHBoxLayout* m_controlLayout;
    QPushButton* m_getWindowListButton;
    QLabel* m_statusLabel;
    
    // 结果显示区域
    QGroupBox* m_resultGroup;
    QVBoxLayout* m_resultLayout;
    QTextEdit* m_resultTextEdit;
    
    // 状态栏信息
    QLabel* m_windowCountLabel;
};