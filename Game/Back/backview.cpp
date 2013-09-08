#include "BackView.h"

BackView::BackView(QWidget *parent) {
    this->setParent(parent);
    this->initialSettrings();
}

BackView::BackView(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView(scene) {
    this->setParent(parent);
    this->initialSettrings();
}


void BackView::initialSettrings() {
    this->setSizePolicy(
                QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(
                QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setUpdatesEnabled(true);
}

void BackView::resizeEvent(QResizeEvent *e) {
    if (scene() == NULL)
        return;
    qreal w1 = e->size().width();
    qreal w2 = scene()->width();
    if (w1 <= w2) {
        qreal ff = 1.0;
        matrix.reset();
        matrix.scale(ff, ff);
        setMatrix(matrix);
    } else {
        qreal ff = w1/w2;
        matrix.reset();
        matrix.scale(ff, ff);
        setMatrix(matrix);
    }
}
