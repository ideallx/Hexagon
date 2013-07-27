#include "cardback.h"

cardBack::cardBack(QRectF rec, QString path)
{
    setRect(rec);
    this->path = path;
}

QRectF cardBack::boundingRect()
{
    return rect();
}

void cardBack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QPixmap(path + "backCard.png").scaledToHeight(rect().height()));
    painter->drawRect(rect());
}