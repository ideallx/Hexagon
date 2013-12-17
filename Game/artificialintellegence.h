#ifndef ARTIFICIALINTELLEGENCE_H
#define ARTIFICIALINTELLEGENCE_H

#include <QList>
#include <QPoint>
#include "enums.h"

class HeroItem;
class HandCard;

class ArtificialIntellegence {
 public:
    ArtificialIntellegence(HeroItem* hi);
    QList<HandCard*> useCard(int n);
    HandCard* useCard(CardNormalPackageType cnpt);
    QPoint nearestPointToNearestHero();

    inline void addFriend(HeroItem* hi) { friendHeros.append(hi); }
    inline void addEnemy(HeroItem* hi) { enemyHeros.append(hi); }
    inline QList<HeroItem*> friends() { return friendHeros; }
    inline QList<HeroItem*> enemys() { return enemyHeros; }
    inline HeroItem* hero() { return AiHero; }

    inline HeroItem* target() { return targetEnemyHero; }
    inline void setTarget(HeroItem* hi) { targetEnemyHero = hi; }

 private:
    friend class HeroItem;
    HeroItem* AiHero;
    HeroItem* targetEnemyHero;
    QList<HeroItem*> friendHeros;
    QList<HeroItem*> enemyHeros;
};

#endif // ARTIFICIALINTELLEGENCE_H
