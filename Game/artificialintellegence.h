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
    HandCard* useCard(enum Card_Normal_Package_Type_t cnpt);
    QPoint nearestPointToNearestHero();

    void addFriend(HeroItem* hi) { friendHeros.append(hi); }
    void addEnemy(HeroItem* hi) { enemyHeros.append(hi); }
    QList<HeroItem*> friends() { return friendHeros; }
    QList<HeroItem*> enemys() { return enemyHeros; }
    HeroItem* hero() { return AiHero; }

 private:
    friend class HeroItem;
    HeroItem* AiHero;
    QList<HeroItem*> friendHeros;
    QList<HeroItem*> enemyHeros;
};

#endif // ARTIFICIALINTELLEGENCE_H
