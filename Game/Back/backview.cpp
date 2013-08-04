#include "backview.h"

backview::backview(QWidget *parent)
{
    this->setParent(parent);
    this->initialSettrings();
}

backview::backview(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView(scene)
{
    this->setParent(parent);
    this->initialSettrings();
}


void backview::initialSettrings()
{
    this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setUpdatesEnabled(true);
    this->centerOn(QPointF(0, 0));//TODO
}

void backview::resizeEvent(QResizeEvent *e)
{
    qreal w1 = e->size().width();
    qreal w2 = scene()->width();
    if(w1 <= w2)
    {
        this->centerOn(0, 0); //TODO
        qreal ff = 1.0;
        matrix.reset();
        matrix.scale(ff, ff);
        setMatrix(matrix);
    }
    else
    {
        qreal ff = w1/w2;
        matrix.reset();
        matrix.scale(ff, ff);
        setMatrix(matrix);
    }

}
