#-------------------------------------------------
#
# Project created by QtCreator 2021-10-31T11:59:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HMI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        Source/mainwindow.cpp \
        ExternalLibs/snap7.cpp \
        Source/plcS7.cpp \
        Source/worker.cpp \
        Source/inputwindow.cpp \
        Source/outputwindow.cpp \
        Source/hmi_tag.cpp \
    statisticwindow.cpp \
    setpointwindow.cpp

HEADERS += \
        Include/mainwindow.h \
        Include/plcS7.h \
        ExternalLibs/snap7.h \
        Include/worker.h \
        Include/inputwindow.h \
        Include/outputwindow.h \
        Include/configPLC.h \
        Include/hmi_tag.h \
    statisticwindow.h \
    setpointwindow.h

INCLUDEPATH += \
        Include \
        Source \
        Forms \
        ExternalLibs \

FORMS += \
        Forms/mainwindow.ui \
        Forms/inputwindow.ui \
        Forms/outputwindow.ui \
    statisticwindow.ui \
    setpointwindow.ui

LIBS += -lsnap7

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
