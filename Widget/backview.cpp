#include "backview.h"

backview::backview(QGraphicsScene *scene, int lineLength)
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
    QBrush b(globol::gbi->getPixmap());
    this->setBackgroundBrush(b);
    this->lineLength = lineLength;
    qDebug("%d", lineLength);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QVector<char> element = globol::gbi->getMapElement();
    int wid = globol::gbi->getWidthCount();
    int hei = globol::gbi->getHeightCount();

    for(int i=0; i<wid; i++)
    {
        for(int j=0; j<hei; j++)
        {
            QGraphicsItem *mapItem = new gameMapElement(element[i+j*wid]);
            if(globol::gbi->isPointAvailable(QPoint(i, j)))
            {
                mapItem->setPos(globol::gbi->getBeginPosWithCoo(QPoint(i, j)));
                scene->addItem(mapItem);
            }
        }
    }
    heroItem *item = new heroItem(Qt::yellow, lineLength*1.6);
    scene->addItem(item);


}
