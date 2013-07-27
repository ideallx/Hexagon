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
    ic->setHeroFactory(new heroFactory(gbi, this), i);
    ic->setMapElement();

    this->setParent(parent);
}

void backScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
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
