#include "backscene.h"

backScene::backScene(gameBackInfo* gbi, gameCoordinate *gc, QList<heroFactory::ExternInfo> i, QObject *parent) :
    gbi(gbi),
    gc(gc)
{
    //![0] settings
    this->setSceneRect(gbi->getPixmap().rect());
    //![0] settings

    ic = new itemCollector(gbi, gc, this);
    ic->setCardEngine(new cardEngine());
    ic->setHeroFactory(new heroFactory(gbi), i);
    ic->setMapElement();

    this->setParent(parent);
}

void backScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static QPoint oldPoint;
    QPoint newPoint = gc->getCooxWithPos(event->scenePos());
    if((oldPoint == newPoint) || !ic->isPointAvailable(newPoint))
    {
       return;
    }
    oldPoint = newPoint;
    qDebug("new %d %d", newPoint.x(), newPoint.y());
    emit mapElementMovedIn(newPoint);
}

bool backScene::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);
    Q_UNUSED(event);
    return false;
}

void backScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}
