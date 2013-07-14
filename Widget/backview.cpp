#include "backview.h"

backview::backview(QGraphicsScene *scene, int lineLength, gameBackInfo* gbi)
    : QGraphicsView(scene)
{

    this->scene = scene;
    QBrush b(gbi->getPixmap());
    this->setBackgroundBrush(b);
    this->lineLength = lineLength;
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setUpdatesEnabled(true);
    this->setCacheMode(CacheBackground);
}
