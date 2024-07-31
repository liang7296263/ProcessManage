#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

enum buttonType
{
    MIN_BUTTON = 0,    // 最小化和关闭按钮;
    MIN_MAX_BUTTON,    // 最小化、最大化和关闭按钮;
    ONLY_CLOSE_BUTTON  // 最小化、最大化和关闭按钮;
};

class myTitlebar : public QWidget
{
    Q_OBJECT
public:
    explicit myTitlebar(QWidget *parent);
    ~myTitlebar();

    void setBackgroundColor(int r, int g, int b, bool isTransparent = false);    //设置标题栏背景色及是否透明
    void setTitleIcon(QString filePath, QSize iconSize = QSize(30, 30));         //设置标题图标
    void setTitleContent(QString titleContent, int titleFontSize= 12);            //设置标题内容及字体大小
    void setTitleWidth(int width);                                               //设置标题长度
    void setButtonType(buttonType button_type);                                  //设置标题按钮类型
    void setWindowBorderWidth(int borderWidth);                                  //设置窗口边框宽度;

    void setpButtonMinIcon(QString filePath, QSize iconSize = QSize(25, 25));         //设置最小化按钮图标
    void setpButtonMaxIcon(QString filePath, QSize iconSize = QSize(25, 25));         //设置最大化按钮图标
    void setpButtonRestoreIcon(QString filePath, QSize iconSize = QSize(25, 25));         //设置还原按钮图标
    void setpButtonCloseIcon(QString filePath, QSize iconSize = QSize(25, 25));         //设置还原按钮图标

    // 保存/获取 最大化前窗口的位置及大小;
    void saveRestoreInfo(const QPoint point, const QSize size);
    void getRestoreInfo(QPoint& point, QSize& size);

    //重写鼠标事件
    void mouseDoubleClickEvent(QMouseEvent *event) override;    //鼠标双击事件
    void mousePressEvent(QMouseEvent *event) override;          //鼠标按压事件
    void mouseMoveEvent(QMouseEvent *event) override;           //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event) override;        //鼠标释放事件

private:
    QLabel* m_pIcon;                    // 标题栏图标;
    QLabel* m_pTitleContent;            // 标题栏内容;
    QPushButton* m_pButtonMin;          // 最小化按钮;
    QPushButton* m_pButtonRestore;      // 最大化还原按钮;
    QPushButton* m_pButtonMax;          // 最大化按钮;
    QPushButton* m_pButtonClose;        // 关闭按钮;

    // 标题栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

    // 最大化，最小化变量;
    QPoint m_restorePos;
    QSize m_restoreSize;
    // 移动窗口的变量;
    bool m_isPressed;
    QPoint m_startMovePos;

    QPoint diff_pos; //鼠标和窗口的相对位移
    QPoint window_pos; //窗口的绝对位置
    QPoint mouse_pos; //鼠标的绝对位置

    // 标题栏内容;
    QString m_titleContent;
    // 按钮类型;
    buttonType m_buttonType;
    // 窗口边框宽度;
    int m_windowBorderWidth;
    // 标题栏是否透明;
    bool m_isTransparent;


    void paintEvent(QPaintEvent *event);



    // 初始化控件;
    void initControl();
    // 信号槽的绑定;
    void initConnections();
    // 加载样式文件;
    void loadStyleSheet(const QString &sheetName);
signals:
    // 按钮触发的信号;
    void signalButtonMinClicked();
    void signalButtonRestoreClicked();
    void signalButtonMaxClicked();
    void signalButtonCloseClicked();

private slots:
    // 按钮触发的槽;
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();
    //void onRollTitle();
};

#endif // MYTITLEBAR_H
