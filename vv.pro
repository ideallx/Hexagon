#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T20:55:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vv
TEMPLATE = app


SOURCES  += main.cpp \
    Game/gamebackpic.cpp \
    Widget/widgetmain.cpp \
    Widget/mainwindow.cpp

HEADERS  += mainwindow.h \
    Game/gamebackpic.h \
    Widget/widgetmain.h \
    Widget/mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    vv.qrc
