#ifndef GAME_SKILLCENTER_H_
#define GAME_SKILLCENTER_H_

#include <QString>
#include <QObject>
#include <QGraphicsItem>
#include "enums.h"

class GameMapElement;
class HeroItem;
class EventCenter;
class MapMark;

class SkillPara {
 public:
    SkillPara(EventCenter *ec, QVariant data,
              QGraphicsItem* from, QGraphicsItem* to)
        : ec(ec) ,
          data(data),
          from(from),
          to(to) {
    }

    EventCenter* ec;
    QVariant data;
    QGraphicsItem* from;
    QGraphicsItem* to;
};


class SkillBase : public QObject {
    Q_ENUMS(TriggerTime)

 public:
    SkillBase(int cdf = 0, int cdmaxf = 0, DamageType dt = DamageType::Physical)
        : cooldown(cdf),
          cooldownMax(cdmaxf),
          dt(dt) {;}
    virtual void skillPrepare(SkillPara sp) = 0;
    virtual void skillFlow(SkillPara sp) = 0;
    virtual TriggerTime triggerTime() const = 0;
    virtual bool isWorkNow() = 0;
    virtual int cdMax() { return cooldownMax; }
    virtual int cdNow() { return cooldown; }
    void addCoolDown(int n);
    virtual SkillType type() { return SkillType::SkillActive; }
    inline DamageType damType() { return dt; }

 private:
    int cooldown;
    int cooldownMax;
    DamageType dt;
};

class AttackBuffSkill : public SkillBase {
 public:
    AttackBuffSkill(AttackBuffEffect abe, int stateType, int probability,
                    int cd = 0, int cdmax = 0, int duration = 1);

    void skillPrepare(SkillPara sp);
    void skillFlow(SkillPara sp);
    virtual TriggerTime triggerTime() const;

    virtual bool isWorkNow() { return availAble; }
    virtual void skillAct(SkillPara sp) { Q_UNUSED(sp);}
    virtual void skillClicked(SkillPara sp) { Q_UNUSED(sp);}
    virtual AttackBuff buffEffect();

    int effectTime() const { return theEffectTime; }
    AttackBuffEffect attackEffect() { return ab.abe; }
    bool skillAvailable() { return true; }

 private:
    AttackBuff ab;
    bool availAble;
    int theEffectTime;
};

class RangeSkill : public SkillBase {
 public:
    RangeSkill(MapRangeType, int range,
               int cd = 0, int cdmax = 0);

    void skillPrepare(SkillPara sp);
    void skillFlow(SkillPara sp);
    TriggerTime triggerTime() const { return TriggerTime::InAction; }
    virtual bool isWorkNow() { return true; }

    virtual void skillAct(SkillPara sp) { Q_UNUSED(sp);}
    virtual void skillRange(SkillPara sp);

 private:
    MapRangeType type;
    int range;
};

class SufferSkill : public SkillBase {
 public:
    SufferSkill(SufferType t, int floor,
                int cd = 0, int cdmax = 0);
};


class CsMoney : public SkillBase {
 public:
    explicit CsMoney(int coin, int cd = 0, int cdmax = 0);
    void skillPrepare(SkillPara sp);
    void skillFlow(SkillPara sp) { Q_UNUSED(sp);}
    bool isWorkNow() { return false; }
    TriggerTime triggerTime() const { return TriggerTime::InAction; }

 private:
    int coin;
};

class MapMarkSkill : public SkillBase {
 public:
    MapMarkSkill(MapMark* mark, int range, int cd = 0, int cdmax = 0);

    void skillPrepare(SkillPara sp);
    void skillFlow(SkillPara sp);
    TriggerTime triggerTime() const { return TriggerTime::InAction; }
    virtual bool isWorkNow() { return true; }

    virtual void skillAct(SkillPara sp);
    virtual void skillRange(SkillPara sp);

 private:
    MapMark* mark;
    int range;
};

#endif  // GAME_SKILLCENTER_H_
