#include "gamemapelement.h"

gameMapElement::gameMapElement(char elementType)
    :elementType(elementType)
{
    variableInitial();
}

void gameMapElement::variableInitial()
{
    moveAvailable = true;
    switch(elementType)
    {
    case areaGrass:
        brush = QBrush(Qt::green);
        elementName = QString("草地");
        break;
    case areaStone:
        brush = QBrush(Qt::darkGray);
        elementName = QString("石头");
        moveAvailable = false;
        break;
    case areaShop:
        brush = QBrush(Qt::gray);
        elementName = QString("商店");
        moveAvailable = false;
        break;
    case areaAlchemy:
        brush = QBrush(Qt::lightGray);
        elementName = QString("炼金之阵");
        break;
    case areaSpring:
        brush = QBrush(Qt::cyan);
        elementName = QString("泉水");
        break;
    case areaCamp:
        //brush = QBrush(QPixmap(":/Resource/SkinDefault/test.jpg"));
        brush = QBrush(Qt::yellow);
        elementName = QString("营地");
        break;
    case areaSwamp:
        brush = QBrush(Qt::darkRed);
        elementName = QString("沼泽");
        break;
    case areaDesert:
        brush = QBrush(Qt::darkYellow);
        elementName = QString("沙漠");
        break;
    case areaWater:
        brush = QBrush(Qt::blue);
        elementName = QString("深水");
        break;
    case areaFort:
        //brush = QBrush(QPixmap(":/Resource/SkinDefault/areaFort.jpg"));
        brush = QBrush(Qt::red);
        elementName = QString("堡垒");
        moveAvailable = false;
        break;
    case areaRedHome:
        brush = QBrush(Qt::magenta);
        elementName = QString("红色基地");
        break;
    case areaTree:
        brush = QBrush(Qt::darkGreen);
        elementName = QString("世界之树");
        moveAvailable = false;
        break;
    case areaBlueHome:
        brush = QBrush(Qt::black);
        elementName = QString("蓝色基地");
        break;
    default:
        brush = QBrush(Qt::white);
        elementName = QString("空地");
    }
}
