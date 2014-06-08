#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T17:51:09
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_vvtesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
CONFIG += c++11


SOURCES += tst_vvtesttest.cpp \
    Game/Back/backinfo.cpp \
    Game/Items/Hero/moveability.cpp \
    Game/Items/Hero/herowhole.cpp \
    Game/Items/Hero/heroitem.cpp \
    Game/Items/Hero/heroengine.cpp \
    Game/Items/Hero/attackability.cpp \
    Game/Back/menu.cpp \
    Game/Back/layoutscene.cpp \
    Game/Back/herolabel.cpp \
    Game/Back/coordinate.cpp \
    Game/Back/backview.cpp \
    Game/Back/backscene.cpp \
    Game/Items/mapmark.cpp \
    Game/Items/mapelement.cpp \
    Game/Items/itemcollector.cpp \
    Game/Items/equipment.cpp \
    Game/Items/camphealth.cpp \
    Game/Items/Card/carditem.cpp \
    Game/Items/Card/cardengine.cpp \
    Package/normalpackage.cpp \
    Widget/otherwidgets.cpp \
    Widget/gameWidget.cpp \
    Game/skillcenter.cpp \
    Game/gameprocess.cpp \
    Game/eventcenter.cpp \
    Game/ai.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    Game/Back/backinfo.h \
    Game/Items/Hero/moveability.h \
    Game/Items/Hero/herowhole.h \
    Game/Items/Hero/heroitem.h \
    Game/Items/Hero/heroengine.h \
    Game/Items/Hero/attackability.h \
    Game/Back/menu.h \
    Game/Back/layoutscene.h \
    Game/Back/herolabel.h \
    Game/Back/coordinate.h \
    Game/Back/backview.h \
    Game/Back/backscene.h \
    Game/Items/mapmark.h \
    Game/Items/mapelement.h \
    Game/Items/itemcollector.h \
    Game/Items/equipment.h \
    Game/Items/camphealth.h \
    Game/Items/Card/carditem.h \
    Game/Items/Card/cardengine.h \
    Package/normalpackage.h \
    Widget/otherwidgets.h \
    Widget/gameWidget.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_modechoose.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_mainwindow.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_gameSetting.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_front.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_equipmentshop.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_enviroSettings.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_chooseHero.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_chooseGame.h \
    ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug/ui_chooseBirth.h \
    Game/skillcenter.h \
    Game/gameprocess.h \
    Game/eventcenter.h \
    Game/enums.h \
    Game/ai.h

INCLUDEPATH += include
INCLUDEPATH += Game/
INCLUDEPATH += Game/Items/Hero
INCLUDEPATH += Game/Back/
INCLUDEPATH += Game/Items
INCLUDEPATH += Package
INCLUDEPATH += Widget
INCLUDEPATH += Game/Items/Card
INCLUDEPATH += ../build-vv-Desktop_Qt_5_1_1_MinGW_32bit-Debug
