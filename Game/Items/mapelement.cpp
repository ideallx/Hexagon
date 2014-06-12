#include <QDebug>
#include "mapelement.h"
#include "backinfo.h"

MapEngine::MapEngine(GameBackInfo* gbi)
    : gbi(gbi) {
}

// wid and hei is total width and total height
QList<GameMapElement*> MapEngine::generateMapElements() {
    QList<GameMapElement*> elements;
    QVector<char> map = gbi->getMapElement();
    int hei = gbi->getHeightCount();
    int wid = gbi->getWidthCount();
    for (int j = 0; j < hei; j++) {
        for (int i = 0; i < wid; i++) {
            GameMapElement *mapItem = new GameMapElement(
                        gbi->getLineLength(),
                        static_cast<AreaHexagon>(map[i+j*wid]),
                        QPoint(i, j),
                        gbi->getConfigDir()+"elements/");
            elements.append(mapItem);
            if (!mapItem->isPointAvailable()) {
                mapItem->hide();
            }
        }
    }
    return elements;
}

GameMapElement::GameMapElement(int lineLength,
                               AreaHexagon elementType,
                               QPoint point,
                               QString path)
    : elementType(elementType),
      halfSqrt3(sqrt(3) / 2),
      lineLength(lineLength),
      path(path),
      thePoint(point),
      moveAvailable(true) {

    getPolygonPointf(QPointF(0, 0));

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setPolygon(hexagon);

    variableInitial();
    setDefaultPen();
    setDefaultZValue();
}

void GameMapElement::setDefaultZValue() {
    if (moveAvailable)
        setZValue(0.6);
    else
        setZValue(0.8);
}

QRectF GameMapElement::boundingRect() const {
    return QRectF(0, 0, 2*lineLength, 1.73*lineLength);
}

void GameMapElement::setDefaultPen() {
    if (moveAvailable)
        setPen(QPen(Qt::gray, 2));
    else
        setPen(QPen(Qt::white, 5));
}

void GameMapElement::variableInitial() {
    QPixmap block;
    switch (elementType) {
    case AreaHexagon::AreaGrass:
        block = QPixmap(path + "forest.png");
        elementName = QString(tr("grass"));
        break;
    case AreaHexagon::AreaStone:
        block = QPixmap(path + "stone.png");
        elementName = QString(tr("stone"));
        moveAvailable = false;
        break;
    case AreaHexagon::AreaShop:
        block = QPixmap(path + "shop.png");
        elementName = QString(tr("shop"));
        moveAvailable = false;
        break;
    case AreaHexagon::AreaAlchemy:
        block = QPixmap(path + "alchemy.png");
        elementName = QString(tr("alchemy"));
        break;
    case AreaHexagon::AreaSpring:
        block = QPixmap(path + "spring.png");
        elementName = QString(tr("spring"));
        moveAvailable = false;
        break;
    case AreaHexagon::AreaCamp:
        block = QPixmap(path + "camp.png");
        elementName = QString(tr("camp"));
        break;
    case AreaHexagon::AreaSwamp:
        block = QPixmap(path + "swamp.png");
        elementName = QString(tr("swamp"));
        break;
    case AreaHexagon::AreaDesert:
        block = QPixmap(path + "desert.png");
        elementName = QString(tr("desert"));
        break;
    case AreaHexagon::AreaWater:
        block = QPixmap(path + "water.png");
        elementName = QString(tr("water"));
        break;
    case AreaHexagon::AreaFort:
        block = QPixmap(path + "fort.png");
        elementName = QString(tr("fort"));
        moveAvailable = false;
        break;
    case AreaHexagon::AreaRedHome:
        block = QPixmap(path + "red.png");
        elementName = QString(tr("red camp"));
        break;
    case AreaHexagon::AreaTree:
        block = QPixmap(path + "tree.png");
        elementName = QString(tr("tree"));;
        moveAvailable = false;
        break;
    case AreaHexagon::AreaBlueHome:
        block = QPixmap(path + "blue.png");
        elementName = QString(tr("blue camp"));
        break;
    default:
        block = QPixmap(path + "desert.png");
        elementName = QString(tr("desert"));
    }
    setBrush(QBrush(block.scaledToWidth(2*lineLength,
                                        Qt::SmoothTransformation)));
}

void GameMapElement::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *item,
                           QWidget *widget) {
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setBrush(brush());
    painter->setPen(pen());
    painter->setOpacity(0.8);
    painter->drawPolygon(hexagon);
}

QVector<QPointF> GameMapElement::getPolygonPointf(QPointF begin) {
    QPointF p = QPointF(begin.x(), begin.y() + halfSqrt3*lineLength);
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

QPainterPath GameMapElement::shape() const {
    QPainterPath path;
    path.addPolygon(hexagon);
    return path;
}

//     2  3
//   1      4
//     6  5
QPolygonF GameMapElement::polygonDeleteBound(double width) {
    QVector<QPointF> result;
    result.append(hexagon.at(0)+QPointF(width/2, 0));
    result.append(hexagon.at(1)+QPointF(0, width/2));
    result.append(hexagon.at(2)+QPointF(0, width/2));
    result.append(hexagon.at(3)+QPointF(-width/2, 0));
    result.append(hexagon.at(4)+QPointF(0, -width/2));
    result.append(hexagon.at(5)+QPointF(0, -width/2));
    return result;
}

void GameMapElement::setPen(const QPen &pen) {
    oldPen = this->pen();
    QGraphicsPolygonItem::setPen(pen);
}
