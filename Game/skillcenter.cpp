#include "skillcenter.h"
#include "heroitem.h"
#include "eventcenter.h"


AttackBuffSkill::AttackBuffSkill(enum AttackBuffEffect a,
                                 int effectTime)
    : availAble(true),
      theEffectTime(effectTime),
      abe(a) {
}

void AttackBuffSkill::skillPrepare(struct SkillPara sp) {
    if (theEffectTime <= 0)
        availAble = false;
    theEffectTime--;
    skillAct(sp);
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
