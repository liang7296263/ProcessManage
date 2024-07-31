#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QStyleOptionButton>

class ImageButton : public QPushButton
{
    Q_OBJECT
public:
    ImageButton(const QString& imagePath, const QSize& buttonSize, QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QPixmap m_pixmap;
    QSize buttonSize;
};
#endif // IMAGEBUTTON_H
