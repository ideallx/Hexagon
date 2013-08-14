#ifndef SKILLCENTER_H
#define SKILLCENTER_H

#include <QString>
#include "enums.h"


enum skillType_t
{
    SkillActive,
    SkillPositive,
    SkillPositiveTrigger
};

class skillBase
{
public:
    skillBase();

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
