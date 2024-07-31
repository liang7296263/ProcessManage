#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include "mytitlebar.h"
#include <QPainterPath>
#include <QStackedWidget>
#include "performance.h"
#include "systeminformation.h"
#include "processinformation.h"
#include <QTabWidget>
#include "imagebutton.h"
#include "settingspage.h"
#include <QPushButton>
#include <QScreen>
#include "mystatusbar.h"

class BaseWindow : public QWidget
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

    QTabWidget *m_pTableWidget;

    performance *m_performance;
    processInformation *m_processInformation;
    systemInformation *m_systemInformation;
    void moveToCenter();


private:
    void initTitleBar();
    void initStatusBar();
    void paintEvent(QPaintEvent *event);
    void loadStyleSheet(const QString &sheetName);

    QGroupBox *m_groupBox;

    ImageButton *m_shutdownButton;
    ImageButton *m_restartButton;
    ImageButton *m_setButton;

    settingsPage *m_settingsPage;


private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();


    void onButtomSetClicked(); //设置按钮槽函数
    void onButtonShutDownClicked();
    void onButtonRestartClicked();
protected:
    myTitlebar* m_titleBar;
    myStatusBar* m_statusBar;

};
#endif // BASEWINDOW_H
