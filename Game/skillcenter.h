#ifndef GAME_SKILLCENTER_H_
#define GAME_SKILLCENTER_H_

#include <QString>
#include <QObject>
#include "enums.h"
class HeroItem;

class SkillBase : public QObject {
    Q_ENUMS(TriggerTime_t)

 public:
    virtual void skillFlow(HeroItem* from, HeroItem* to) = 0;
    virtual void terminateSkill() = 0;
    virtual enum TriggerTime_t triggerTime() const = 0;
    virtual bool isAvailable() = 0;
};

class AttackBuffSkill : public SkillBase {
 public:
    AttackBuffSkill(enum AttackBuffEffect a, int effectTime = 1);

    void skillFlow(HeroItem* from, HeroItem* to);
    void terminateSkill();
    enum TriggerTime_t triggerTime() const;
    virtual bool isAvailable() { return availAble; }

    virtual void skillAct(HeroItem* from, HeroItem* to);

    int effectTime() const { return theEffectTime; }
    enum AttackBuffEffect attackEffect() { return abe; }
    bool skillAvailable() { return true; }

 private:
    bool availAble;
    int theEffectTime;
    enum AttackBuffEffect abe;
};
#endif  // GAME_SKILLCENTER_H_
