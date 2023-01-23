QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    currentploter.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    voltageploter.cpp

HEADERS += \
    command.h \
    currentploter.h \
    mainwindow.h \
    qcustomplot.h \
    voltageploter.h

FORMS += \
    currentploter.ui \
    mainwindow.ui \
    voltageploter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
