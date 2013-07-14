#include "carditem.h"

cardItem::cardItem(QRectF rec)
{
    setRect(rec);
    qDebug()<<rec.x()<<rec.y()<<rec.width()<<rec.height();
}

QRectF cardItem::boundingRect()
{
    return rect();
}

void cardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QPixmap("F:/KuGou/vv/Resource/SkinDefault/backCard.png").scaledToHeight(rect().height()));
    painter->drawRect(rect());
}
