#include "attackability.h"

AttackAbility::AttackAbility(int initAttack, int initRange)
    : theAttack(initAttack),
      theRange(initRange),
      theTime(1),
      nextMustHit(0) {
}

void AttackAbility::addBouns(AttackBuff ab) {
    attackBuffs.append(ab);

    if (ab.abe == AttackBuffEffect::AttackBuffAddDamage) {
        setAttack(theAttack + ab.damage);
    } else if (ab.abe == AttackBuffEffect::AttackBuffMustHit) {
        nextMustHit |= ab.probability;  // just as its 100 percent
    } else if (ab.abe == AttackBuffEffect::AttackBuffMoreAttack) {
        theTime += ab.damage;
    }
}

void AttackAbility::removeAttackBouns() {
    foreach(AttackBuff ab, attackBuffs) {
        if (ab.abe == AttackBuffEffect:: AttackBuffAddDamage) {
            setAttack(theAttack - ab.damage);
        } else if (ab.abe == AttackBuffEffect::AttackBuffMustHit) {
            nextMustHit = 0;
        }
    }
    attackBuffs.clear();
    attackTimeMinus();
}

void AttackAbility::attackTimeMinus() {
    if (theTime > 0)
        theTime --;
}
