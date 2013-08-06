#include "layoutscene.h"
#include <QtWidgets>
#include <cardengine.h>

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


void essenialScene::setContent(struct essenialContent ec)
{
    moveRange->setPlainText(preMr + QString::number(ec.mr));
    attackRange->setPlainText(preAr + QString::number(ec.ar));
    attack->setPlainText(preA + QString::number(ec.a));
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

}

cardScene::~cardScene()
{

}


void cardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"cardScene"<<event->scenePos();
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
