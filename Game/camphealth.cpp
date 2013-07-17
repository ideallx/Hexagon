#include "camphealth.h"

campHealth::campHealth(QRectF rec, QObject *parent)
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
    painter->setPen(Qt::PenStyle::NoPen);
    painter->drawPixmap(pixmap().rect(), pixmap());
}
