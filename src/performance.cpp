#include "performance.h"
#include <QDebug>
performance::performance(QWidget *parent)
    : QWidget{parent}
{
    this->setStyleSheet("QWidget { background-color: white; }");

    initChart(); //初始化图表页
    initLable(); //初始化文字标签

    //创建布局并添加部件
    QVBoxLayout *Vlayout = new QVBoxLayout;
    Vlayout->addWidget(m_cpuOccupyLabel);
    Vlayout->addWidget(m_cpuOccupyChart);
    Vlayout->addWidget(m_memoryOccupyLabel);
    Vlayout->addWidget(m_memoryOccupyChart);
    Vlayout->addWidget(m_exchangeOccupyLabel);
    Vlayout->addWidget(m_exchangeOccupyChart);

    setLayout(Vlayout);

    m_Qtimer = new QTimer(this);
    connect(m_Qtimer, &QTimer::timeout, this, &performance::setCurve);
    m_Qtimer->start(1000);
}

void performance::initChart()
{
    m_cpuOccupyChart = new myChart("cpu使用率");
    m_cpuOccupyChart->setaxisY(10);
    m_memoryOccupyChart = new myChart("内存使用率");
    m_exchangeOccupyChart = new myChart("交换区使用率");
}
void performance::initLable()
{
    m_cpuOccupyLabel = new QLabel;
    m_cpuOccupyLabel->setText("cpu使用率");
    m_cpuOccupyLabel->setAlignment(Qt::AlignLeft);

    m_memoryOccupyLabel = new QLabel;
    m_memoryOccupyLabel->setText("内存使用率");
    m_memoryOccupyLabel->setAlignment(Qt::AlignLeft);

    m_exchangeOccupyLabel = new QLabel;
    m_exchangeOccupyLabel->setText("交换区使用率");
    m_exchangeOccupyLabel->setAlignment(Qt::AlignLeft);
}

void performance::setCurve()
{
    getCpuOccupy();
    getMemoryOccupy();
    getSwapOccupy();
}

void performance::getCpuOccupy()
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << "top -bn1 | grep 'Cpu(s)' | awk '{print 100 - $8\"%\"}'");
    process.waitForFinished();
    QString output = process.readAllStandardOutput().trimmed();
    qDebug() << "cup使用率是： " << output;
    m_cpuOccupyChart->setCurve(output);
}
void performance::getMemoryOccupy()
{
    QProcess process;
    process.start("bash", QStringList()<< "-c" << "LC_ALL=C free | awk '/Mem/ {printf(\"%.1f%%\\n\", $3/$2 * 100.0)}'");
    process.waitForFinished();
    QString output = process.readAllStandardOutput().trimmed();
    m_memoryOccupyChart->setCurve(output);
}

void performance::getSwapOccupy()
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << "LC_ALL=C free | awk '/Swap/ {printf(\"%.1f%%\\n\", $3/$2 * 100.0)}'");

    process.waitForFinished();
    QString output = process.readAllStandardOutput().trimmed();
    qDebug() << "交换区使用率是： " << output;
    m_exchangeOccupyChart->setCurve(output);
}
