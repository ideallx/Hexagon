#include "layoutscene.h"
#include "cardengine.h"
#include "carditem.h"

EssenialScene::EssenialScene() {
    preMr = tr("Move Range: ");
    preAr = tr("Attack Range: ");
    preA  = tr("Attack: ");
    preMo = tr("Money: ");

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

    money = new QGraphicsTextItem;
    money->setPlainText(preMo);
    money->setPos(0, 60);
    this->addItem(money);
}

EssenialScene::~EssenialScene() {
    delete moveRange;
    delete attackRange;
    delete attack;
    delete money;
}


void EssenialScene::setContent(panelInfo pi) {
    QString text;

    text = preMr + QString::number(pi.moveRange);
    if (pi.moveRangeBouns > 0)
        text += " + " + QString::number(pi.moveRangeBouns);
    else if (pi.moveRangeBouns < 0)
        text += " - " + QString::number(qAbs(pi.moveRangeBouns));
    moveRange->setPlainText(text);

    text = preA + QString::number(pi.attack);
    if (pi.attackBouns > 0)
        text += " + " + QString::number(pi.attackBouns);
    else if (pi.attackBouns < 0)
        text += " - " + QString::number(qAbs(pi.attackBouns));
    attack->setPlainText(text);

    text = preAr + QString::number(pi.attack);
    if (pi.attackRangeBouns > 0)
        text += " + " + QString::number(pi.attackRangeBouns);
    else if (pi.attackRangeBouns < 0)
        text += " - " + QString::number(qAbs(pi.attackRangeBouns));
    attackRange->setPlainText(text);

    text = preMo;
    if (pi.moneyList.size() == 0) {
        text += "0";
    } else {
        text += QString::number(pi.moneyList[0]);
        for (int i = 1; i < pi.moneyList.size(); i++) {
            text += "+" + QString::number(pi.moneyList[i]);
        }
    }
    money->setPlainText(text);
}


SkillScene::SkillScene() {
    skill1 = new QGraphicsEllipseItem;
    skill2 = new QGraphicsEllipseItem;
    skill3 = new QGraphicsEllipseItem;

    QList<QGraphicsEllipseItem* > skills;
    skills.append(skill1);
    skills.append(skill2);
    skills.append(skill3);

    for (int i = 0; i < skills.size(); i++) {
        skills[i]->setRect(0, 0, 80, 80);
        skills[i]->setBrush(Qt::blue);
        skills[i]->setPos(20+100*i, 15);
        this->addItem(skills[i]);
    }
}

SkillScene::~SkillScene() {
    delete skill1;
    delete skill2;
    delete skill3;
}


void SkillScene::setHeroSkillButton(QList<QPixmap> in) {
    if (!in[0].isNull())
        skill1->setBrush(in[0].scaledToHeight(80,
                                              Qt::SmoothTransformation));
    if (!in[1].isNull())
        skill2->setBrush(in[1].scaledToHeight(80,
                                              Qt::SmoothTransformation));
    if (!in[2].isNull())
        skill3->setBrush(in[2].scaledToHeight(80,
                                              Qt::SmoothTransformation));
    skill1->setPen(Qt::NoPen);
    skill2->setPen(Qt::NoPen);
    skill3->setPen(Qt::NoPen);
}

void SkillScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->scenePos();
    QPointF circleCenter = QPointF(55, 50);
    QPointF calc = pos - circleCenter;

    for (int i = 0; i < 3; i++) {
        calc = pos - circleCenter;
        calc.setX(calc.x()-100*i);
        if ((calc.x()*calc.x() + calc.y()*calc.y()) < 35*35) {
            qDebug("Skill %d Clicked", i+1);
            emit heroSkillUsed(i);
        }
    }
}


QGraphicsEllipseItem* SkillScene::getSkill(int n) {
    switch (n) {
    case 0:
        return skill1;
    case 1:
        return skill2;
    case 2:
        return skill3;
    default:
        return NULL;
    }
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

CardScene::CardScene()
    : cardGroup(this->createItemGroup(this->items())),
      oldItem(0),
      chosenNumber(1) {
}

CardScene::~CardScene() {
}

void CardScene::clearChosenItems() {
    chosenItem.clear();
}

void CardScene::listCards() {
    double y = 0.2*height();
    QList<QGraphicsItem*> cards = items();
    if (cards.size() == 0)
        return;
    double cardWidth = cards[0]->boundingRect().width();
    double xInterval;

    if (cards.size()*cardWidth > width())
        xInterval = (width()-cardWidth)/(cards.size()-1);
    else
        xInterval = cardWidth;

    for (int i = 0; i < cards.size(); i++) {
        cards[cards.size()-1-i]->setPos(i*xInterval, y);
    }
}

void CardScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() & Qt::RightButton) {
        clearChosenItems();
        listCards();
        return;
    }

    if (!oldItem)
        return;

    if (chosenItem.contains(oldItem)) {
        oldItem->setPos(oldItem->pos().x(), 0.2 * height());
        chosenItem.removeAt(chosenItem.indexOf(oldItem));
    } else {
        if (chosenNumber == 1) {
            clearChosenItems();
            listCards();
        }
        oldItem->setPos(oldItem->pos().x(), 0);
        chosenItem.append(oldItem);
    }

    emit chosenNCard(chosenItem.size());
}

void CardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    curItem = itemAt(event->scenePos(), qtf);
    if (event->scenePos().x() == 0 ||
            event->scenePos().x() == width() ||
            event->scenePos().y() == height() ||
            event->scenePos().y() == 0) {
        if (oldItem)
            if (!chosenItem.contains(oldItem))
                oldItem->setPos(oldItem->pos().x(), 0.2*height());
    }

    if (oldItem == curItem)
        return;

    if (oldItem)
        if (!chosenItem.contains(oldItem))
            oldItem->setPos(oldItem->pos().x(), 0.2*height());

    if (curItem) {
        if (!chosenItem.contains(curItem)) {
            curItem->setPos(curItem->pos().x(), 0.1*height());
        }
        oldItem = curItem;
    }
}

QList<int> CardScene::getChosenItems() {
    QList<int> result;
    foreach(QGraphicsItem* qgi, chosenItem) {
        result.append(static_cast<HandCard*>(qgi)->type());
    }
    return result;
}

ViewSendResize::ViewSendResize(QWidget *parent)
    : QGraphicsView(parent) {
}

ViewSendResize::~ViewSendResize() {
}

void ViewSendResize::resizeEvent(QResizeEvent *e) {
    Q_UNUSED(e);
    emit resized();
}
