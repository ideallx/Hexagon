#include "skillcenter.h"
#include "heroitem.h"


AttackBuffSkill::AttackBuffSkill(enum AttackBuffEffect a,
                                 int effectTime)
    : availAble(true),
      theEffectTime(effectTime),
      abe(a) {
}

void AttackBuffSkill::skillFlow(QGraphicsItem* from, QGraphicsItem* to) {
    if (theEffectTime <= 0)
        availAble = false;
    theEffectTime--;
    skillAct(from, to);
}

enum TriggerTime_t AttackBuffSkill::triggerTime() const {
    return TriggerAttackBegin;
}

void AttackBuffSkill::skillAct(QGraphicsItem* from, QGraphicsItem* to) {
}

ShiftSkill::ShiftSkill(enum MapRangeType_t t, int range)
    : type(t),
      range(range) {
}

void ShiftSkill::skillFlow(QGraphicsItem *from, QGraphicsItem *to) {

}
