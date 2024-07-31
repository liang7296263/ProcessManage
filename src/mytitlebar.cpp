#include "mytitlebar.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QFile>
#include <QMouseEvent>
#include <QPainterPath>
#include <QDebug>

#define BUTTON_HEIGHT 30		// 按钮高度;
#define BUTTON_WIDTH 30			// 按钮宽度;
#define TITLE_HEIGHT 30			// 标题栏高度;

myTitlebar::myTitlebar(QWidget *parent)
    : QWidget{parent}
    , m_colorR(200)
    , m_colorG(200)
    , m_colorB(200)
    , m_isPressed(false)
    , m_buttonType(MIN_MAX_BUTTON)
    , m_windowBorderWidth(0)
    , m_isTransparent(false)
{
    // 初始化;
    initControl();
    initConnections();
    // 加载本地样式 MyTitle.css文件;
    //loadStyleSheet("MyTitle");

}

myTitlebar::~myTitlebar()
{

}

// 初始化控件;
void myTitlebar::initControl()
{
    m_pIcon = new QLabel;
    m_pTitleContent = new QLabel;

    m_pButtonMin = new QPushButton;
    m_pButtonRestore = new QPushButton;
    m_pButtonMax = new QPushButton;
    m_pButtonClose = new QPushButton;

    //设置按钮的固定大小
    m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    //设置了各个控件（如标题内容和按钮）的对象名称(为了在 Qt 的样式表（QSS）中能够方便地选择和定制这些控件的样式)
    m_pTitleContent->setObjectName("TitleContent");
    m_pButtonMin->setObjectName("ButtonMin");
    m_pButtonRestore->setObjectName("ButtonRestore");
    m_pButtonMax->setObjectName("ButtonMax");
    m_pButtonClose->setObjectName("ButtonClose");

    //设置按钮的工具提示
    m_pButtonMin->setToolTip(QStringLiteral("最小化"));
    m_pButtonRestore->setToolTip(QStringLiteral("还原"));
    m_pButtonMax->setToolTip(QStringLiteral("最大化"));
    m_pButtonClose->setToolTip(QStringLiteral("关闭"));

    //设置标题内容/图标/按钮的布局
    QHBoxLayout* mylayout = new QHBoxLayout(this);
    mylayout->addWidget(m_pIcon);
    mylayout->addWidget(m_pTitleContent);

    mylayout->addWidget(m_pButtonMin);
    mylayout->addWidget(m_pButtonRestore);
    mylayout->addWidget(m_pButtonMax);
    mylayout->addWidget(m_pButtonClose);

    mylayout->setContentsMargins(5, 0, 0, 0);
    mylayout->setSpacing(0);

    //设置标题栏的大小策略、固定高度以及窗口的样式标志
    m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(TITLE_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);


}

//信号和槽的绑定
void myTitlebar::initConnections()
{
    connect(m_pButtonMin, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
    connect(m_pButtonRestore, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_pButtonMax, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
    connect(m_pButtonClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
}

// 设置标题栏背景色,在paintEvent事件中进行绘制标题栏背景色;
// 在构造函数中给了默认值，可以外部设置颜色值改变标题栏背景色;
void myTitlebar::setBackgroundColor(int r, int g, int b, bool isTransparent)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    m_isTransparent = isTransparent;
    // 重新绘制（调用paintEvent事件）;
    update();
}

// 设置标题栏图标;
void myTitlebar::setTitleIcon(QString filePath, QSize IconSize)
{
    QPixmap titleIcon(filePath);
    m_pIcon->setPixmap(titleIcon.scaled(IconSize));
}

//设置最小化按钮图标
void myTitlebar::setpButtonMinIcon(QString filePath, QSize iconSize)
{

    QIcon ButtonIcon(filePath);
    m_pButtonMin->setIcon(ButtonIcon);
    //m_pButtonMin->setStyleSheet("QPushButton { background-color: rgba(153, 153, 153, 255); }");
    m_pButtonMin->setStyleSheet( "QPushButton {""  background-color: rgba(200, 200, 200, 255);"
                                "  border-radius: 1;" // 设置边框半径为按钮大小的一半，按钮将变为圆形
                      "}");
}

//设置最大化按钮图标
void myTitlebar::setpButtonMaxIcon(QString filePath, QSize iconSize)
{

    QIcon ButtonIcon(filePath);
    m_pButtonMax->setIcon(ButtonIcon);
    //m_pButtonMin->setStyleSheet("QPushButton { background-color: rgba(200, 200, 200, 255); }");
    m_pButtonMax->setStyleSheet( "QPushButton {"
                                "  background-color: rgba(200, 200, 200, 255);"
                                "  border-radius: 1;" // 设置边框半径为按钮大小的一半，按钮将变为圆形
                                "}");
}

//设置恢复按钮图标
void myTitlebar::setpButtonRestoreIcon(QString filePath, QSize iconSize)
{

    QIcon ButtonIcon(filePath);
    m_pButtonRestore->setIcon(ButtonIcon);
    //m_pButtonMin->setStyleSheet("QPushButton { background-color: rgba(153, 153, 153, 255); }");
    m_pButtonRestore->setStyleSheet( "QPushButton {"
                                "  background-color: rgba(200, 200, 200, 255);"
                                "  border-radius: 1;" // 设置边框半径为按钮大小的一半，按钮将变为圆形
                                "}");
}



//设置关闭按钮图标
void myTitlebar::setpButtonCloseIcon(QString filePath, QSize iconSize)
{
    QIcon ButtonIcon(filePath);
    m_pButtonClose->setIcon(ButtonIcon);
    m_pButtonClose->setStyleSheet( "QPushButton {"
                                  "  background-color: rgba(200, 200, 200, 255);"
                                  "  border-radius: 1;" // 设置边框半径为按钮大小的一半，按钮将变为圆形
                                  "}");
}

// 设置标题内容;
void myTitlebar::setTitleContent(QString titleContent, int titleFontSize)
{
    // 设置标题字体大小;
    QFont font = m_pTitleContent->font();
    font.setPointSize(titleFontSize);
    m_pTitleContent->setFont(font);
    // 设置标题内容;
    m_pTitleContent->setText(titleContent);
    m_titleContent = titleContent;
}

// 设置标题栏长度;
void myTitlebar::setTitleWidth(int width)
{
    this->setFixedWidth(width);
}

// 设置标题栏上按钮类型;
// 由于不同窗口标题栏上的按钮都不一样，所以可以自定义标题栏中的按钮;
// 这里提供了四个按钮，分别为最小化、还原、最大化、关闭按钮，如果需要其他按钮可自行添加设置;
void myTitlebar::setButtonType(buttonType buttonType)
{
    m_buttonType = buttonType;

    switch (buttonType)
    {
    case MIN_BUTTON:
    {
        m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
    }
    break;
    case MIN_MAX_BUTTON:
    {
        m_pButtonRestore->setVisible(false);
    }
    break;
    case ONLY_CLOSE_BUTTON:
    {
        m_pButtonMin->setVisible(false);
        m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
    }
    break;
    default:
        break;
    }
}

// 设置窗口边框宽度;
void myTitlebar::setWindowBorderWidth(int borderWidth)
{
    m_windowBorderWidth = borderWidth;
}

// 保存窗口最大化前窗口的位置以及大小;
void myTitlebar::saveRestoreInfo(const QPoint point, const QSize size)
{
    m_restorePos = point;
    m_restoreSize = size;
}

// 获取窗口最大化前窗口的位置以及大小;
void myTitlebar::getRestoreInfo(QPoint& point, QSize& size)
{
    point = m_restorePos;
    size = m_restoreSize;
}

// 绘制标题栏背景色;
void myTitlebar::paintEvent(QPaintEvent *event)
{
    // 是否设置标题透明;
    if (!m_isTransparent)
    {
        //设置背景色;
        QPainter painter(this);
        QPainterPath pathBack;
        pathBack.setFillRule(Qt::WindingFill);
        pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    }

    // 当窗口最大化或者还原后，窗口长度变了，标题栏的长度应当一起改变;
    // 这里减去m_windowBorderWidth ，是因为窗口可能设置了不同宽度的边框;
    // 如果窗口有边框则需要设置m_windowBorderWidth的值，否则m_windowBorderWidth默认为0;
    if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth))
    {
        this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
    }
    QWidget::paintEvent(event);
}

// 双击响应事件，主要是实现双击标题栏进行最大化和最小化操作;
void myTitlebar::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 只有存在最大化、还原按钮时双击才有效;
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态;
        // 或者通过单独设置变量来表示当前窗口状态;
        if (m_pButtonMax->isVisible())
        {
            onButtonMaxClicked();
        }
        else
        {
            onButtonRestoreClicked();
        }
    }

    return QWidget::mouseDoubleClickEvent(event);
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果;
void myTitlebar::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }

    return QWidget::mousePressEvent(event);

}
//将父窗口坐标设置为跟随鼠标移动，且维护当前坐标变量
void myTitlebar::mouseMoveEvent(QMouseEvent *event)
{
    /*if (m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }
    return QWidget::mouseMoveEvent(event);*/

    if (m_isPressed)
    {
        QPoint movePos = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePos.x(), widgetPos.y() + movePos.y());
        //move(widgetPos.x() + movePos.x(), widgetPos.y() + movePos.y());
    }

    return QWidget::mouseMoveEvent(event);
}

//鼠标释放后，更新状态变量
void myTitlebar::mouseReleaseEvent(QMouseEvent *event)
{
   // m_isPressed = false;
   // return QWidget::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = false;
    }

    return QWidget::mouseReleaseEvent(event);
}

// 加载本地样式文件;
// 可以将样式直接写在文件中，程序运行时直接加载进来;
void myTitlebar::loadStyleSheet(const QString &sheetName)
{
    QFile file("/home/liang/code/ProcessManage/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {

        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
    else {
        qDebug() << "文件加载失败";
    }
}

// 以下为按钮操作响应的槽;
void myTitlebar::onButtonMinClicked()
{
    emit signalButtonMinClicked();
}

void myTitlebar::onButtonRestoreClicked()
{
    m_pButtonRestore->setVisible(false);
    m_pButtonMax->setVisible(true);
    emit signalButtonRestoreClicked();
}

void myTitlebar::onButtonMaxClicked()
{
    m_pButtonMax->setVisible(false);
    m_pButtonRestore->setVisible(true);
    emit signalButtonMaxClicked();
}

void myTitlebar::onButtonCloseClicked()
{
    emit signalButtonCloseClicked();
}

