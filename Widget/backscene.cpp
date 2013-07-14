#include "backscene.h"

backScene::backScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void backScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

bool backScene::eventFilter(QObject *watched, QEvent *event)
{
    return false;
}

void backScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}
