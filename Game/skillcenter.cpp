#include "skillcenter.h"
#include "heroitem.h"


AttackBuffSkill::AttackBuffSkill(enum AttackBuffEffect a,
                                 int effectTime)
    : availAble(true),
      theEffectTime(effectTime),
      abe(a) {
}

void AttackBuffSkill::skillFlow(HeroItem* from, HeroItem* to) {
    if (theEffectTime <= 0)
        availAble = false;
    theEffectTime--;
    skillAct(from, to);
}

enum TriggerTime_t AttackBuffSkill::triggerTime() const {
    return TriggerAttackBegin;
}

void AttackBuffSkill::terminateSkill() {
    return;
}

void AttackBuffSkill::skillAct(HeroItem* from, HeroItem* to) {
}
