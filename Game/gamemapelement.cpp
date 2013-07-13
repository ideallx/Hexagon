#include "gamemapelement.h"

gameMapElement::gameMapElement(char elementType, QPoint pos)
    :elementType(elementType)
{
    this->lineLength = 50; //nnn
    this->halfSqrt3 = 0.86;

    getPolygonPointf(QPointF(0, 0));

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setPolygon(hexagon);
    setZValue(0);

    this->pos = pos;
    this->moveAvailable = true;

    variableInitial();
}

void gameMapElement::variableInitial()
{
    QPixmap block;
    QString path = QString("F:/KuGou/vv/Resource/SkinDefault/");
    switch(elementType)
    {
    case areaGrass:
        block = QPixmap(path + "forest.png");
        elementName = QString("草地");
        break;
    case areaStone:
        block = QPixmap(path + "stone.png");
        elementName = QString("石头");
        moveAvailable = false;
        break;
    case areaShop:
        block = QPixmap(path + "shop.png");
        elementName = QString("商店");
        moveAvailable = false;
        break;
    case areaAlchemy:
        block = QPixmap(path + "alchemy.png");
        elementName = QString("炼金之阵");
        break;
    case areaSpring:
        block = QPixmap(path + "spring.png");
        elementName = QString("泉水");
        break;
    case areaCamp:
        block = QPixmap(path + "camp.png");
        elementName = QString("营地");
        break;
    case areaSwamp:
        block = QPixmap(path + "swamp.png");
        elementName = QString("沼泽");
        break;
    case areaDesert:
        block = QPixmap(path + "desert.png");
        elementName = QString("沙漠");
        break;
    case areaWater:
        block = QPixmap(path + "water.png");
        elementName = QString("深水");
        break;
    case areaFort:
        block = QPixmap(path + "fort.png");
        elementName = QString("要塞");
        moveAvailable = false;
        break;
    case areaRedHome:
        block = QPixmap(path + "red.png");
        elementName = QString("红方基地");
        break;
    case areaTree:
        block = QPixmap(path + "tree.png");
        elementName = QString("世界之树");
        moveAvailable = false;
        break;
    case areaBlueHome:
        block = QPixmap(path + "blue.png");
        elementName = QString("蓝方基地");
        break;
    default:
        block = QPixmap(path + "desert.png");
        elementName = QString("空白");
    }
    brush = QBrush(block.scaledToWidth(2*lineLength));
}

QRectF gameMapElement::boundingRect() const
{
    return QRectF(0, 0, 2*lineLength, 1.73*lineLength);
}

void gameMapElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setBrush(brush);
    if(item->state & QStyle::State_MouseOver)
    {
        painter->setPen(QPen(Qt::black, 5));
    }
    else
    {
        painter->setPen(pen());
    }
    painter->setOpacity(0.6);
    //painter->drawPolygon(hexagon);

    QPolygonF p = polygonDeleteBound(double(painter->pen().width()));
    painter->drawPolygon(p);
}

//     2  3
//   1      4
//     6  5
QVector<QPointF> gameMapElement::getPolygonPointf(QPointF begin)
{
    QPointF p = QPointF(begin.x(),begin.y() + halfSqrt3*lineLength);
    hexagon.append(p);
    p = QPointF(begin.x()+0.5*lineLength, begin.y());
    hexagon.append(p);
    p = QPointF(begin.x()+1.5*lineLength, begin.y());
    hexagon.append(p);
    p = QPointF(begin.x()+2.0*lineLength, begin.y() + halfSqrt3*lineLength);
    hexagon.append(p);
    p = QPointF(begin.x()+1.5*lineLength, begin.y() + 2*halfSqrt3*lineLength);
    hexagon.append(p);
    p = QPointF(begin.x()+0.5*lineLength, begin.y() + 2*halfSqrt3*lineLength);
    hexagon.append(p);
    return hexagon;
}

void gameMapElement::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mousePressEvent(e);
    emit elementClicked(e);
}

void gameMapElement::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    emit elementHoverin(event);
    emit statusInfoChanged(QString("坐标:(") + QString::number(pos.x()) + ", " + QString::number(pos.y()) + ") " + elementName);

}

void gameMapElement::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit statusInfoChanged("");
    QGraphicsItem::hoverLeaveEvent(event);
}

QPainterPath gameMapElement::shape() const
{
    QPainterPath path;
    path.addPolygon(hexagon);
    return path;
}

//     2  3
//   1      4
//     6  5
QPolygonF gameMapElement::polygonDeleteBound(double width)
{
    QVector<QPointF> result;
    result.append(hexagon.at(0)+QPointF(width/2, 0));
    result.append(hexagon.at(1)+QPointF(0, width/2));
    result.append(hexagon.at(2)+QPointF(0, width/2));
    result.append(hexagon.at(3)+QPointF(-width/2, 0));
    result.append(hexagon.at(4)+QPointF(0, -width/2));
    result.append(hexagon.at(5)+QPointF(0, -width/2));
    return result;
}
