#include "animationcenter.h"
#include <QDebug>
#include "mapelement.h"
#include "heroitem.h"

animationCenter::animationCenter()
{
    theGia = new QGraphicsItemAnimation();
    theGiaTimer = new QTimeLine(500);
    attackTimer = new QTimeLine(200);
    targetTimer = new QTimeLine(500);
}

void animationCenter::moveAnimate(heroItem* item, gameMapElement* gme)
{
    item->setFlag(QGraphicsItem::ItemIsSelectable, false);
    qDebug()<<"Move Animate Prepare";
    theGia->setItem(item);
    theGia->setTimeLine(theGiaTimer);

    double frame = theGiaTimer->duration()/theGiaTimer->updateInterval();

    double x = (gme->scenePos().x() - item->scenePos().x())/frame;
    double y = (gme->scenePos().y() - item->scenePos().y())/frame;

    for(int i=0; i<=frame; ++i)
        theGia->setPosAt(i/frame, item->scenePos()+QPoint(x*i, y*i));
    theGiaTimer->start();
    qDebug()<<"Move Animate Start";
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void animationCenter::attackAnimate(heroItem* srcItem, heroItem* targetItem)
{
    srcItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    theGia->setItem(srcItem);
    theGia->setTimeLine(attackTimer);

    double frame = attackTimer->duration()/attackTimer->updateInterval();

    double x = (targetItem->scenePos().x() - srcItem->scenePos().x())/frame;
    double y = (targetItem->scenePos().y() - srcItem->scenePos().y())/frame;

    for(int i=0; i<=frame/2; ++i)
    {
        theGia->setPosAt(i/frame, targetItem->scenePos()+QPoint(x*i, y*i));
    }

    for(int i=0; i<=frame/2; ++i)
    {
        theGia->setPosAt((i+frame/2)/frame, targetItem->scenePos()+QPoint((frame/2-i)*x, (frame/2-i)*y));
    }

    attackTimer->start();
    srcItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void animationCenter::skillAnimate(heroItem* item, gameMapElement* gme)
{
    theGia->setItem(targetLines[0]);
    theGia->setTimeLine(targetTimer);

    QPointF oldP = item->scenePos();
    QPointF newP = gme->scenePos();

    double frame = targetTimer->duration()/targetTimer->updateInterval();

    double x = (newP.x() - oldP.x())/frame*2;
    double y = (newP.y() - oldP.y())/frame*2;

    targetLines[0]->setLine(0, 0, newP.x()-oldP.x(), newP.y()-oldP.y());
    targetLines[0]->setPos(oldP);
    targetLines[0]->show();


    //TODO
    for(int i=0; i<=frame/2; ++i)
    {
        theGia->setShearAt(i/frame, oldP.x()+x*i, oldP.y()+y*i);
    }

    for(int i=0; i<=frame/2; ++i)
    {
        theGia->setPosAt((i+frame/2)/frame, oldP+QPoint(x*i, y*i));
    }

    targetTimer->start();
}
