#include "backscene.h"

backScene::backScene(gameBackInfo* gbi, gameCoordinate *gc, QObject *parent) :
    gbi(gbi),
    gc(gc),
    QGraphicsScene(parent)
{
    //![0] settings
    scene->setSceneRect(gbi->getPixmap().rect());
    //![0] settings

    //![1] mapElement
    QVector<char> element = gbi->getMapElement();
    int wid = gbi->getWidthCount();
    int hei = gbi->getHeightCount();
    for(int j=0; j<hei; j++)
    {
        for(int i=0; i<wid; i++)
        {
            gameMapElement *mapItem = new gameMapElement(gbi->getLineLength(), element[i+j*wid], QPoint(i, j), gbi->getConfigDir());
            gc->addmapElement(mapItem);
            mapItem->hide();
            if(gc->isPointAvailable(QPoint(i, j)))
            {
                mapItem->setPos(gc->getBeginPosWithCoo(QPoint(i, j)));
                mapItem->show();
                scene->addItem(mapItem);
            }
        }
    }
    //![1] mapElement

    //![2] heros
    heroFactory *hf = new heroFactory(gbi->getConfigDir(), gbi->getLineLength(), gc, this);
    heroItem* h;
    h = hf->createHero(heroFactory::MieShaZhe, QPoint(1, 1), heroItem::camp_red);
    this->addItem(h);
    gc->addHero(h);
    h = hf->createHero(heroFactory::LeiShen, QPoint(0, 2), heroItem::camp_blue);
    this->addItem(h);
    gc->addHero(h);
    //![2] heros
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
