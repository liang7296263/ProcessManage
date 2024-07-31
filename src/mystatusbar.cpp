#include "mystatusbar.h"


myStatusBar::myStatusBar(QWidget *parent)
    : QWidget{parent}, m_timeDisplay(new QLabel(this))
    , m_cpuDisplay(new QLabel(this))
    , m_memoryDisplay(new QLabel(this))
    , m_QTimer(new QTimer(this))
{
    //设置状态栏的大小策略、固定高度以及窗口的样式标志
    this->setFixedHeight(20);
    this->setWindowFlags(Qt::FramelessWindowHint);

    //设置时间相关函数
    m_QTimer->start(1000);
    connect(m_QTimer, &QTimer::timeout, this, &myStatusBar::updateTimer);
    updateTimer(); // 初始化显示当前时间

    //设置布局
    QHBoxLayout *Layout = new QHBoxLayout;
    Layout->addWidget(m_timeDisplay);
    Layout->addWidget(m_cpuDisplay);
    Layout->addWidget(m_memoryDisplay);
    Layout->setContentsMargins(0,0,0,0);

    setLayout(Layout);
}

void myStatusBar::initTimeDisplay()
{

}
void myStatusBar::initCpuDisplay()
{

}
void myStatusBar::initMemoryDisplay()
{

}
void myStatusBar::updateTimer()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeString = currentTime.toString("yyyy-MM-dd HH:mm:ss");
    m_timeDisplay->setText(timeString);
    getCpuOccupy();
    getMemoryOccupy();
}

void myStatusBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int lineX = this->width();
    //painter.drawLine(QPoint(0,0), QPoint(lineX,0));
}

void myStatusBar::getCpuOccupy()
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << "top -bn1 | grep 'Cpu(s)' | awk '{print 100 - $8\"%\"}'");
    process.waitForFinished();
    QString output = process.readAllStandardOutput().trimmed();

    m_cpuDisplay->setText("CPU占用率： " + output);
}
void myStatusBar::getMemoryOccupy()
{
    QProcess process;
    process.start("bash", QStringList()<< "-c" << "LC_ALL=C free | awk '/Mem/ {printf(\"%.1f%%\\n\", $3/$2 * 100.0)}'");
    process.waitForFinished();
    QString output = process.readAllStandardOutput().trimmed();

    m_memoryDisplay->setText("内存占用率： " + output);
}
