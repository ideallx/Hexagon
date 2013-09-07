#include "heroitem.h"
#include "skillcenter.h"

HeroItem::HeroItem(int lineLength)
    : thePlayerName(tr("player 1")),
    theAttack(1),
    theAvaPic(NULL),
    theWhoPic(NULL),
    theHealth(7),
    theMaxHealth(7),
    theSexual(sex_male),
    theMoveRange(2),
    theAttackRange(1),
    lineLength(lineLength),
    theMoney(0) {
    setZValue(1.2);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, lineLength*1.6, lineLength*1.6);
}

QRectF HeroItem::boundingRect() const {
    return QRectF(rect());
}

void HeroItem::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
    Q_UNUSED(option);
    painter->setOpacity(1.0);
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawEllipse(rect());
}

QPainterPath HeroItem::shape() const {
    QPainterPath path;
    path.addEllipse(rect());
    return path;
}

void HeroItem::setHeroProperty(char s, char a, char m, int h) {
    theSexual = s;
    theAttackRange = a;
    theMoveRange = m;
    theMaxHealth = h;
    theHealth = h;

    theAttack = 1;
}


void HeroItem::setHeroProperty(struct heroInfo hi) {
    theSexual = hi.sexual;
    theAttackRange = hi.attackRange;
    theMoveRange = hi.moveRange;
    theMaxHealth = hi.healthMax;
    theHealth = hi.healthMax;

    theAttack = hi.attackRange;
}

void HeroItem::setwholePic(QPixmap*p) {
    theWhoPic = p;
    QPixmap skillPic;

    skillPic = p->copy(0.098*p->width(), 0.895*p->height(),
                       0.1375*p->width(), 0.1375*p->width());
    theSkillButtons.append(skillPic);

    skillPic = p->copy(0.352*p->width(), 0.895*p->height(),
                       0.1375*p->width(), 0.1375*p->width());
    theSkillButtons.append(skillPic);

    skillPic = p->copy(0.602*p->width(), 0.895*p->height(),
                       0.1375*p->width(), 0.1375*p->width());
    theSkillButtons.append(skillPic);
}


void HeroItem::addCards(QList<HandCard*> c) {
    theCards += c;
}

void HeroItem::addSkill(SkillBase* s) {
    if (!skills.contains(s))
        skills.append(s);
}

void HeroItem::removeSkill(SkillBase* s) {
    if (skills.contains(s))
        skills.removeAt(skills.indexOf(s));
}

QList<SkillBase*> HeroItem::hasSkillTriggerAt(enum triggerTime_t time) {
    QList<SkillBase*> result;
    for (int i = 0; i < skills.size(); i++) {
        if (skills[i]->triggerTime() == time) {
            result.append(skills[i]);
        }
    }
    return result;
}
