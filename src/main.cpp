#include "basewindow.h"
#include "mytitlebar.h"
#include <QApplication>
#include <QtCore/QProcessEnvironment>
#include "imagebutton.h"


int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "xcb");

    QApplication a(argc, argv);
    BaseWindow w;
    w.show();

    return a.exec();
}
