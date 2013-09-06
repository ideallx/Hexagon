#ifndef GAME_SKILLCENTER_H_
#define GAME_SKILLCENTER_H_

#include <QString>
#include "enums.h"

enum skillType_t {
    SkillActive,
    SkillPositive,
    SkillPositiveTrigger
};

class SkillBase {
 public:
    SkillBase();

    void skillFlow();
    QString skillName() const { return name; }
    enum triggerTime_t triggerTime() const { return time; }

 private:
    enum skillType_t type;
    enum triggerTime_t time;
    int priority;
    int coolDownTime;
    int curCD;
    QString name;
};

#endif  // GAME_SKILLCENTER_H_
