#ifndef GAME_ITEMS_MAPMARK_H_
#define GAME_ITEMS_MAPMARK_H_

#include <QGraphicsEllipseItem>
#include <QPoint>

class MapMark : public QObject, public QGraphicsEllipseItem {
 public:
    MapMark(QString path, int width);

    inline QPoint point() { return thePoint; }
    inline void setPoint(QPoint in) { thePoint = in;}
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
 private:
    QPoint thePoint;
};

#endif  // GAME_ITEMS_MAPMARK_H_
