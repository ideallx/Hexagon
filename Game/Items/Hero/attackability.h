#ifndef ATTACKABILITY_H
#define ATTACKABILITY_H

#include <QList>
#include "enums.h"

class AttackAbility {
 public:
    AttackAbility(int initAttack = 1, int initRange = 1);

    inline int attack() const { return theAttack; }
    inline void setAttack(int i) { theAttack = i; }

    inline int attackRange() const { return theRange; }
    inline void setRange(int i) { theRange = i; }

    void addBouns(AttackBuff ab);
    void removeAttackBouns();
    inline void restore() { theTime = 1;}
    inline int remainingTimes() { return theTime; }
    inline int mustHitRate() { return nextMustHit; }
    void attackTimeMinus();

 private:
    QList<AttackBuff> attackBuffs;          // special effects on attack
    int theAttack;                          // attack damage
    int theRange;                           // attack range
    int theTime;                            // remaining attack time
    int nextMustHit;
};

#endif // ATTACKABILITY_H
