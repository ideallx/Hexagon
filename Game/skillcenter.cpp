#include "skillcenter.h"

/*
SkillBase::SkillBase()
    :type(SkillPositive),
    time(TriggerGameBegin),
    priority(0),
    coolDownTime(0),
    curCD(0),
    name("no skill") {
}
*/

AttackBuffSkill::AttackBuffSkill(enum AttackBuffEffect a,
                                 int effectTime)
    :theEffectTime(effectTime),
      abe(a) {
}

void AttackBuffSkill::skillFlow() {
    if (theEffectTime <= 0)
        delete this;
    theEffectTime--;
    askForChangeHealth()
}
