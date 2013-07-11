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
    commonvariable.cpp \
    Widget/widgetmain.cpp \
    Widget/mainwindow.cpp \
    Widget/widgetmaintest.cpp \
    Widget/backview.cpp \
    Game/gamemapelement.cpp \
    Game/abstracthero.cpp \
    Game/heroitem.cpp \
    Game/gamemenu.cpp \
    Game/gamebackinfo.cpp

HEADERS  += mainwindow.h \
    commonvariable.h \
    Widget/widgetmain.h \
    Widget/mainwindow.h \
    Widget/widgetmaintest.h \
    Widget/backview.h \
    Game/gamemapelement.h \
    Game/abstracthero.h \
    Game/heroitem.h \
    Game/gamemenu.h \
    Game/gamebackinfo.h

FORMS    += mainwindow.ui

RESOURCES += \
    vv.qrc
