#include "backview.h"

backview::backview(QGraphicsScene *scene, int lineLength)
    : QGraphicsView(scene)
{
    this->lineLength = lineLength;
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(QPainter::Antialiasing);
    this->setUpdatesEnabled(true);
    this->setCacheMode(CacheBackground);
}
