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
    void askCard(CardNormalPackageType cnpt, int n);
    void dothings(AskType at);
    void thinkHowToReact();
    void thinkNextEvent();
    void aisTurn();
    void aisReact();

    inline void addFriend(HeroItem* hi) { friendHeros.append(hi); }
    inline void addEnemy(HeroItem* hi) { enemyHeros.append(hi); }
    inline QList<HeroItem*> friends() { return friendHeros; }
    inline QList<HeroItem*> enemys() { return enemyHeros; }
    inline HeroItem* hero() { return AiHero; }

 private:
    void useCard();
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
    AskType askForWhat;


    int resultsCardNum;
    CardNormalPackageType resultsCardType;
    // TODO


 signals:
    void heroClicked(HeroItem* h);
    void rangeClicked(QPoint p);
    void menuClicked(GameMenuType gmt);
    void buttonOkClicked(QList<HandCard*> l);
    void buttonCancelClicked();
    void skillUsed(int n);
    void turnEnd();
};

#endif // AI_H
