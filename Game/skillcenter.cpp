#include "skillcenter.h"

SkillBase::SkillBase()
    :type(SkillPositive),
    time(TriggerGameBegin),
    priority(0),
    coolDownTime(0),
    curCD(0),
    name("no skill") {
}
