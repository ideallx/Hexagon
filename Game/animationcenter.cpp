#include "animationcenter.h"
#include <QDebug>

animationCenter::animationCenter()
{
    theGia = new QGraphicsItemAnimation();
    theGiaTimer = new QTimeLine(500);
    theGiaAttackTimer = new QTimeLine(200);
    targetLine = new QGraphicsLineItem();
}

void animationCenter::moveAnimate(QGraphicsItem* item, QPointF oldPos, QPointF newPos)
{
    qDebug()<<"Move Animate Prepare";
    theGia->setItem(item);
    theGia->setTimeLine(theGiaTimer);

    double frame = 500*60/1000;

    double x = (newPos.x() - oldPos.x())/frame;
    double y = (newPos.y() - oldPos.y())/frame;

    for(int i=0; i<=frame; ++i)
        theGia->setPosAt(i/frame, oldPos+QPoint(x*i, y*i));
    theGiaTimer->start();
    qDebug()<<"Move Animate Start";
}

void animationCenter::attackAnimate(QGraphicsItem* item, QPointF oldPos, QPointF newPos, int damage)
{
    theGia->setItem(item);
    theGia->setTimeLine(theGiaAttackTimer);

    double frame = 200*60/1000;

    double x = (newPos.x() - oldPos.x())/frame;
    double y = (newPos.y() - oldPos.y())/frame;

    for(int i=0; i<=frame/2; ++i)
    {
        theGia->setPosAt(i/frame, oldPos+QPoint(x*i, y*i));
    }

    for(int i=0; i<=frame/2; ++i)
    {
        theGia->setPosAt((i+frame/2)/frame, oldPos+QPoint((frame/2-i)*x, (frame/2-i)*y));
    }

    theGiaAttackTimer->start();

}
