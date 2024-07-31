#include "processinformation.h"
#include <QLabel>

processInformation::processInformation(QWidget *parent)
    : QWidget{parent}, m_NumberOfProcesses(new QLabel(this)), m_Qtimer(new QTimer(this))
    , m_SleepProcesses(new QLabel(this))
    , m_RunProcesses(new QLabel(this))
    , m_DeadProcesses(new QLabel(this))
    , m_searchEdit(new QTextEdit(this))
    , m_queryButton(new QPushButton(this))
    , m_refreshButton(new QPushButton(this))
    , m_endProcessButton(new QPushButton(this))
{
    this->setStyleSheet("QWidget { background-color: white; }");
    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20,20,20,20);

    initProcesses();    //初始化进程表
    // 初次更新
    updateProcessList();
    initStatistics();   //初始化统计信息
    initQueryKey();     //初始化查询组件

    //创建统计信息布局
    QHBoxLayout *statisticsLayout1 = new QHBoxLayout;
    QHBoxLayout *statisticsLayout2 = new QHBoxLayout;
    statisticsLayout1->addWidget(m_NumberOfProcesses);
    statisticsLayout1->addWidget(m_SleepProcesses);
    statisticsLayout2->addWidget(m_RunProcesses);
    statisticsLayout2->addWidget(m_DeadProcesses);

    //创建查询组件布局
    QHBoxLayout *queryLayout = new QHBoxLayout;
    queryLayout->addWidget(m_searchEdit);
    queryLayout->addWidget(m_queryButton);
    queryLayout->addWidget(m_refreshButton);
    queryLayout->addWidget(m_endProcessButton);

    //总部局设置
    mainLayout->addWidget(m_tableWidget);
    mainLayout->addLayout(statisticsLayout1);
    mainLayout->addLayout(statisticsLayout2);
    mainLayout->addLayout(queryLayout);

    // 链接定时器
    connect(m_Qtimer, &QTimer::timeout, this, &processInformation::updateProcessList);
    m_Qtimer->start(500); // 每0.5秒更新一次
}

void processInformation::updateProcessList()
{
    QProcess process;
    QStringList parameter;
    parameter << "-eo" << "pid,comm,state,ppid,%cpu,rss";
    process.start("ps", parameter);

    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split("\n");
    lines.removeFirst(); // 移除表头

    m_tableWidget->setRowCount(lines.size() - 1); // 更新行数

    //遍历命令输出，填充表格
    for (int i = 0; i < lines.size(); ++i) { //外层循环分割每行
        QString line = lines.at(i).simplified();
        QStringList columns = line.split(QRegularExpression("\\s+"));
        if (columns.size() < 6) continue;

        for (int j = 0; j < 6; ++j) {//内层循环填充每列到表格
            if (j == 5) { // 转换内存使用量为MB并转换为数值
                bool ok;
                double memoryKB = columns.at(j).toDouble(&ok);
                if (ok) {
                    double memoryMB = memoryKB / 1024.0;
                    m_tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(memoryMB, 'f', 1)));
                }
                else {
                    m_tableWidget->setItem(i, j, new QTableWidgetItem(columns.at(j)));
                }
            } else {
                m_tableWidget->setItem(i, j, new QTableWidgetItem(columns.at(j)));
            }
        }
    }

   // m_tableWidget->sortItems(4, Qt::DescendingOrder); //依据cpu使用率进行排序
    this->updateStatistics();
}

void processInformation::initProcesses()
{
    // 创建并配置表格
    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(6);
    QStringList headers;
    headers << "进程号" << "名称" << "状态" << "父进程" << "cpu占用(%)" << "占用内存(MB)";
    m_tableWidget->setHorizontalHeaderLabels(headers);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);   //表格的最后一列自动拉伸以填充可用空间
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置表格的选择行为为选择整行
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁用表格的编辑功能
    m_tableWidget->setSortingEnabled(true);                             //设置点击表头进行排序

    connect(m_tableWidget, &QTableWidget::itemSelectionChanged, this, &processInformation::onItemSelectionChanged);
}

void processInformation::initStatistics()
{
    setNumberOfProcesses();
    setSleepProcesses();
    setRunProcesses();
    setDeadProcesses();
}
QString processInformation::countValuesInColumn(int column, const QString& value)
{
    int count = 0;
    for(int row = 0; row < m_tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem* item = m_tableWidget->item(row, column);
        if(item && item->text() == value){
            ++count;
        }
    }
    QString number = QString::number(count);
    return number;
}    //筛选统计信息


void processInformation::setNumberOfProcesses()
{
    QString number = QString::number(m_tableWidget->rowCount());
    number.trimmed();
    m_NumberOfProcesses->setText("进程总数： " + number);
    m_NumberOfProcesses->setStyleSheet("QLabel { font-size: 14px; }"); // 设置字体大小
}    //设置进程总数显示
void processInformation::setSleepProcesses()
{

    QString number = countValuesInColumn(2, "S");
    number.trimmed();
    m_SleepProcesses->setText("睡眠进程： " + number);
    m_SleepProcesses->setStyleSheet("QLabel { font-size: 14px; }"); // 设置字体大小
}    //设置睡眠进程数显示
void processInformation::setRunProcesses()
{

    QString number = countValuesInColumn(2, "R");
    number.trimmed();
    m_RunProcesses->setText("运行进程： " + number);
    m_RunProcesses->setStyleSheet("QLabel { font-size: 14px; }"); // 设置字体大小
}    //设置运行进程总数显示
void processInformation::setDeadProcesses()
{

    QString number = countValuesInColumn(2, "Z");
    number.trimmed();
    m_DeadProcesses->setText("僵死进程： " + number);
    m_DeadProcesses->setStyleSheet("QLabel { font-size: 14px; }"); // 设置字体大小
}    //设置僵死进程总数显示

void processInformation::updateStatistics()
{

    QString NumberOfProcesses = QString::number(m_tableWidget->rowCount());
    QString SleepProcesses = countValuesInColumn(2, "S");
    QString RunProcesses = countValuesInColumn(2, "R");
    QString DeadProcesses = countValuesInColumn(2, "Z");
    if (!m_NumberOfProcesses) {
        qDebug() << "m_NumberOfProcesses is not initialized!";
        return;
    }
    m_NumberOfProcesses->setText("进程总数： " + NumberOfProcesses);
    m_SleepProcesses->setText("睡眠进程： " + SleepProcesses);
    m_RunProcesses->setText("运行进程： " + RunProcesses);
    m_DeadProcesses->setText("僵死进程： " + DeadProcesses);
}

void processInformation::initQueryKey()
{
    m_queryButton->setText("查询");
    m_refreshButton->setText("刷新");
    m_endProcessButton->setText("结束进程");
    m_searchEdit->setFixedHeight(25);
    m_searchEdit->setFixedWidth(300);
    m_searchEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(m_queryButton, &QPushButton::clicked, this, &processInformation::onQueryButtonClickd);
    connect(m_refreshButton, &QPushButton::clicked, this, &processInformation::onRefreshButtonClickd);
    connect(m_endProcessButton,&QPushButton::clicked, this, &processInformation::onEndProcessButtonClickd);
}

void processInformation::onQueryButtonClickd()
{
    QString searchText = m_searchEdit->toPlainText();;
    bool found = false;

    // 遍历表格的所有行
    for (int row = 0; row < m_tableWidget->rowCount(); ++row) {
        // 检查每一行的所有单元格是否包含搜索内容
        for (int column = 0; column < m_tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = m_tableWidget->item(row, column);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                // 选中匹配的行
                m_tableWidget->selectRow(row);
                m_tableWidget->scrollToItem(item);
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        // 如果没有找到匹配项
        m_tableWidget->clearSelection();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "错误提示", "没有找到这个进程", QMessageBox::Yes | QMessageBox::No);
    }
}

void processInformation::onRefreshButtonClickd()
{
    m_Qtimer->start(500); // 每0.5秒更新一次
}

void processInformation::onEndProcessButtonClickd()
{
    //获取选中的行
    QList<QTableWidgetItem*> selectedItems = m_tableWidget->selectedItems();
    QString firstColumnData;
    //获取选中行的索引
    if(!selectedItems.isEmpty())
    {
        int selectedRow = selectedItems.first()->row();
        QTableWidgetItem *firstColumnItem = m_tableWidget->item(selectedRow, 0);

        //获取该行第一列的单元格项
        if(firstColumnItem != nullptr)
        {
            firstColumnData = firstColumnItem->text();
        }
    }

    //通过获取的进程号，杀死进程
    qDebug() << "进程号是： " << firstColumnData;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "kill process提示", "是否杀死这个进程", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QProcess process;
        process.start("kill", QStringList() << firstColumnData);
        if (!process.waitForStarted()) {
            qDebug() << "查看进程是否被杀死";
        } else {
            process.waitForFinished();
            qDebug() << "Reboot process finished with output:" << process.readAll();
        }
    }else if(reply == QMessageBox::No)
    {
        m_Qtimer->start(500);
    }
}

void processInformation::onItemSelectionChanged()
{
    if (m_Qtimer->isActive()) {
        m_Qtimer->stop();
        qDebug() << "Timer stopped due to selection change";
    }
}
