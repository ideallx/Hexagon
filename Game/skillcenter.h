#ifndef SKILLCENTER_H
#define SKILLCENTER_H

#include <QString>

enum mapRangeType_t
{
    dfa,
    sdf
};

enum skillType_t
{
    SkillActive,
    SkillPositive,
    SkillPositiveTrigger
};

enum triggerTime_t
{
    TriggerGameBegin,
    TriggerRoundBegin,
    TriggerTurnBegin,
    TriggerMoveBegin,
    TriggerMoveEnd,
    TriggerAttackBegin,
    TriggerAttackEnd,
    TriggerOtherSkillBegin,
    TriggerOtherSkillEnd,
    TriggerTurnEnd,
    TriggerRoundEnd,
    TriggerGameEnd
};


class skillBase
{
public:
    skillBase();

    void skillFlow();
    QString skillName() { return name; }

private:
    enum skillType_t type;
    enum triggerTime_t time;
    int priority;
    int coolDownTime;
    int curCD;
    QString name;
};

#endif // SKILLCENTER_H
