#include "heroitem.h"

heroItem::heroItem(int lineLength, QString path)
{
    this->lineLength = lineLength;
    this->path = path;

    playerName = QString(tr("player 1"));

    setZValue(1.2);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, lineLength, lineLength);
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

void heroItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mousePressEvent(e);
    emit mouseClicked(e);
}

QPainterPath heroItem::shape() const
{
    QPainterPath path;
    path.addEllipse(rect());
    return path;
}

void heroItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    emit changeStatus(playerName + ": " + heroName);
}
