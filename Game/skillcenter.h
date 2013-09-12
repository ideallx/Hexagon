#ifndef GAME_SKILLCENTER_H_
#define GAME_SKILLCENTER_H_

#include <QString>
#include <QObject>
#include <QGraphicsItem>
#include "enums.h"

class GameMapElement;
class HeroItem;
class EventCenter;

class SkillBase : public QObject {
    Q_ENUMS(TriggerTime_t)

 public:
    virtual void skillFlow(EventCenter* ec, QVariant &data,
                           QGraphicsItem* from, QGraphicsItem* to) = 0;
    virtual enum TriggerTime_t triggerTime() const = 0;
    virtual bool isAvailable() = 0;
};

class AttackBuffSkill : public SkillBase {
 public:
    AttackBuffSkill(enum AttackBuffEffect a, int effectTime = 1);

    void skillFlow(EventCenter* ec, QVariant &data,
                   QGraphicsItem* from, QGraphicsItem* to);
    enum TriggerTime_t triggerTime() const;
    virtual bool isAvailable() { return availAble; }
    virtual void skillAct(EventCenter* ec, QVariant &data,
                          QGraphicsItem* from, QGraphicsItem* to);

    int effectTime() const { return theEffectTime; }
    enum AttackBuffEffect attackEffect() { return abe; }
    bool skillAvailable() { return true; }

 private:
    bool availAble;
    int theEffectTime;
    enum AttackBuffEffect abe;
};

class ShiftSkill : public SkillBase {
 public:
    ShiftSkill(enum MapRangeType_t, int range);

    void skillFlow(EventCenter* ec, QVariant &data,
                   QGraphicsItem* from, QGraphicsItem* to);
    enum TriggerTime_t triggerTime() const { return TriggerInAction; }
    virtual bool isAvailable() { return true; }
    virtual void chooseRangePoint(GameMapElement* gme) {;}

 private:
    enum MapRangeType_t type;
    int range;
};

#endif  // GAME_SKILLCENTER_H_
