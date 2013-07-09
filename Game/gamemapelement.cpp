#include "gamemapelement.h"

gameMapElement::gameMapElement(char elementType, QPoint coo)
    :elementType(elementType)
{
    this->coo = coo;
    variableInitial();
}

void gameMapElement::variableInitial()
{
    moveAvailable = true;
    //QPointF p0pointf = globol::gbi->getBeginPosWithCoo(coo);


    switch(elementType)
    {
    case areaGrass:
        brush = QBrush(Qt::green);
        elementName = QString("");
        break;
    case areaStone:
        brush = QBrush(Qt::darkGray);
        elementName = QString("");
        moveAvailable = false;
        break;
    case areaShop:
        brush = QBrush(Qt::gray);
        elementName = QString("");
        moveAvailable = false;
        break;
    case areaAlchemy:
        brush = QBrush(Qt::lightGray);
        elementName = QString("");
        break;
    case areaSpring:
        brush = QBrush(Qt::cyan);
        elementName = QString("");
        break;
    case areaCamp:
        //brush = QBrush(QPixmap(":/Resource/SkinDefault/test.jpg"));
        brush = QBrush(Qt::yellow);
        elementName = QString("");
        break;
    case areaSwamp:
        brush = QBrush(Qt::darkRed);
        elementName = QString("");
        break;
    case areaDesert:
        brush = QBrush(Qt::darkYellow);
        elementName = QString("");
        break;
    case areaWater:
        brush = QBrush(Qt::blue);
        elementName = QString("");
        break;
    case areaFort:
        //brush = QBrush(QPixmap(":/Resource/SkinDefault/areaFort.jpg"));
        brush = QBrush(Qt::red);
        elementName = QString("");
        moveAvailable = false;
        break;
    case areaRedHome:
        brush = QBrush(Qt::magenta);
        elementName = QString("");
        break;
    case areaTree:
        brush = QBrush(Qt::darkGreen);
        elementName = QString("");
        moveAvailable = false;
        break;
    case areaBlueHome:
        brush = QBrush(Qt::black);
        elementName = QString("");
        break;
    default:
        brush = QBrush(Qt::white);
        elementName = QString("");
    }
}

QRectF gameMapElement::boundingRect() const
{

    return QRectF();
}
void gameMapElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{

}

QVector<QPointF> gameMapElement::getPolygonPointf(QPointF begin)
{
    int lineLength = 50;
    double halfSqrt3 = 50*0.86;
    QVector<QPointF> result;
    QPointF p = QPointF(begin.x(),begin.y() + halfSqrt3*lineLength);
    result.append(p);
    p = QPointF(begin.x()+0.5*lineLength, begin.y());
    result.append(p);
    p = QPointF(begin.x()+1.5*lineLength, begin.y());
    result.append(p);
    p = QPointF(begin.x()+2.0*lineLength, begin.y() + halfSqrt3*lineLength);
    result.append(p);
    p = QPointF(begin.x()+1.5*lineLength, begin.y() + 2*halfSqrt3*lineLength);
    result.append(p);
    p = QPointF(begin.x()+0.5*lineLength, begin.y() + 2*halfSqrt3*lineLength);
    result.append(p);
    return result;
}
