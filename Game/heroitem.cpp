#include "heroitem.h"

heroItem::heroItem(const QColor &color, int lineLength)
{
    this->lineLength = lineLength;
    this->color = color;

    playerName = QString(tr("player 1"));
    heroName = QString(tr("hero 1"));
    moveSphere = 6;
    attackSphere = 1;

    setZValue(0.6);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, lineLength, lineLength);
}


char heroItem::getSexual() const
{
    return sexual;
}

char heroItem::getMoveSphere() const
{
    return moveSphere;
}

QString heroItem::getPlayerName() const
{
    return playerName;
}

QString heroItem::getHeroName() const
{
    return heroName;
}

QRectF heroItem::boundingRect() const
{
    return QRectF(0, 0, lineLength, lineLength);
}

void heroItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setOpacity(0.8);
    QBrush brush = QBrush(QPixmap("F:/KuGou/vv/Resource/SkinDefault/hero1.png").scaledToWidth(lineLength));
    painter->setBrush(brush);
    painter->setPen(QPen(Qt::black, 3));
    painter->drawEllipse(0, 0, lineLength, lineLength);
}

void heroItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mousePressEvent(e);
    emit mouseClicked(e);
}

QPainterPath heroItem::shape() const
{
    QPainterPath path;
    path.addEllipse(0, 0, lineLength, lineLength);
    return path;
}

void heroItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    emit changeStatus(playerName + ": " + heroName);
}
