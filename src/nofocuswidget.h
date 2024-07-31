#ifndef NOFOCUSWIDGET_H
#define NOFOCUSWIDGET_H

#include <QWidget>
#include "basewindow.h"

class NoFocuswidget : public BaseWindow
{
    Q_OBJECT
public:
    explicit NoFocuswidget(QWidget *parent = nullptr);
    ~NoFocuswidget();

signals:
};

#endif // NOFOCUSWIDGET_H
