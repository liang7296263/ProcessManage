#include "mychart.h"
#include <QString>


myChart::myChart(const QString &type, QWidget *parent)
    : QWidget{parent}, m_type(type), m_chartView(new QChartView(this))
    , m_series(new QLineSeries()), m_chart(new QChart())
{
    this->resize(600, 100);
    initChart();
}

void myChart::initChart()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 设置 QChartView 背景透明
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setStyleSheet("background: transparent");

    // 设置 QChart 背景透明
    m_chart->setBackgroundBrush(Qt::NoBrush);
    m_chart->setBackgroundPen(Qt::NoPen);

    // 隐藏图表标题和图例
    m_chart->setTitle("");
    m_chart->legend()->hide();

    // 设置图表网格线颜色和样式
    axisX = new QValueAxis;
    axisY = new QValueAxis;
    axisX->setRange(0, 100);
    axisY->setRange(0, 100);

    // 设置网格线
    axisX->setTickCount(11);
    axisY->setTickCount(4);

    // 隐藏坐标轴的数字值
    axisX->setLabelsVisible(false);
    axisY->setLabelsVisible(false);

    // 隐藏网格线
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);

    // 将坐标轴设置为透明色
    axisX->setLinePenColor(Qt::transparent);
    axisY->setLinePenColor(Qt::transparent);

    // 设置系列颜色
    QPen pen;
    pen.setColor(Qt::yellow);
    m_series->setPen(pen);

    m_chart->addSeries(m_series); // 首先添加系列到图表

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignRight);

    // 将系列与轴关联
    m_series->attachAxis(axisX);
    m_series->attachAxis(axisY);

    m_chartView->setChart(m_chart);

    layout->addWidget(m_chartView);
    layout->setContentsMargins(0,0,0,0);
}

void myChart::setCpuOccupy(const QString &y)
{

}

void myChart::setMemoryOccupy(const QString &y)
{

}

void myChart::setExchangeOccupy(const QString &y)
{

}

void myChart::setCurve(const QString &y)
{
    /*if(m_type == "cpu使用率")
    {
        setCpuOccupy(y);
    }else if (m_type == "内存使用率")
    {
        setMemoryOccupy(y);
    }else
    {
        setExchangeOccupy(y);
    }*/
    // 去掉字符串中的百分号
    QString valueStr = y;
    valueStr.chop(1); // 去掉最后一个字符（百分号）

    // 将字符串转换为 double
    m_Ydata = valueStr.toDouble();

    qDebug() << "m_Ydata是： " << m_Ydata;

    m_series->append(m_Xdata,m_Ydata); // 使用 std::uniform_int_distribution 生成随机数
    if (m_series->count() > 100) {
        m_series->remove(0);
        axisX->setRange(m_Xdata - 100, m_Xdata);
    }
    m_Xdata++;
}

void myChart::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QBrush(QColor(0, 0, 0)));

    // 设置画笔颜色为黄色
    QPen pen;
    pen.setColor(Qt::yellow);

    pen.setWidthF(0.4);  // 可选：设置线宽(浮点数）
    painter.setPen(pen);

    int xline = 12;
    int xspace = 38;
    int yline = 3;
    int yspace = 25;
    for(int i = 0; i < xline; ++i)
    {
        painter.drawLine(xspace,0, xspace,this->height());
        xspace += 60;
    }

    for(int i = 0; i < yline; ++i)
    {
        painter.drawLine(0,yspace, this->width(),yspace);
        yspace += 33;
    }
    QWidget::paintEvent(event);
}

void myChart::setaxisY(int y)
{
    axisY->setRange(0,y);
}
