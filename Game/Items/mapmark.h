#ifndef MAPMARK_H
#define MAPMARK_H

#include <QGraphicsEllipseItem>

class MapMark : public QObject, public QGraphicsEllipseItem {
 public:
    MapMark(QString path, int width);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // MAPMARK_H
