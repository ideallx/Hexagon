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
}

void backview::resizeEvent(QResizeEvent *e)
{
    qreal w1 = e->size().width();
    qreal w2 = 1200;
    qreal ff = w1/w2;
    qDebug()<<ff<<w1<<w2;
    //qDebug()<<ff<<e->size().width()<<size().width();
    QMatrix matrix;
    matrix.scale(ff, ff);
    setMatrix(matrix);

}
