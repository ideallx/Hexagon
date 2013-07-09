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
    Widget/widgetmain.cpp \
    Widget/mainwindow.cpp \
    Widget/widgetmaintest.cpp \
    Game/gamemapelement.cpp \
    Game/abstracthero.cpp \
    Game/heroitem.cpp \
    Game/gamemenu.cpp \
    commonvariable.cpp \
    Game/gamebackinfo.cpp \
    Widget/backview.cpp

HEADERS  += mainwindow.h \
    Widget/widgetmain.h \
    Widget/mainwindow.h \
    Widget/widgetmaintest.h \
    Game/gamemapelement.h \
    Game/abstracthero.h \
    Game/heroitem.h \
    Game/gamemenu.h \
    commonvariable.h \
    Game/gamebackinfo.h \
    Widget/backview.h

FORMS    += mainwindow.ui

RESOURCES += \
    vv.qrc
