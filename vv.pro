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
    Game/Items/camphealth.cpp \
    Game/Items/Hero/herowhole.cpp \
    Game/Items/Hero/heroitem.cpp \
    Game/Items/Hero/heroengine.cpp \
    Game/Items/Card/cardBack.cpp \
    Game/Items/Card/cardengine.cpp \
    Widget/gameWidget.cpp \
    Game/Items/Card/carditem.cpp \
    Game/Items/itemcollector.cpp \
    Game/eventcenter.cpp \
    Game/animationcenter.cpp \
    Game/Back/layoutscene.cpp \
    Widget/otherwidgets.cpp \
    Game/skillcenter.cpp

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
    Game/Items/Hero/heroitem.h \
    Game/Items/Hero/heroengine.h \
    Game/Items/Card/cardback.h \
    Game/Items/Card/cardengine.h \
    Widget/gameWidget.h \
    Game/Items/Card/carditem.h \
    Game/Items/itemcollector.h \
    Game/eventcenter.h \
    Game/animationcenter.h \
    Game/Back/layoutscene.h \
    Widget/otherwidgets.h \
    Game/skillcenter.h

INCLUDEPATH += include
INCLUDEPATH += Game
INCLUDEPATH += Game/Back
INCLUDEPATH += Game/Items
INCLUDEPATH += Game/Items/Hero
INCLUDEPATH += Game/Items/Card
INCLUDEPATH += Widget

FORMS    += mainwindow.ui \
    front.ui \
    modechoose.ui \
    gameSetting.ui \
    enviroSettings.ui \
    chooseHero.ui

TRANSLATIONS = lang__zhCN.ts

RESOURCES += \
    vv.qrc
