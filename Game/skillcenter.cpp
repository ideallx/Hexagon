#include "skillcenter.h"
#include "heroitem.h"
#include "eventcenter.h"


AttackBuffSkill::AttackBuffSkill(enum AttackBuffEffect a,
                                 int effectTime)
    : availAble(true),
      theEffectTime(effectTime),
      abe(a) {
}

void AttackBuffSkill::skillFlow(EventCenter* ec, QVariant &data,
                                QGraphicsItem* from, QGraphicsItem* to) {
    if (theEffectTime <= 0)
        availAble = false;
    theEffectTime--;
    skillAct(ec, data, from, to);
}

enum TriggerTime_t AttackBuffSkill::triggerTime() const {
    return TriggerAttackBegin;
}

void AttackBuffSkill::skillAct(EventCenter* ec, QVariant &data,
                               QGraphicsItem* from, QGraphicsItem* to) {
    return;
}

ShiftSkill::ShiftSkill(enum MapRangeType_t t, int range)
    : type(t),
      range(range) {
}

void ShiftSkill::skillFlow(EventCenter* ec, QVariant &data,
                           QGraphicsItem *from, QGraphicsItem *to) {
    ec->showSkillRange(from, RangeTypeRound, 2);
}
