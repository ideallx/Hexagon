#include "heroitem.h"

heroItem::heroItem(const QColor &color, int lineLength)
{
    this->lineLength = lineLength;
    this->color = color;

    setFlags(ItemIsSelectable | ItemIsMovable);
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
//    QImage origin(":/resource/SkinDefault/iconTest.jpg");
//    QPixmap pictoshow = QPixmap::fromImage(origin.scaled(lineLength, lineLength, Qt::KeepAspectRatioByExpanding));
    painter->setBrush(color);
    //painter->setPen(Qt::white);
    painter->drawEllipse(0, 0, lineLength, lineLength);
}

void heroItem::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mouseMoveEvent(e);
}

void heroItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mousePressEvent(e);
    if(e->button() & Qt::LeftButton)
    {
        showHideAllList(menuList, 's', e->pos());
    }
}
