#include <QDebug>
#include "skillcenter.h"
#include "heroitem.h"
#include "eventcenter.h"


AttackBuffSkill::AttackBuffSkill(enum AttackBuffEffect abe, int stateType,
                                 int probability, int effectTime)
    : availAble(true),
      theEffectTime(effectTime) {
    ab.abe = abe;
    ab.stateType = stateType;
    ab.probability = probability;
}

void AttackBuffSkill::skillPrepare(struct SkillPara sp) {
    Q_UNUSED(sp);
    if (theEffectTime <= 0)
        availAble = false;
    theEffectTime--;
}

void AttackBuffSkill::skillFlow(struct SkillPara sp) {
    Q_UNUSED(sp);
    skillAct(sp);
}

struct AttackBuff AttackBuffSkill::buffEffect() {
    return ab;
}

enum TriggerTime_t AttackBuffSkill::triggerTime() const {
    return TriggerAttackBegin;
}

RangeSkill::RangeSkill(enum MapRangeType_t t, int range)
    : type(t),
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

CsMoney::CsMoney(int money)
    : coin(money) {
}

void CsMoney::skillPrepare(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->addMoney(coin);
}

MapMarkSkill::MapMarkSkill(MapMark* mark, int range)
    : mark(mark),
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
    //mark->setPos(sp.ec);
}
