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
    Widget/mainwindow.cpp \
    Widget/widgetmaintest.cpp \
    Game/gamemapelement.cpp \
    Game/abstracthero.cpp \
    Game/heroitem.cpp \
    Widget/testview2.cpp \
    Game/gamemenu.cpp

HEADERS  += mainwindow.h \
    Game/gamebackpic.h \
    Widget/widgetmain.h \
    Widget/mainwindow.h \
    Widget/widgetmaintest.h \
    Game/gamemapelement.h \
    Game/abstracthero.h \
    Game/heroitem.h \
    Widget/testview2.h \
    Game/gamemenu.h

FORMS    += mainwindow.ui

RESOURCES += \
    vv.qrc
