#include "imagebutton.h"

ImageButton::ImageButton(const QString& imagePath, const QSize& buttonSize, QWidget* parent)
    :  QPushButton(parent), m_pixmap(imagePath), buttonSize(buttonSize)
{
    // 设置按钮的大小
    setFixedSize(buttonSize);
    // 调整图片大小以适应按钮大小
    m_pixmap = m_pixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 创建遮罩
    //QBitmap mask = m_pixmap.createMaskFromColor(Qt::transparent);

    // 创建区域并调整大小
    //QRegion region(mask);
    //region = region.intersected(QRegion(0, 0, buttonSize.width(), buttonSize.height()));

    // 设置遮罩
    //setMask(region);
    //qDebug() << "Button mask region:" << region;

}

void ImageButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // 绘制按钮图片
    painter.drawPixmap(0, 0, m_pixmap);

    // 如果按钮被按下或有焦点，绘制按下或有焦点的样式
    /*if (isDown() || hasFocus()) {
        QStyleOptionButton option;
        option.initFrom(this);
        style()->drawPrimitive(QStyle::PE_PanelButtonBevel, &option, &painter, this);
    }*/
}

void ImageButton::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse pressed on button";
    QPushButton::mousePressEvent(event);
}

