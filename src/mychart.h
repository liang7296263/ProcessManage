#ifndef MYCHART_H
#define MYCHART_H

#include <QWidget>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QTimer>
#include <QValueAxis>
#include <QVBoxLayout>

class myChart : public QWidget
{
    Q_OBJECT
public:
    explicit myChart(const QString &type, QWidget *parent = nullptr);
    void setCpuOccupy(const QString &y);
    void setMemoryOccupy(const QString &y);
    void setExchangeOccupy(const QString &y);
    void paintEvent(QPaintEvent *event);

    int m_Xdata = 0;
    double m_Ydata = 0;

    void setCurve(const QString &y);
    void setaxisY(int y);
signals:
private:
    QString m_type;
    QChartView *m_chartView;
    QLineSeries *m_series;
    QChart *m_chart;
    QValueAxis *axisX;
    QValueAxis *axisY;
    void initChart();
};

#endif // MYCHART_H
