#include "gamemapelement.h"

gameMapElement::gameMapElement(int lineLength, char elementType, QPoint point, QString path)
    :elementType(elementType)
{
    this->lineLength = lineLength;
    this->halfSqrt3 = 0.86;
    this->path = path;

    getPolygonPointf(QPointF(0, 0));

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setPolygon(hexagon);
    setZValue(0.6);

    this->point = point;
    this->moveAvailable = true;

    variableInitial();
}

void gameMapElement::variableInitial()
{
    QPixmap block;
    switch(elementType)
    {
    case areaGrass:
        block = QPixmap(path + "forest.png");
        elementName = QString(tr("grass"));
        break;
    case areaStone:
        block = QPixmap(path + "stone.png");
        elementName = QString(tr("stone"));
        moveAvailable = false;
        break;
    case areaShop:
        block = QPixmap(path + "shop.png");
        elementName = QString(tr("shop"));
        moveAvailable = false;
        break;
    case areaAlchemy:
        block = QPixmap(path + "alchemy.png");
        elementName = QString(tr("alchemy"));
        break;
    case areaSpring:
        block = QPixmap(path + "spring.png");
        elementName = QString(tr("spring"));
        moveAvailable = false;
        break;
    case areaCamp:
        block = QPixmap(path + "camp.png");
        elementName = QString(tr("camp"));
        break;
    case areaSwamp:
        block = QPixmap(path + "swamp.png");
        elementName = QString(tr("swamp"));
        break;
    case areaDesert:
        block = QPixmap(path + "desert.png");
        elementName = QString(tr("desert"));
        break;
    case areaWater:
        block = QPixmap(path + "water.png");
        elementName = QString(tr("water"));
        break;
    case areaFort:
        block = QPixmap(path + "fort.png");
        elementName = QString(tr("fort"));
        moveAvailable = false;
        break;
    case areaRedHome:
        block = QPixmap(path + "red.png");
        elementName = QString(tr("red camp"));
        break;
    case areaTree:
        block = QPixmap(path + "tree.png");
        elementName = QString(tr("tree"));;
        moveAvailable = false;
        break;
    case areaBlueHome:
        block = QPixmap(path + "blue.png");
        elementName = QString(tr("blue camp"));
        break;
    default:
        block = QPixmap(path + "desert.png");
        elementName = QString(tr("desert"));
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
        if(moveAvailable)
            painter->setPen(QPen(Qt::black, 5));
        else
            painter->setPen(QPen(Qt::white, 5));
    }
    else
    {
        if(moveAvailable)
            pen().setColor(Qt::white);
        painter->setPen(pen());
    }
    painter->setOpacity(0.8);
    painter->drawPolygon(hexagon);

//    QPolygonF p = polygonDeleteBound(double(painter->pen().width()));
//    painter->drawPolygon(p);
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
    setZValue(0.8);
    emit elementHoverin(event);
    emit statusInfoChanged(elementName + ";" + QString::number(point.x()) + ", " + QString::number(point.y()));

}

void gameMapElement::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //emit statusInfoChanged("");
    setZValue(0.6);
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
