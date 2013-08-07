#include "carditem.h"

handCard::handCard(int t, QString s):
    type(t),
    pixmapPath(QPixmap(s))
{
    setRect(0, 0, 137, 200);
    setBrush(pixmapPath.scaledToHeight(200, Qt::SmoothTransformation));
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
