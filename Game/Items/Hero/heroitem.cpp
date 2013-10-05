#include "heroitem.h"
#include "skillcenter.h"
#include "equipment.h"

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
      theMoney(0),
      nextMustHit(0) {
    setZValue(1.2);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, lineLength*1.6, lineLength*1.6);
    equipments.append(NULL);
    equipments.append(NULL);
    equipments.append(NULL);
    equipments.append(NULL);
}

QRectF HeroItem::boundingRect() const {
    return rect();
}

void HeroItem::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
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

void HeroItem::setHeroProperty(Sexual_t s, int a, int m, int h) {
    theSexual = s;
    baseInfo.attackRange = theAttackRange = a;
    baseInfo.moveRange = theMoveRange = m;
    theMaxHealth = h;
    theHealth = h;
    theAttack = 1;
}


void HeroItem::setHeroProperty(struct HeroInfo hi) {
    theSexual = hi.sexual;
    theAttackRange = hi.attackRange;
    theMoveRange = hi.moveRange;
    theMaxHealth = hi.healthMax;
    theHealth = hi.healthMax;
    theAttack = hi.attackRange;

    baseInfo = hi;
}

void HeroItem::setwholePic(QString path) {
    theWhoPic = new QPixmap(path);
}

void HeroItem::setSkillPics(QString path) {
    QPixmap pic = QPixmap(path.replace('*', '1'));
    theSkillButtons.append(pic);
    pic = QPixmap(path.replace('1', '2'));
    theSkillButtons.append(pic);
    pic = QPixmap(path.replace('2', '3'));
    theSkillButtons.append(pic);
}

void HeroItem::addCards(QList<HandCard*> c) {
    theCards += c;
}

HandCard* HeroItem::removeCard(HandCard* hc) {
    if (theCards.removeOne(hc)) {
        return hc;
    } else {
        return NULL;
    }
}

void HeroItem::addSkill(SkillBase* s) {
    if (!skills.contains(s))
        skills.append(s);
}

void HeroItem::addHeroSkill(SkillBase* s) {
    if (!heroSkills.contains(s))
        heroSkills.append(s);
}

void HeroItem::removeSkill(SkillBase* s) {
    if (skills.contains(s))
        skills.removeAt(skills.indexOf(s));
}

// TODO(ideallx) sort by priority
QList<SkillBase*> HeroItem::hasSkillTriggerAt(enum TriggerTime_t time) {
    QList<SkillBase*> result;
    for (int i = 0; i < skills.size(); i++) {
        if (skills[i]->triggerTime() == time) {
            result.append(skills[i]);
        }
    }
    return result;
}

void HeroItem::addHealth(int n) {
    theHealth += n;
    if (theHealth > theMaxHealth) {
        theHealth = theMaxHealth;
    } else if (theHealth < 0) {
        theHealth = 0;
    } else {
        return;
    }
}

void HeroItem::addNextAttackBouns(struct AttackBuff ab) {
    tempBuff.append(ab);
    if (ab.abe == AttackBuffAddDamage) {
        theAttack += ab.damage;
    } else if (ab.abe == AttackBuffMustHit) {
        nextMustHit |= ab.probability;  // just as its 100 percent
    }
}

void HeroItem::removetAttackBouns() {
    foreach(struct AttackBuff ab, tempBuff) {
        if (ab.abe == AttackBuffAddDamage) {
            theAttack -= ab.damage;
        } else if (ab.abe == AttackBuffMustHit) {
            nextMustHit = 0;  // just as its 100 percent
        }
    }
}

void HeroItem::endRoundSettle() {
    reduceAllSkillCooldown();
    reduceAllStatesCooldown();
}

void HeroItem::reduceAllSkillCooldown() {
    foreach(SkillBase* sb, heroSkills) {
        if (sb->cdNow() != 0) {
            sb->addCoolDown(-1);
        }
    }
}

void HeroItem::reduceAllStatesCooldown() {
    for (int i = 0; i < heroStates.size(); i++) {
        if (heroStates[i].second == 0)
            heroStates.removeAt(i);
        else
            heroStates[i].second--;
    }
}


bool HeroItem::addEquipment(Equipment* eq) {
    if (equipments[eq->type()]) {
        qDebug() << "Aleady Has Same Type Equipment";
        return false;
    }
    equipments[eq->type()] = eq;
    return true;
}

bool HeroItem::removeEquipment(Equipment* eq) {
    if (equipments[eq->type()] != eq) {
        qDebug() << "Hero Hasn't Such Equipment";
        return false;
    }
    equipments[eq->type()] = NULL;
    return true;
}

QList<int> HeroItem::skillCoolDown() {
    QList<int> result;
    for (int i = 0; i < heroSkills.size(); i++) {
        result.append(heroSkills[i]->cdNow());
    }
    return result;
}


SkillBase* HeroItem::getHeroSkill(int n) {
    if (n < 0 || n > 3)
        return NULL;
    else
        return heroSkills[n];
}

void HeroItem::addState(enum HeroState_t state, int lastTime) {
    QPair<enum HeroState_t, int> states;
    states.first = state;
    states.second = lastTime;
    heroStates.append(states);
}

