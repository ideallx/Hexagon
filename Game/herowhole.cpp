#include "herowhole.h"

heroWhole::heroWhole(int lineLength, QObject *parent)
{
    this->lineLength = lineLength;
    setZValue(1.2);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, 6*lineLength, 8.75*lineLength);
}

QRectF heroWhole::boundingRect() const
{
    return QRectF(rect());
}

void heroWhole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setOpacity(1.0);
    painter->setBrush(brush());
    painter->setPen(QPen(Qt::black, 2));
    painter->drawRect(rect());
}

void heroWhole::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}

void heroWhole::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}
