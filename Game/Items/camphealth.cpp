#include "camphealth.h"

CampHealth::CampHealth(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent) {
    setShapeMode(MaskShape);
}

QRectF CampHealth::boundingRect() {
    return this->pixmap().rect();
}

void CampHealth::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(pixmap().rect(), pixmap());
}
