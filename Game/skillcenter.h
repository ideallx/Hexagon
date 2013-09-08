#ifndef GAME_SKILLCENTER_H_
#define GAME_SKILLCENTER_H_

#include <QString>
#include "enums.h"

class SkillBase {
 public:
    SkillBase();

    void skillFlow();
    QString skillName() const { return name; }
    enum TriggerTime_t triggerTime() const { return time; }
    void terminateSkill();

 private:
    enum SkillType_t type;
    enum TriggerTime_t time;
    int priority;
    int coolDownTime;
    int curCD;
    QString name;
};

class AttackBuffSkill : public SkillBase {
 public:
    AttackBuffSkill(enum AttackBuffEffect a, int effectTime = 1);

 private:
    int effectTime;
    enum AttackBuffEffect abe;
};

class CardSkill : public SkillBase {
    explicit CardSkill(enum SkillType_t t);
};

#endif  // GAME_SKILLCENTER_H_
