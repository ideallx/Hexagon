#include "cardback.h"

CardBack::CardBack(QRectF rec, QString path)
    : path(path) {
    setRect(rec);
}

QRectF CardBack::boundingRect() {
    return rect();
}

void CardBack::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QPixmap(path + "backCard.png").
                      scaledToHeight(rect().height()));
    painter->drawRect(rect());
}
