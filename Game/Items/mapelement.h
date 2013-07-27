#ifndef GAMEMAPELEMENT_H
#define GAMEMAPELEMENT_H

#include <QtWidgets>
#include "backinfo.h"

class gameMapElement : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:
    gameMapElement(int, char, QPoint, QString);

    QVector<QPointF> getPolygonPointf(QPointF);
    QPolygonF polygonDeleteBound(double);

    QBrush getBrush() const { return brush; }
    QPoint getPoint() const { return point; }
    QString getElementName() const { return elementName; }
    bool isPointAvailable() const { return elementType != areaNouse; }
    bool isMoveAvailable() const { return moveAvailable; }

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    enum gameEnvironment_t
    {
        areaSpace,
        areaGrass   = '1',
        areaStone   = '2',
        areaShop    = '3',
        areaAlchemy = '4',
        areaSpring  = '5',
        areaCamp    = '6',
        areaSwamp   = '7',
        areaDesert  = '8',
        areaWater   = '9',


        areaFort    = 'J',
        areaRedHome = 'K',
        areaTree    = 'L',
        areaBlueHome= 'M',

        areaNouse = 'Z'
    };

private:
    void variableInitial();
    QString path;
    QPoint point;
    int lineLength;
    double halfSqrt3;

    bool moveAvailable;
    char elementType;
    QBrush brush;
    QString elementName;
    QPolygonF hexagon;

signals:
    void statusInfoChanged(QString);
    void elementClicked(QGraphicsSceneMouseEvent*);
    void elementHoverin(QGraphicsSceneHoverEvent*);
};


#endif // GAMEMAPELEMENT_H
