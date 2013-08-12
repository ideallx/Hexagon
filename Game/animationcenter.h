#ifndef ANIMATIONCENTER_H
#define ANIMATIONCENTER_H

#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsLineItem>
#include <QPoint>

class animationCenter
{
public:
    animationCenter();

    QGraphicsItemAnimation* gia() { return theGia; }
    QTimeLine* giaTimer() { return theGiaTimer; }

    void moveAnimate(QGraphicsItem* item, QPointF oldPos, QPointF newPos);
    void attackAnimate(QGraphicsItem* item, QPointF oldPos, QPointF newPos, int damage);

private:
    QGraphicsLineItem* targetLine;
    QGraphicsItemAnimation* theGia;
    QTimeLine* theGiaTimer;
    QTimeLine* theGiaAttackTimer;
};

#endif // ANIMATIONCENTER_H
