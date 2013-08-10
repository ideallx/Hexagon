#include "camphealth.h"

campHealth::campHealth(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    setShapeMode(MaskShape);
}

QRectF campHealth::boundingRect()
{
    return this->pixmap().rect();
}

void campHealth::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(pixmap().rect(), pixmap());
}
