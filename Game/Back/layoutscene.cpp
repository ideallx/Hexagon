#include "layoutscene.h"
#include "cardengine.h"

essenialScene::essenialScene()
{
    preMr = tr("Move Range: ");
    preAr = tr("Attack Range: ");
    preA  = tr("Attack: ");

    moveRange = new QGraphicsTextItem;
    moveRange->setPlainText(preMr);
    moveRange->setPos(0, 0);
    this->addItem(moveRange);

    attackRange = new QGraphicsTextItem;
    attackRange->setPlainText(preAr);
    attackRange->setPos(0, 20);
    this->addItem(attackRange);

    attack = new QGraphicsTextItem;
    attack->setPlainText(preA);
    attack->setPos(0, 40);
    this->addItem(attack);
}

essenialScene::~essenialScene()
{
    delete moveRange;
    delete attackRange;
    delete attack;
}


void essenialScene::setContent(struct panelInfo pi)
{
    moveRange->setPlainText(preMr + pi.moveRange);
    attackRange->setPlainText(preAr + pi.attackRange);
    attack->setPlainText(preA + pi.attack);
}


skillScene::skillScene()
{
    skill1 = new QGraphicsEllipseItem;
    skill2 = new QGraphicsEllipseItem;
    skill3 = new QGraphicsEllipseItem;

    QList<QGraphicsEllipseItem* > skills;
    skills.append(skill1);
    skills.append(skill2);
    skills.append(skill3);

    for(int i=0; i<skills.size(); i++)
    {
        skills[i]->setRect(0, 0, 70, 70);
        skills[i]->setBrush(Qt::blue);
        skills[i]->setPos(40+80*i, 15);
        this->addItem(skills[i]);
    }

}

skillScene::~skillScene()
{
    delete skill1;
    delete skill2;
    delete skill3;
}


void skillScene::setHeroSkillButton(QList<QPixmap>in)
{
    skill1->setBrush(in[0].scaledToHeight(80, Qt::SmoothTransformation));
    skill2->setBrush(in[1].scaledToHeight(80, Qt::SmoothTransformation));
    skill3->setBrush(in[2].scaledToHeight(80, Qt::SmoothTransformation));
}

/*
skillButton::skillButton()
{
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
}

void skillButton::paint(QPainter *p, const QStyleOptionGraphicsItem *i, QWidget *w)
{
    p->setBrush(brush());
    p->drawEllipse(rect());
}

QRectF skillButton::boundingRect() const
{
    return QRectF(rect());
}
*/

cardScene::cardScene()
{
    cardGroup = this->createItemGroup(this->items());
    oldItem = 0;
}

cardScene::~cardScene()
{

}

void cardScene::clearChosenItems()
{
    chosenItem.clear();
}

void cardScene::listCards()
{
    double y = 0.2*height();
    QList<QGraphicsItem*> cards = items();
    if(cards.size() == 0)
        return;
    double cardWidth = cards[0]->boundingRect().width();
    double xInterval;

    if(cards.size()*cardWidth > width())
        xInterval = (width()-cardWidth)/(cards.size()-1);
    else
        xInterval = cardWidth;

    for(int i=0; i<cards.size(); i++)
    {
        cards[cards.size()-1-i]->setPos(i*xInterval, y);
    }
}

void cardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() & Qt::RightButton)
    {
        clearChosenItems();
        listCards();
        return;
    }

    if(!oldItem)
        return;

    if(chosenItem.contains(oldItem))
    {
        oldItem->setPos(oldItem->pos().x(), 0.2*height());
        chosenItem.remove(chosenItem.indexOf(oldItem));
    }
    else
    {
        oldItem->setPos(oldItem->pos().x(), 0);
        chosenItem.append(oldItem);
    }

    qDebug()<<"append";
}

void cardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    curItem = itemAt(event->scenePos(), qtf);

    if(event->scenePos().x() == 0 ||
            event->scenePos().x() == width() ||
            event->scenePos().y() == height() ||
            event->scenePos().y() == 0)
    {
        if(oldItem)
            if(!chosenItem.contains(oldItem))
                oldItem->setPos(oldItem->pos().x(), 0.2*height());
    }

    if(oldItem == curItem)
        return;

    if(oldItem)
        if(!chosenItem.contains(oldItem))
            oldItem->setPos(oldItem->pos().x(), 0.2*height());

    if(curItem)
    {
        if(!chosenItem.contains(curItem))
        {
            curItem->setPos(curItem->pos().x(), 0.1*height());
        }
        oldItem = curItem;
    }
}

viewSendResize::viewSendResize(QWidget *parent) :
    QGraphicsView(parent)
{

}

viewSendResize::~viewSendResize()
{

}

void viewSendResize::resizeEvent(QResizeEvent *e)
{
    emit resized();
}
