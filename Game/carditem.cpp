#include "carditem.h"

cardItem::cardItem(QRectF rec, QString path)
{
    setRect(rec);
    this->path = path;
}

QRectF cardItem::boundingRect()
{
    return rect();
}

void cardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QPixmap(path + "backCard.png").scaledToHeight(rect().height()));
    painter->drawRect(rect());
}
