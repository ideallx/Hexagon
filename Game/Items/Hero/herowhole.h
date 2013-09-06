#ifndef GAME_ITEMS_HERO_HEROWHOLE_H_
#define GAME_ITEMS_HERO_HEROWHOLE_H_

#include <QGraphicsRectItem>
#include <QtWidgets>

class HeroWhole : public QObject, public QGraphicsRectItem {
    Q_OBJECT
 public:
    HeroWhole(int lineLength, QObject *parent = 0);

 private:
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

class heroThumbnail : public QObject, public QGraphicsRectItem {
 public:
    heroThumbnail(int lineLength, QObject *parent = 0);

 private:
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif  // GAME_ITEMS_HERO_HEROWHOLE_H_
