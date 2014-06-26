#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T20:55:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = vv
TEMPLATE = app


SOURCES  += \
    Game/gameprocess.cpp \
    Game/eventcenter.cpp \
    Game/skillcenter.cpp \
    Game/Back/menu.cpp \
    Game/Back/coordinate.cpp \
    Game/Back/backview.cpp \
    Game/Back/backscene.cpp \
    Game/Back/backinfo.cpp \
    Game/Back/layoutscene.cpp \
    Game/Back/herolabel.cpp \
    Game/Items/mapelement.cpp \
    Game/Items/camphealth.cpp \
    Game/Items/Hero/herowhole.cpp \
    Game/Items/Hero/heroitem.cpp \
    Game/Items/Hero/heroengine.cpp \
    Game/Items/Card/cardengine.cpp \
    Game/Items/Card/carditem.cpp \
    Game/Items/itemcollector.cpp \
    Widget/otherwidgets.cpp \
    Widget/gameWidget.cpp \
    Game/Items/mapmark.cpp \
    Package/normalpackage.cpp \
    Game/Items/equipment.cpp \
    Game/Items/Hero/attackability.cpp \
    Game/Items/Hero/moveability.cpp \
    Game/ai.cpp \
    forms/dialogskillchosen.cpp \
    main.cpp \
    forms/dialogherochosen.cpp

HEADERS  += \
    mainwindow.h \
    Game/gameprocess.h \
    Game/eventcenter.h \
    Game/skillcenter.h \
    Game/Back/menu.h \
    Game/Back/coordinate.h \
    Game/Back/backview.h \
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
    Game/Items/Card/cardengine.h \
    Game/Items/Card/carditem.h \
    Game/Items/itemcollector.h \
    Widget/gameWidget.h \
    Widget/otherwidgets.h \
    Game/enums.h \
    Game/Items/mapmark.h \
    Package/normalpackage.h \
    Game/Items/equipment.h \
    Game/Items/Hero/attackability.h \
    Game/Items/Hero/moveability.h \
    Game/ai.h \
    forms/dialogskillchosen.h \
    forms/dialogherochosen.h

INCLUDEPATH += include
INCLUDEPATH += .
INCLUDEPATH += Game
INCLUDEPATH += Game/Back
INCLUDEPATH += Game/Items
INCLUDEPATH += Game/Items/Hero
INCLUDEPATH += Game/Items/Card
INCLUDEPATH += Widget
INCLUDEPATH += Package

FORMS    += forms/modechoose.ui \
    forms/mainwindow.ui \
    forms/front.ui \
    forms/enviroSettings.ui \
    forms/chooseGame.ui \
    forms/dialogskillchosen.ui \
    forms/dialogherochosen.ui

TRANSLATIONS = lang__zhCN.ts

RESOURCES += \
    vv.qrc
