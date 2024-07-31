#ifndef PROCESSINFORMATION_H
#define PROCESSINFORMATION_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QTimer>
#include <QProcess>
#include <QDebug>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
class processInformation : public QWidget
{
    Q_OBJECT
public:
    explicit processInformation(QWidget *parent = nullptr);
    QString countValuesInColumn(int column, const QString& value);  //筛选统计信息
    void updateStatistics();


private:
    QTableWidget *m_tableWidget;
    QLabel *m_NumberOfProcesses;
    QLabel *m_SleepProcesses;
    QLabel *m_RunProcesses;
    QLabel *m_DeadProcesses;

    QTextEdit *m_searchEdit;
    QPushButton *m_queryButton;
    QPushButton *m_refreshButton;
    QPushButton *m_endProcessButton;

    void initProcesses();
    void initStatistics();
    void initQueryKey();

    void setNumberOfProcesses();    //设置进程总数显示
    void setSleepProcesses();    //设置睡眠进程数显示
    void setRunProcesses();    //设置运行进程总数显示
    void setDeadProcesses();    //设置僵死进程总数显示

    QTimer *m_Qtimer;
private slots:
    void updateProcessList();
    void onQueryButtonClickd();
    void onRefreshButtonClickd();
    void onEndProcessButtonClickd();
    void onItemSelectionChanged();
signals:
};

#endif // PROCESSINFORMATION_H
