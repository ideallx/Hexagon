#include "heroitem.h"

heroItem::heroItem(const QColor &color, int lineLength, gameMenu* menu)
{
    this->lineLength = lineLength;
    this->color = color;
    this->menu = menu;

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, lineLength, lineLength);
   // emit heroInvokeMenu(QPointF(50, 50));
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
        menu->hideAllMenu();
        menu->showMenu(gameMenu::MENULIST, e->pos());
    }
}
