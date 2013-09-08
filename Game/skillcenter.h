#ifndef GAME_SKILLCENTER_H_
#define GAME_SKILLCENTER_H_

#include <QString>
#include <QObject>
#include "enums.h"

class SkillBase : public QObject {
 public:
    void skillFlow();
    virtual QString skillName() const = 0;
    virtual enum TriggerTime_t triggerTime() const = 0;
    void terminateSkill();

// private:
//    enum SkillType_t type;
//    enum TriggerTime_t time;
//    int priority;
//    int coolDownTime;
//    int curCD;
//    QString name;
};

class AttackBuffSkill : public SkillBase {
 public:
    AttackBuffSkill(enum AttackBuffEffect a, int effectTime = 1);
    enum TriggerTime_t triggerTime() const { return TriggerAttackBegin; }
    QString skillName() const { return objectName(); }
    int effectTime() const { return theEffectTime; }
    enum AttackBuffEffect attackEffect() { return abe; }
    void skillFlow();

 private:
    int theEffectTime;
    enum AttackBuffEffect abe;
};

class CardSkill : public SkillBase {
    explicit CardSkill(enum SkillType_t t);
};

#endif  // GAME_SKILLCENTER_H_
