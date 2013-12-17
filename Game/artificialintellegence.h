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

    void addFriend(HeroItem* hi) { friendHeros.append(hi); }
    void addEnemy(HeroItem* hi) { enemyHeros.append(hi); }
    QList<HeroItem*> friends() { return friendHeros; }
    QList<HeroItem*> enemys() { return enemyHeros; }
    HeroItem* hero() { return AiHero; }

    HeroItem* target() { return targetEnemyHero; }
    void setTarget(HeroItem* hi) { targetEnemyHero = hi; }

 private:
    friend class HeroItem;
    HeroItem* AiHero;
    HeroItem* targetEnemyHero;
    QList<HeroItem*> friendHeros;
    QList<HeroItem*> enemyHeros;
};

#endif // ARTIFICIALINTELLEGENCE_H
