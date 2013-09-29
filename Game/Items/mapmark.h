#ifndef GAME_ITEMS_MAPMARK_H_
#define GAME_ITEMS_MAPMARK_H_

#include <QGraphicsEllipseItem>
#include <QPoint>

class MapMark : public QObject, public QGraphicsEllipseItem {
 public:
    MapMark(QString path, int width);

    QPoint point() { return thePoint; }
    void setPoint(QPoint in) { thePoint = in;}
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
 private:
    QPoint thePoint;
};

#endif  // GAME_ITEMS_MAPMARK_H_
