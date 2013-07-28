#include "heroitem.h"

heroItem::heroItem(int lineLength)
{
    this->lineLength = lineLength;

    playerName = QString(tr("player 1"));

    setZValue(1.2);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, lineLength*1.6, lineLength*1.6);
}

QRectF heroItem::boundingRect() const
{
    return QRectF(rect());
}

void heroItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setOpacity(1.0);
    painter->setBrush(brush());
    painter->setPen(QPen(Qt::black, 3));
    painter->drawEllipse(rect());
}

QPainterPath heroItem::shape() const
{
    QPainterPath path;
    path.addEllipse(rect());
    return path;
}
