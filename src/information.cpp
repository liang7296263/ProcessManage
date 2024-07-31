#include "information.h"
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
information::information(const QString &title, QWidget *parent)
    :QGroupBox(title,parent)
{
    initCpuOrSys();
    initLayout();
}

information::~information()
{

}

QString information::getGccVersion()
{
    QProcess process;
    process.start("gcc", QStringList() << "--version");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    QString gccVersion = output.split('\n').first(); // 获取输出的第一行
    return gccVersion;
}

QString information::getCpuModel()
{
    QProcess process;
    process.start("lscpu");
    if (!process.waitForFinished()) {
        qDebug() << "Failed to execute lscpu";
        return QString();
    }

    QString output = process.readAllStandardOutput();
    QStringList lines = output.split("\n");
    for (const QString &line : lines) {
        if (line.startsWith("型号名称：")) { // 根据中文字段查找
            return line.split("：").at(1).trimmed();
        }
    }
    return QString();
}//获取cpu型号
QString information::getCpuFrequency()
{
    QProcess process;
    process.start("lscpu");
    if (!process.waitForFinished()) {
        qDebug() << "Failed to execute lscpu";
        return QString();
    }

    QString output = process.readAllStandardOutput();
    QStringList lines = output.split("\n");
    for (const QString &line : lines) {
        if (line.startsWith("L3 缓存：")) { // 根据中文字段查找
            return line.split("：").at(1).trimmed();
        }
    }
    return QString();
}//获取cpu主频
QString information::getMemorySize()
{
    QProcess process;
    process.start("free", QStringList() << "-h");
    if (!process.waitForFinished()) {
        qDebug() << "Failed to execute free";
        return QString();
    }

    QString output = process.readAllStandardOutput();
    QStringList lines = output.split("\n");
    for (const QString &line : lines) {
        if (line.startsWith("内存：")) {
            QStringList fields = line.split(QRegularExpression("\\s+"));
            if (fields.size() > 1) {
                return fields.at(1); // 总内存容量
            }
        }
    }
    return QString();
}//获取内存大小

void information::initCpuOrSys()
{
    if(this->title() == "操作系统信息")
    {
        osTypeLabel = new QLabel("系统类型: " + QSysInfo::kernelType());        //类型
        kernelVersionLabel = new QLabel("内核版本: " + QSysInfo::kernelVersion()); //内核版本号
        gccVersionLabel = new QLabel("GCC编译器版本: " + this->getGccVersion());   //GCC编译器版本
    }else
    {
        cpuModelLabel = new QLabel("cpu型号: " + this->getCpuModel());
        cpuFrequencyLabel = new QLabel("L3 缓存: " + this->getCpuFrequency());
        memoryLabel = new QLabel("内存容量: " + this->getMemorySize());
    }
}

void information::initLayout()
{
    if(this->title() == "操作系统信息")
    {
        QVBoxLayout *groupBoxLayout = new QVBoxLayout;
        groupBoxLayout->addWidget(osTypeLabel);
        groupBoxLayout->addWidget(kernelVersionLabel);
        groupBoxLayout->addWidget(gccVersionLabel);

        this->setLayout(groupBoxLayout);
    }else
    {
        QVBoxLayout *groupBoxLayout = new QVBoxLayout;
        groupBoxLayout->addWidget(cpuModelLabel);
        groupBoxLayout->addWidget(cpuFrequencyLabel);
        groupBoxLayout->addWidget(memoryLabel);

        this->setLayout(groupBoxLayout);
    }
}
