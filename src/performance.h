#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <QWidget>
#include "mychart.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QProcess>

class performance : public QWidget
{
    Q_OBJECT
public:
    explicit performance(QWidget *parent = nullptr);
signals:
private:
    myChart *m_cpuOccupyChart;
    myChart *m_memoryOccupyChart;
    myChart *m_exchangeOccupyChart;

    QLabel *m_cpuOccupyLabel;
    QLabel *m_memoryOccupyLabel;
    QLabel *m_exchangeOccupyLabel;

    QTimer *m_Qtimer;

    void initChart();
    void initLable();

    void getCpuOccupy();
    void getMemoryOccupy();
    void getSwapOccupy();
private slots:
    void setCurve();
};

#endif // PERFORMANCE_H
