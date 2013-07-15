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
    Widget/backview.cpp \
    Game/gamemapelement.cpp \
    Game/heroitem.cpp \
    Game/gamemenu.cpp \
    Game/gamebackinfo.cpp \
    Game/gamecoordinate.cpp \
    Widget/backscene.cpp \
    Game/carditem.cpp

HEADERS  += mainwindow.h \
    Widget/mainwindow.h \
    Widget/backview.h \
    Game/gamemapelement.h \
    Game/heroitem.h \
    Game/gamemenu.h \
    Game/gamebackinfo.h \
    Game/gamecoordinate.h \
    Widget/backscene.h \
    Game/carditem.h

FORMS    += mainwindow.ui

TRANSLATIONS = lang__zhCN.ts

RESOURCES += \
    vv.qrc
