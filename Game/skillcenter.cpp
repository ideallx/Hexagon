#include <QDebug>
#include "skillcenter.h"
#include "heroitem.h"
#include "eventcenter.h"


AttackBuffSkill::AttackBuffSkill(struct AttackBuff ab,
                                 int effectTime)
    : availAble(true),
      theEffectTime(effectTime),
      ab(ab) {
}

void AttackBuffSkill::skillPrepare(struct SkillPara sp) {
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
