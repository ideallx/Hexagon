#ifndef ANIMATIONCENTER_H
#define ANIMATIONCENTER_H

#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsLineItem>
#include <QPoint>
#include <QList>

class heroItem;
class gameMapElement;

class animationCenter
{
public:
    animationCenter();

    QGraphicsItemAnimation* gia() { return theGia; }
    QTimeLine* giaTimer() { return theGiaTimer; }
    void setLines(QList<QGraphicsLineItem*> lls) { targetLines = lls;}

    void moveAnimate(heroItem* item, gameMapElement* gme);
    void attackAnimate(heroItem* srcItem, heroItem* targetItem);

    void skillAnimate(heroItem* item, gameMapElement* gme);

private:
    QList<QGraphicsLineItem*> targetLines;
    QGraphicsItemAnimation* theGia;
    QTimeLine* theGiaTimer;
    QTimeLine* attackTimer;
    QTimeLine* targetTimer;
};

#endif // ANIMATIONCENTER_H
