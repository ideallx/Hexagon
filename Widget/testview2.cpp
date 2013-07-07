#include "testview2.h"

testView2::testView2(QGraphicsScene *scene, int lineLength)
    : QGraphicsView(scene)
{
    menu = new gameMenu(this);
    this->scene = scene;
    for(int i=0; i<8; ++i)
    {
        heroItem *item = new heroItem(Qt::yellow, lineLength, menu);
        item->setPos(i*lineLength, 0);
        scene->addItem(item);
        items.append(item);
        item->hide();
    }
    QBrush b(QColor("darkGray"));
    this->setBackgroundBrush(b);
    this->lineLength = lineLength;
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    items[1]->show();


}
