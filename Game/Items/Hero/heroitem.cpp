#include "heroitem.h"
#include "skillcenter.h"
#include "equipment.h"

HeroItem::HeroItem(int lineLength)
    : aa(new AttackAbility),
      ma(new MoveAbility),
      thePlayerName(tr("player 1")),
      theAvaPic(NULL),
      theWhoPic(NULL),
      theHealth(7),
      theMaxHealth(7),
      theSexual(Sexual::SexMale),
      lineLength(lineLength),
      theMoney(0),
      ai(NULL),
      isAlive(DeathStatus::Alive) {
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

void HeroItem::setHeroProperty(Sexual s, int ar, int m, int h) {
    theSexual = s;
    baseInfo.attackRange = ar;
    baseInfo.moveRange = m;
    theMaxHealth = h;
    theHealth = h;
    aa->setAttack(1);
    aa->setRange(ar);
    ma->setRange(m);
}


void HeroItem::setHeroProperty(HeroInfo hi) {
    theSexual = hi.sexual;
    theMaxHealth = hi.healthMax;
    theHealth = hi.healthMax;

    aa->setAttack(hi.attackRange);
    aa->setRange(hi.attackRange);
    ma->setRange(hi.moveRange);
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

void HeroItem::addCards(QList<int> c) {
    theCards += c;
}

int HeroItem::removeCard(int cardId) {
    if (theCards.removeOne(cardId)) {
        return cardId;
    } else {
        return -1;
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
QList<SkillBase*> HeroItem::hasSkillTriggerAt(TriggerTime time) {
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
        isAlive = DeathStatus::Dying;
    } else {
        return;
    }
}

void HeroItem::ambulance(bool get) {
    if (get) {
        isAlive = DeathStatus::Alive;
        theHealth = 2;
    } else {
        isAlive = DeathStatus::Died;
        theHealth = theMaxHealth;
    }
}

void HeroItem::beginTurnSettle() {
    aa->restore();
    ma->restore();
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
    Equipment* temp = equipments[static_cast<int>(eq->type())];
    if (temp) {
        qDebug() << "Aleady Has Same Type Equipment";
        return false;
    }
    temp = eq;
    return true;
}

bool HeroItem::removeEquipment(Equipment* eq) {
    Equipment* temp = equipments[static_cast<int>(eq->type())];
    if (temp != eq) {
        qDebug() << "Hero Hasn't Such Equipment";
        return false;
    }
    temp = NULL;
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

void HeroItem::addState(HeroState state, int lastTime) {
    QPair<HeroState, int> states;
    states.first = state;
    states.second = lastTime;
    heroStates.append(states);
}

void HeroItem::useMoney(QList<int> money) {
    foreach (int coin, money) {
        if (!moneyList.contains(coin)) {
            throw QString("HeroItem > useMoney : no such coin found");
        } else {
            moneyList.removeOne(coin);
            theMoney -= coin;
        }
    }
}
