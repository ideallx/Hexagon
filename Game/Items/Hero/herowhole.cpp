#include "herowhole.h"

heroWhole::heroWhole(int lineLength, QObject *parent)
{
    setZValue(1.2);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, 6*lineLength, 8.75*lineLength);
    this->setParent(parent);
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

heroThumbnail::heroThumbnail(int lineLength, QObject *parent)
{
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, lineLength, lineLength);
    this->setParent(parent);
}

QRectF heroThumbnail::boundingRect() const
{
    return QRectF(rect());
}

void heroThumbnail::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setOpacity(1.0);
    painter->setBrush(brush());
    painter->setPen(QPen(Qt::black, 2));
    painter->drawRect(rect());
}

void heroThumbnail::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}

void heroThumbnail::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}
