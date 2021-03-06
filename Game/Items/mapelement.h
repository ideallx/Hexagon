#ifndef GAME_ITEMS_MAPELEMENT_H_
#define GAME_ITEMS_MAPELEMENT_H_

#include <QGraphicsItem>
#include <QVector>
#include <QPoint>
#include <QString>
#include <QPen>
#include <QPainter>
#include "enums.h"

class GameBackInfo;

class GameMapElement : public QObject, public QGraphicsPolygonItem {
    Q_OBJECT

 public:
    GameMapElement(int, AreaHexagon, QPoint, QString);

    QVector<QPointF> getPolygonPointf(QPointF);
    QPolygonF polygonDeleteBound(double width);

    inline QPoint point() const { return thePoint; }
    inline QString getElementName() const { return elementName; }
    inline bool isPointAvailable() const {
        return elementType != AreaHexagon::AreaNouse;
    }
    inline bool isMoveAvailable() const { return moveAvailable; }
    inline AreaHexagon getType() const { return elementType; }

    void setDefaultZValue();
    void setDefaultPen();
    QPen getDefaultPen() {
        if (moveAvailable)
            return QPen(Qt::black);
        else
            return QPen(Qt::white);
    }

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *item,
               QWidget *widget);

    void setPen(const QPen &pen);
    inline QPen getOldPen() const { return oldPen; }
    void restorePen() { QGraphicsPolygonItem::setPen(oldPen); }

 private:
    void variableInitial();

    QPen oldPen;

    AreaHexagon elementType;
    double halfSqrt3;
    int lineLength;
    QString path;
    QPoint thePoint;
    bool moveAvailable;

    QString elementName;
    QPolygonF hexagon;

    friend class VvTestTest;
};


class MapEngine {
 public:
    explicit MapEngine(GameBackInfo* gbi);
    QList<GameMapElement*> generateMapElements();

 private:
    GameBackInfo* gbi;
};

#endif  // GAME_ITEMS_MAPELEMENT_H_
