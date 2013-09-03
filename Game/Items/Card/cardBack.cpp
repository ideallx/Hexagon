#include "cardback.h"

CardBack::CardBack(QRectF rec, QString path)
{
    setRect(rec);
    this->path = path;
}

QRectF CardBack::boundingRect()
{
    return rect();
}

void CardBack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QPixmap(path + "backCard.png").scaledToHeight(rect().height()));
    painter->drawRect(rect());
}
