#include <QDebug>
#include "skillcenter.h"
#include "heroitem.h"
#include "eventcenter.h"


void SkillBase::addCoolDown(int n) {
    if (n + cooldown > cooldownMax) {
        cooldown = cooldownMax;
    } else if (n + cooldown < 0) {
        cooldown = 0;
    } else {
        cooldown += n;
    }
}

/*
 * probability every bit is a side of the dice
 * 0 0 0 0 0 0 0 0   0x00  no condition
 * 0 0 1 1 1 1 1 1   0x3F  100%
 * 0 0 1 0 0 1 0 0   0x24  when the dice get 1 or 4
 */

AttackBuffSkill::AttackBuffSkill(AttackBuffEffect abe, int stateType,
                                 int probability, int cd, int cdmax, int duration)
    : SkillBase(cd, cdmax),
      availAble(true),
      theEffectTime(duration) {
    ab.abe = abe;
    ab.stateType = stateType;
    ab.damage = stateType;
    ab.probability = probability;
    ab.duration = duration;
}

void AttackBuffSkill::skillPrepare(SkillPara sp) {
    if (theEffectTime <= 0) {
        throw QString("skill dont cooldown now");
    }
    skillClicked(sp);
    qDebug() << objectName() << "triggered";
}

void AttackBuffSkill::skillFlow(SkillPara sp) {
    skillAct(sp);
    theEffectTime--;
    qDebug() << objectName() << "acted";
}

AttackBuff AttackBuffSkill::buffEffect() {
    return ab;
}

TriggerTime AttackBuffSkill::triggerTime() const {
    return TriggerTime::AttackBegin;
}

RangeSkill::RangeSkill(MapRangeType t, int range,
                       int cd, int cdmax)
    : SkillBase(cd, cdmax),
      type(t),
      range(range) {
}

void RangeSkill::skillFlow(SkillPara sp) {
    skillAct(sp);
    qDebug() << objectName() << "acted";
}

void RangeSkill::skillPrepare(SkillPara sp) {
    skillRange(sp);
    qDebug() << objectName() << "triggered";
}

void RangeSkill::skillRange(SkillPara sp) {
    sp.ec->showSkillRange(sp.from, MapRangeType::Round, range);
}

CsMoney::CsMoney(int money, int cd, int cdmax)
    : SkillBase(cd, cdmax),
      coin(money) {
}

void CsMoney::skillPrepare(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->addMoney(coin);
}

MapMarkSkill::MapMarkSkill(MapMark* mark, int range, int cd, int cdmax)
    : SkillBase(cd, cdmax),
      mark(mark),
      range(range) {
}

void MapMarkSkill::skillFlow(SkillPara sp) {
    skillAct(sp);
}

void MapMarkSkill::skillPrepare(SkillPara sp) {
    skillRange(sp);
}

void MapMarkSkill::skillRange(SkillPara sp) {
    sp.ec->showSkillRange(sp.from, MapRangeType::Round, range);
}

void MapMarkSkill::skillAct(SkillPara sp) {
    Q_UNUSED(sp);
    // mark->setPos(sp.ec);
}
