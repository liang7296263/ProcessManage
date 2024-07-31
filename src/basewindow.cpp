#include "basewindow.h"
#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScreen>
#include <QMessageBox>


BaseWindow::BaseWindow(QWidget *parent)
    : QWidget(parent), m_setButton(nullptr), m_settingsPage(nullptr) // 初始化 m_setButton
{
    this->resize(800, 600);
    moveToCenter();

    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    // 设置窗口背景透明;
    setAttribute(Qt::WA_TranslucentBackground);

    //初始化标题栏;
    initTitleBar();
    //初始化状态栏
    initStatusBar();

    m_performance = new performance;
    m_processInformation = new processInformation;
    m_systemInformation = new systemInformation;

    m_pTableWidget = new QTabWidget(this);

    m_pTableWidget->setTabsClosable(false); // 设置标签页可关闭
    m_pTableWidget->setMovable(false); // 设置标签页不可移动
    m_pTableWidget->setTabPosition(QTabWidget::North); // 设置标签页位置在上方
    //m_pTableWidget->setTabShape(QTabWidget::Triangular); // 设置标签页形状为三角形

    m_pTableWidget->insertTab(0,m_systemInformation,"系统信息");
    m_pTableWidget->insertTab(1,m_processInformation,"进程信息");
    m_pTableWidget->insertTab(2,m_performance,"性能");

    m_shutdownButton = new ImageButton("/home/liang/下载/关机.png", QSize(30, 30));
    m_restartButton = new ImageButton("/home/liang/下载/重启.png", QSize(40, 40));
    m_setButton = new ImageButton("/home/liang/下载/设置.png", QSize(30, 30));

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addWidget(m_shutdownButton);
    HLayout->addWidget(m_restartButton);
    HLayout->addWidget(m_setButton);
    HLayout->setSpacing(40);
    HLayout->setAlignment(Qt::AlignLeft);


    QVBoxLayout* VLayout = new QVBoxLayout(this); // 创建一个垂直布局对象，并设置当前widget为其父组件
    VLayout->addLayout(HLayout);
    VLayout->addWidget(m_pTableWidget); // 将标签页控件添加到垂直布局中
    VLayout->addWidget(m_statusBar);
    VLayout->setSpacing(10);
    VLayout->setContentsMargins(20,50,20,5);


    connect(m_setButton, &QPushButton::clicked, this, &BaseWindow::onButtomSetClicked);
    connect(m_shutdownButton, &QPushButton::clicked, this, &BaseWindow::onButtonShutDownClicked);
    connect(m_restartButton, &QPushButton::clicked, this, &BaseWindow::onButtonRestartClicked);

}

BaseWindow::~BaseWindow()
{
    if (m_settingsPage != nullptr) {
        delete m_settingsPage;
    }
}

void BaseWindow::initTitleBar()
{
    m_titleBar = new myTitlebar(this);
    m_titleBar->move(0, 0);

    connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
    connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));


    //:/Resources/titleicon.png
    m_titleBar->setTitleIcon(":/Resources/titleicon.png");
    m_titleBar->setTitleContent(QStringLiteral("任务管理器"), 11);
    m_titleBar->setButtonType(MIN_MAX_BUTTON);
    m_titleBar->setTitleWidth(this->width());

    //设置按钮图标
    m_titleBar->setpButtonMinIcon(":/Resources/最小化.png");
    m_titleBar->setpButtonMaxIcon(":/Resources/最大化.png");
    m_titleBar->setpButtonCloseIcon(":/Resources/关闭小.png");
    m_titleBar->setpButtonRestoreIcon(":/Resources/win-恢复窗口.png");
}

void BaseWindow::initStatusBar()
{
    m_statusBar = new myStatusBar(this);
}
void BaseWindow::paintEvent(QPaintEvent* event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(245, 245, 245)));

    QWidget::paintEvent(event);
}

//暂未调用此函数
void BaseWindow::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/Resources/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

//下为按钮的槽函数实现
void BaseWindow::onButtonMinClicked()
{
    showMinimized();
}

void BaseWindow::onButtonRestoreClicked()
{
    QPoint windowPos;
    QSize windowSize;
    m_titleBar->getRestoreInfo(windowPos, windowSize);
    this->setGeometry(QRect(windowPos, windowSize));
}

void BaseWindow::onButtonMaxClicked()
{
    m_titleBar->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect desktopRect = screen->availableGeometry();
    QRect FactRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
    setGeometry(FactRect);
}

void BaseWindow::onButtonCloseClicked()
{
    close();
}

void BaseWindow::onButtomSetClicked()
{
    m_settingsPage = new settingsPage();
    if (!m_settingsPage) {
        qDebug() << "m_settingsPage is null";
        return;
    }
    m_settingsPage->show();
    m_settingsPage->raise();
    m_settingsPage->activateWindow();
    qDebug() << "Settings page shown";
}

void BaseWindow::onButtonShutDownClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "关机确认", "你确定要关机吗?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        QProcess::execute("shutdown", QStringList() << "-h" << "now");
        qDebug() << "关机";
    }
}

void BaseWindow::onButtonRestartClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "重启确认", "你确定要重启吗?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QProcess process;
        process.start("pkexec", QStringList() << "reboot");
        if (!process.waitForStarted()) {
            qDebug() << "Failed to start the reboot process.";
        } else {
            process.waitForFinished();
            qDebug() << "Reboot process finished with output:" << process.readAll();
        }
    }
}

void BaseWindow::moveToCenter()
{
    // 获取屏幕的大小
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    // 移动窗口
    this->move(x, y);
}
