#ifndef GAME_SKILLCENTER_H_
#define GAME_SKILLCENTER_H_

#include <QString>
#include <QObject>
#include <QGraphicsItem>
#include "enums.h"

class GameMapElement;
class HeroItem;
class EventCenter;


struct SkillPara {
    EventCenter* ec;
    QVariant data;
    QGraphicsItem* from;
    QGraphicsItem* to;
};


class SkillBase : public QObject {
    Q_ENUMS(TriggerTime_t)

 public:
    virtual void skillPrepare(struct SkillPara sp) = 0;
    virtual void skillFlow(struct SkillPara sp) = 0;
    virtual enum TriggerTime_t triggerTime() const = 0;
    virtual bool isAvailable() = 0;
};

class AttackBuffSkill : public SkillBase {
 public:
    AttackBuffSkill(enum AttackBuffEffect a, int effectTime = 1);

    virtual void skillPrepare(struct SkillPara sp);
    void skillFlow(struct SkillPara sp);
    enum TriggerTime_t triggerTime() const;
    virtual bool isAvailable() { return false; }
    virtual void skillAct(struct SkillPara sp) { Q_UNUSED(sp);}

    int effectTime() const { return theEffectTime; }
    enum AttackBuffEffect attackEffect() { return abe; }
    bool skillAvailable() { return true; }

 private:
    bool availAble;
    int theEffectTime;
    enum AttackBuffEffect abe;
};

class RangeSkill : public SkillBase {
 public:
    RangeSkill(enum MapRangeType_t, int range);

    void skillPrepare(struct SkillPara sp);
    void skillFlow(struct SkillPara sp);
    enum TriggerTime_t triggerTime() const { return TriggerInAction; }
    virtual bool isAvailable() { return true; }
    virtual void skillAct(struct SkillPara sp) { Q_UNUSED(sp);}
    virtual void skillRange(struct SkillPara sp);

 private:
    enum MapRangeType_t type;
    int range;
};


class CsMoney : public SkillBase {
 public:
    explicit CsMoney(int coin);
    void skillPrepare(SkillPara sp);
    void skillFlow(SkillPara sp) { Q_UNUSED(sp);}
    bool isAvailable() { return false; }
    enum TriggerTime_t triggerTime() const { return TriggerInAction; }

 private:
    int coin;
};

#endif  // GAME_SKILLCENTER_H_
