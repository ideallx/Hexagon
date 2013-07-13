#include "backview.h"

backview::backview(QGraphicsScene *scene, int lineLength, gameBackInfo* gbi)
    : QGraphicsView(scene)
{

    this->scene = scene;
//    for(int i=0; i<8; ++i)
//    {
//        heroItem *item = new heroItem(Qt::yellow, lineLength);
//        item->setPos(i*lineLength, 0);
//        scene->addItem(item);
//        items.append(item);
//        item->hide();
//    }
    QBrush b(gbi->getPixmap());
    this->setBackgroundBrush(b);
    this->lineLength = lineLength;
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setUpdatesEnabled(true);
    this->setCacheMode(CacheBackground);


    //item->setPos(gbi->getBeginPosWithCoo(QPoint(1, 1))+=QPointF(0.2*lineLength, 0.06*lineLength));
    //scene->addItem(item);
}
