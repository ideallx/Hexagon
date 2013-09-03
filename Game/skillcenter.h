#ifndef SKILLCENTER_H
#define SKILLCENTER_H

#include "enums.h"
#include <QString>


enum skillType_t
{
    SkillActive,
    SkillPositive,
    SkillPositiveTrigger
};

class SkillBase
{
public:
    SkillBase();

    void skillFlow();
    QString skillName() { return name; }
    enum triggerTime_t triggerTime() { return time; }

private:
    enum skillType_t type;
    enum triggerTime_t time;
    int priority;
    int coolDownTime;
    int curCD;
    QString name;
};

#endif // SKILLCENTER_H
