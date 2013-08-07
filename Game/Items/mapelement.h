#ifndef GAMEMAPELEMENT_H
#define GAMEMAPELEMENT_H

#include <QGraphicsItem>
#include <QVector>
#include <QPoint>
#include <QString>
#include <QPen>
#include <QPainter>

class gameBackInfo;

class gameMapElement : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:
    gameMapElement(int, char, QPoint, QString);

    QVector<QPointF> getPolygonPointf(QPointF);
    QPolygonF polygonDeleteBound(double);

    QPoint getPoint() const { return point; }
    QString getElementName() const { return elementName; }
    bool isPointAvailable() const { return elementType != areaNouse; }
    bool isMoveAvailable() const { return moveAvailable; }

    void setDefaultZValue();
    void setDefaultPen();
    QPen getDefaultPen() { if(moveAvailable) return QPen(Qt::black); else return QPen(Qt::white); }

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    void setPen(const QPen &pen);
    QPen getOldPen() const { return oldPen; }
    void restorePen() { QGraphicsPolygonItem::setPen(oldPen); }

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

    QPen oldPen;
    QString path;
    QPoint point;
    int lineLength;
    double halfSqrt3;

    bool moveAvailable;
    char elementType;
    QString elementName;
    QPolygonF hexagon;
};


#endif // GAMEMAPELEMENT_H
