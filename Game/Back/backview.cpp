#include "backview.h"

backview::backview(QWidget *parent)
{
    this->setParent(parent);
    this->initialSettrings();
}

backview::backview(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView(scene)
{
    this->setScene(scene);
    this->setParent(parent);
    this->initialSettrings();
}


void backview::initialSettrings()
{
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(QPainter::Antialiasing);
    this->setUpdatesEnabled(true);
    this->setCacheMode(CacheBackground);
}
