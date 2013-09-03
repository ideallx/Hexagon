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
    Game/eventcenter.cpp \
    Game/skillcenter.cpp \
    Game/Back/menu.cpp \
    Game/Back/coordinate.cpp \
    Game/Back/BackView.cpp \
    Game/Back/backscene.cpp \
    Game/Back/backinfo.cpp \
    Game/Back/layoutscene.cpp \
    Game/Back/herolabel.cpp \
    Game/Items/mapelement.cpp \
    Game/Items/camphealth.cpp \
    Game/Items/Hero/herowhole.cpp \
    Game/Items/Hero/heroitem.cpp \
    Game/Items/Hero/heroengine.cpp \
    Game/Items/Card/CardBack.cpp \
    Game/Items/Card/cardengine.cpp \
    Game/Items/Card/carditem.cpp \
    Game/Items/itemcollector.cpp \
    Widget/otherwidgets.cpp \
    Widget/gameWidget.cpp

HEADERS  += enums.h \
    mainwindow.h \
    Game/gameprocess.h \
    Game/eventcenter.h \
    Game/skillcenter.h \
    Game/Back/menu.h \
    Game/Back/coordinate.h \
    Game/Back/BackView.h \
    Game/Back/backscene.h \
    Game/Back/backinfo.h \
    Game/Back/herolabel.h \
    Game/Back/layoutscene.h \
    Game/Items/mapelement.h \
    Game/Items/carditem.h \
    Game/Items/camphealth.h \
    Game/Items/Hero/herowhole.h \
    Game/Items/Hero/heroitem.h \
    Game/Items/Hero/heroengine.h \
    Game/Items/Card/cardback.h \
    Game/Items/Card/cardengine.h \
    Game/Items/Card/carditem.h \
    Game/Items/itemcollector.h \
    Widget/gameWidget.h \
    Widget/otherwidgets.h \
    Game/enums.h

INCLUDEPATH += include
INCLUDEPATH += .
INCLUDEPATH += Game
INCLUDEPATH += Game/Back
INCLUDEPATH += Game/Items
INCLUDEPATH += Game/Items/Hero
INCLUDEPATH += Game/Items/Card
INCLUDEPATH += Widget

FORMS    += mainwindow.ui \
    front.ui \
    gameSetting.ui \
    enviroSettings.ui \
    chooseHero.ui \
    modechoose.ui \
    chooseGame.ui \
    chooseBirth.ui

TRANSLATIONS = lang__zhCN.ts

RESOURCES += \
    vv.qrc
