#include "sidescene.h"

sideScene::sideScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 280, 720);
}


void sideScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("%d, %d", event->scenePos().x(), event->scenePos().y());
}

void sideScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event->scenePos().x()<<event->scenePos().y();
}
