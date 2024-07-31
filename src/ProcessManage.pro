QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basewindow.cpp \
    imagebutton.cpp \
    information.cpp \
    main.cpp \
    mychart.cpp \
    mystatusbar.cpp \
    mytitlebar.cpp \
    performance.cpp \
    processinformation.cpp \
    settingspage.cpp \
    systeminformation.cpp

HEADERS += \
    basewindow.h \
    imagebutton.h \
    information.h \
    mychart.h \
    mystatusbar.h \
    mytitlebar.h \
    performance.h \
    processinformation.h \
    settingspage.h \
    systeminformation.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
