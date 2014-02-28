#ifndef AI_H
#define AI_H

#include <QList>
#include <QPoint>
#include <QObject>
#include <QThread>
#include <QSemaphore>
#include "enums.h"

class HeroItem;
class HandCard;
class ItemCollector;

class AI : public QThread {
    Q_OBJECT

 public:
    AI(HeroItem* hi, ItemCollector *ic);
    QList<HandCard*> useCard(int n);
    HandCard* useCard(CardNormalPackageType cnpt);
    void dothings(AskType at);
    void thinkNextEvent();

    inline void addFriend(HeroItem* hi) { friendHeros.append(hi); }
    inline void addEnemy(HeroItem* hi) { enemyHeros.append(hi); }
    inline QList<HeroItem*> friends() { return friendHeros; }
    inline QList<HeroItem*> enemys() { return enemyHeros; }
    inline HeroItem* hero() { return AiHero; }

 private:
    HeroItem* findAttackTarget();
    bool isTargetNearAI();
    void run();
    void waitForTime(int msec);
    void processMove();
    void processAttack();

    friend class HeroItem;
    HeroItem* AiHero;
    HeroItem* targetEnemyHero;
    QList<HeroItem*> friendHeros;
    QList<HeroItem*> enemyHeros;
    QSemaphore* sem;
    ItemCollector* ic;

 signals:
    void heroClicked(HeroItem* h);
    void rangeClicked(QPoint p);
    void menuClicked(GameMenuType gmt);
    void buttonOkClicked(QList<HandCard*> l);
    void skillUsed(int n);
    void turnEnd();
};

#endif // AI_H
