#ifndef MYSTATUSBAR_H
#define MYSTATUSBAR_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QProcess>
#include <QHBoxLayout>

class myStatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit myStatusBar(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void getCpuOccupy();
    void getMemoryOccupy();
private:
    QLabel *m_timeDisplay;
    QLabel *m_cpuDisplay;
    QLabel *m_memoryDisplay;
    QTimer *m_QTimer;

    void initTimeDisplay();
    void initCpuDisplay();
    void initMemoryDisplay();

signals:
private slots:
    void updateTimer();
};

#endif // MYSTATUSBAR_H
