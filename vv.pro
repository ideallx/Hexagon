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
    Game/gameprocess.cpp \
    Game/Back/menu.cpp \
    Game/Back/coordinate.cpp \
    Game/Back/backview.cpp \
    Game/Back/backscene.cpp \
    Game/Back/backinfo.cpp \
    Game/Items/mapelement.cpp \
    Game/Items/carditem.cpp \
    Game/Items/camphealth.cpp \
    Game/Items/Hero/herowhole.cpp \
    Game/Items/Hero/heronormalpackage.cpp \
    Game/Items/Hero/heroitem.cpp \
    Game/Items/Hero/heroengine.cpp \
    Widget/gameWidget.cpp

HEADERS  += mainwindow.h \
    Game/gameprocess.h \
    Game/Back/menu.h \
    Game/Back/coordinate.h \
    Game/Back/backview.h \
    Game/Back/backscene.h \
    Game/Back/backinfo.h \
    Game/Items/mapelement.h \
    Game/Items/carditem.h \
    Game/Items/camphealth.h \
    Game/Items/Hero/herowhole.h \
    Game/Items/Hero/heronormalpackage.h \
    Game/Items/Hero/heroitem.h \
    Game/Items/Hero/heroengine.h \
    Widget/gameWidget.h

INCLUDEPATH += include
INCLUDEPATH += Game
INCLUDEPATH += Game/Back
INCLUDEPATH += Game/Items
INCLUDEPATH += Game/Items/Hero
INCLUDEPATH += Widget

FORMS    += mainwindow.ui

TRANSLATIONS = lang__zhCN.ts

RESOURCES += \
    vv.qrc
