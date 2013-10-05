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
 * 0 0 0 0 0 0   0x00  no condition
 * 1 1 1 1 1 1   0x3F  100%
 * 1 0 0 1 0 0   0x24  when the dice get 1 or 4
 */

AttackBuffSkill::AttackBuffSkill(enum AttackBuffEffect abe, int stateType,
                                 int probability, int cd, int cdmax, int effectTime)
    : SkillBase(cd, cdmax),
      availAble(true),
      theEffectTime(effectTime) {
    ab.abe = abe;
    ab.stateType = stateType;
    ab.damage = stateType;
    ab.probability = probability;
}

void AttackBuffSkill::skillPrepare(struct SkillPara sp) {
    Q_UNUSED(sp);
    if (theEffectTime <= 0)
        availAble = false;
    theEffectTime--;
}

void AttackBuffSkill::skillFlow(struct SkillPara sp) {
    skillAct(sp);
}

struct AttackBuff AttackBuffSkill::buffEffect() {
    return ab;
}

enum TriggerTime_t AttackBuffSkill::triggerTime() const {
    return TriggerAttackBegin;
}

RangeSkill::RangeSkill(enum MapRangeType_t t, int range,
                       int cd, int cdmax)
    : SkillBase(cd, cdmax),
      type(t),
      range(range) {
}

void RangeSkill::skillFlow(struct SkillPara sp) {
    skillAct(sp);
}

void RangeSkill::skillPrepare(struct SkillPara sp) {
    skillRange(sp);
}

void RangeSkill::skillRange(struct SkillPara sp) {
    sp.ec->showSkillRange(sp.from, RangeTypeRound, range);
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
    sp.ec->showSkillRange(sp.from, RangeTypeRound, range);
}

void MapMarkSkill::skillAct(struct SkillPara sp) {
    Q_UNUSED(sp);
    // mark->setPos(sp.ec);
}
