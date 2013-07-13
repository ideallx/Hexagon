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
    Widget/mainwindow.cpp \
    Widget/widgetmaintest.cpp \
    Widget/backview.cpp \
    Game/gamemapelement.cpp \
    Game/heroitem.cpp \
    Game/gamemenu.cpp \
    Game/gamebackinfo.cpp \
    Game/gamecoordinate.cpp

HEADERS  += mainwindow.h \
    Widget/mainwindow.h \
    Widget/widgetmaintest.h \
    Widget/backview.h \
    Game/gamemapelement.h \
    Game/heroitem.h \
    Game/gamemenu.h \
    Game/gamebackinfo.h \
    Game/gamecoordinate.h

FORMS    += mainwindow.ui

RESOURCES +=
