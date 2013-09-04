#ifndef GAME_ITEMS_CAMPHEALTH_H_
#define GAME_ITEMS_CAMPHEALTH_H_

#include <QGraphicsRectItem>
#include <QPainter>

class CampHealth : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

 public:
    explicit CampHealth(const QPixmap &pixmap, QGraphicsItem *parent = 0);

 private:
    QRectF boundingRect();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif  // GAME_ITEMS_CAMPHEALTH_H_
