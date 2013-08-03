#include "buttomui.h"

buttomUi::buttomUi(QString path)
{
    setShapeMode(MaskShape);
    setPixmap(QPixmap(path+"eee.png"));
    setFlag(ItemIsPanel);
}

QRectF buttomUi::boundingRect()
{
    return this->pixmap().rect();
}

void buttomUi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::PenStyle::NoPen);
    painter->drawPixmap(pixmap().rect(), pixmap());
}
