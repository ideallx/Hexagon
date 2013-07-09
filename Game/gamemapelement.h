#ifndef GAMEMAPELEMENT_H
#define GAMEMAPELEMENT_H

#include <QtWidgets>

class gameMapElement : public QGraphicsPolygonItem, public QObject
{
public:
    gameMapElement(char, QPoint);

    QVector<QPointF> getPolygonPointf(QPointF);
    QBrush getBrush() { return brush; }
    QString getElementName() { return elementName; }
    bool isPointAvailable() { return elementType != areaNouse; }
    bool isMoveAvailable() { return moveAvailable; }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

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

    QPoint coo;
    bool moveAvailable;
    char elementType;
    QBrush brush;
    QString elementName;
};

#endif // GAMEMAPELEMENT_H
