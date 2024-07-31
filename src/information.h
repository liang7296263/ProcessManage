#ifndef INFORMATION_H
#define INFORMATION_H

#include <QGroupBox>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QSysInfo>
#include <QProcess>
#include <QFile>

class information: public QGroupBox
{
    Q_OBJECT
public:
    explicit information(const QString &title, QWidget *parent = nullptr);
    ~information();

    static QString getGccVersion();//获取gcc版本号
    static QString getCpuModel();//获取cpu型号
    static QString getCpuFrequency();//获取cpu主频
    static QString getMemorySize();//获取内存大小


private:
    //QLabel 系统类型
    QLabel *osTypeLabel;        //类型
    QLabel *kernelVersionLabel; //内核版本号
    QLabel *gccVersionLabel;    //GCC编译器版本

    QLabel *cpuModelLabel;
    QLabel *cpuTypeLabel;
    QLabel *cpuFrequencyLabel;
    QLabel *memoryLabel;


    QVBoxLayout *m_groupBoxLayout;
    //初始化信息
    void initCpuOrSys();

    //初始化布局
    void initLayout();

};

#endif // INFORMATION_H
