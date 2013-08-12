#include "heroitem.h"

heroItem::heroItem(int lineLength)
{
    this->lineLength = lineLength;

    thePlayerName = QString(tr("player 1"));

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
    painter->setOpacity(1.0);
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawEllipse(rect());
}

QPainterPath heroItem::shape() const
{
    QPainterPath path;
    path.addEllipse(rect());
    return path;
}


void heroItem::setHeroProperty(char s, char a, char m, int h)
{
    theSexual = s;
    theAttackRange = a;
    theMoveRange = m;
    theMaxHealth = h;
    theHealth = h;

    theAttack = 1;
}

void heroItem::setwholePic(QPixmap*p)
{
    theWhoPic = p;
    QPixmap skillPic;

    skillPic = p->copy(0.098*p->width(), 0.895*p->height(), 0.1375*p->width(), 0.1375*p->width());
    theSkillButtons.append(skillPic);
    skillPic = p->copy(0.352*p->width(), 0.895*p->height(), 0.1375*p->width(), 0.1375*p->width());
    theSkillButtons.append(skillPic);
    skillPic = p->copy(0.602*p->width(), 0.895*p->height(), 0.1375*p->width(), 0.1375*p->width());
    theSkillButtons.append(skillPic);

}


void heroItem::addCards(QList<handCard*> c)
{
    theCards += c;
}
