#include "gamemapelement.h"
#include "../commonvariable.h"

gameMapElement::gameMapElement(char elementType)
    :elementType(elementType)
{
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);

    lineLength = globol::gbi->getLineLength();
    halfSqrt3 = 0.86;

    getPolygonPointf(QPointF(0, 0));
    setPolygon(hexagon);
    moveAvailable = true;
    setZValue(0);

    variableInitial();
}

void gameMapElement::variableInitial()
{

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
        elementName = QString("要塞");
        moveAvailable = false;
        break;
    case areaRedHome:
        brush = QBrush(Qt::magenta);
        elementName = QString("红方基地");
        break;
    case areaTree:
        brush = QBrush(Qt::darkGreen);
        elementName = QString("世界之树");
        moveAvailable = false;
        break;
    case areaBlueHome:
        brush = QBrush(Qt::black);
        elementName = QString("蓝方基地");
        break;
    default:
        brush = QBrush(Qt::white);
        elementName = QString("空白");
    }
}

QRectF gameMapElement::boundingRect() const
{
    return QRectF(0, 0, 2*lineLength, 1.73*lineLength);
}
void gameMapElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    if(item->state & QStyle::State_MouseOver)
    {
        painter->setPen(QPen(Qt::black, 5));
    }
    else
    {
        painter->setPen(Qt::black);
    }

    painter->setBrush(brush);
    painter->setOpacity(0.4);
    painter->drawPolygon(hexagon);
}

QVector<QPointF> gameMapElement::getPolygonPointf(QPointF begin)
{
    QVector<QPointF> result;
    QPointF p = QPointF(begin.x(),begin.y() + halfSqrt3*lineLength);
    result.append(p);
    hexagon.append(p);
    p = QPointF(begin.x()+0.5*lineLength, begin.y());
    result.append(p);
    hexagon.append(p);
    p = QPointF(begin.x()+1.5*lineLength, begin.y());
    result.append(p);
    hexagon.append(p);
    p = QPointF(begin.x()+2.0*lineLength, begin.y() + halfSqrt3*lineLength);
    result.append(p);
    hexagon.append(p);
    p = QPointF(begin.x()+1.5*lineLength, begin.y() + 2*halfSqrt3*lineLength);
    result.append(p);
    hexagon.append(p);
    p = QPointF(begin.x()+0.5*lineLength, begin.y() + 2*halfSqrt3*lineLength);
    result.append(p);
    hexagon.append(p);
    return result;
}

void gameMapElement::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mouseMoveEvent(e);
    globol::statusLabel->setText(elementName);
    update();
}

void gameMapElement::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mousePressEvent(e);
    update();
}

void gameMapElement::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    globol::statusLabel->setText(elementName);
    QGraphicsItem::hoverEnterEvent(event);
}

void gameMapElement::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    globol::statusLabel->clear();
    QGraphicsItem::hoverLeaveEvent(event);
}

QPainterPath gameMapElement::shape() const
{
    QPainterPath path;
    path.addPolygon(hexagon);
    return path;
}
