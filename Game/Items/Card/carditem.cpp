#include "carditem.h"

handCard::handCard(int t, QString s):
    type(t),
    pixmapPath(QPixmap(s))
{
    setRect(0, 0, 194, 282);
    if(pixmapPath.isNull())
        qDebug()<<s;
    setBrush(pixmapPath);
}

QRectF handCard::boundingRect() const
{
    return rect();
}

void handCard::paint(QPainter* p, const QStyleOptionGraphicsItem* i, QWidget* w)
{
    p->setBrush(brush());
    p->drawRect(rect());
}
