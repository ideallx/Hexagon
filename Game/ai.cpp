#include <QEventLoop>
#include <QDebug>
#include <QTimer>
#include "ai.h"
#include "heroitem.h"
#include "carditem.h"
#include "coordinate.h"
#include "itemcollector.h"


AI::AI(HeroItem *hi, ItemCollector *ic)
    : AiHero (hi),
      targetEnemyHero(NULL),
      sem(new QSemaphore),
      ic(ic) {
    qDebug() << "AI";
}

HandCard* AI::useCard(CardNormalPackageType cnpt) {
    foreach(HandCard* hc, AiHero->cards()) {
        if (hc->cardType() == cnpt)
            return hc;
    }
    return NULL;
}

QList<HandCard*> AI::useCard(int n) {
    if (AiHero->cards().size() <= n) {
        return AiHero->cards();
    } else {
        QList<HandCard*> result;
        while (n != 0) {
            result.append(AiHero->cards()[n-1]);
            n--;
        }
        return result;
    }
}

void AI::dothings(AskType at) {
    qDebug() << "AI moves";
    sem->release();
}

HeroItem* AI::findAttackTarget() {
    int nearest = 0;
    int distance = 500;
    for (int i = 1; i < enemyHeros.size(); i++) {
        int d = GameCoordinate::roughDistance(enemyHeros[i]->point(),
                              AiHero->point());
        if (d < distance) {
            nearest = i;
            distance = d;
        }
    }
    return targetEnemyHero = enemyHeros[nearest];
}

void AI::thinkNextEvent() {
    qDebug() << "wake up AI";
    sem->acquire();
    if (AiHero->isMoveAble()) {
        qDebug() << "AI ready to move";
        processMove();
    } else if (AiHero->isAttackAble() && isTargetNearAI()) {
        qDebug() << "AI ready to attack";
        processAttack();
    } else {
        emit endTurn();
    }
}

void AI::processMove() {
    findAttackTarget();
    emit menuClicked(GameMenuType::Move);
    sem->acquire();

    QList<QPoint> result =
            ic->pathOnSearch(AiHero->point(), targetEnemyHero->point());

    int msec = 500;
    QPoint targetPoint;
    if (result.size() > AiHero->moveRange()+1) {
        waitForTime(msec);
        qDebug() << "not attack";
        targetPoint = result[AiHero->moveRange()-1];
    } else {
        if (!isTargetNearAI()) {
            waitForTime(msec);
            targetPoint = result[AiHero->moveRange()-1];
        } else {
            return;  // your target in your range
        }
    }
    emit rangeClicked(targetPoint);
}

bool AI::isTargetNearAI() {
    return GameCoordinate::roughDistance(
                AiHero->point(), targetEnemyHero->point()) ==
            AiHero->attackRange();
}

void AI::processAttack() {
    int msec = 500;
    waitForTime(msec);
    emit menuClicked(GameMenuType::Attack);
    sem->acquire();

    emit rangeClicked(targetEnemyHero->point());
}

void AI::waitForTime(int msec) {
    QTimer timer;
    QEventLoop l;
    connect(&timer, &QTimer::timeout, &l, &QEventLoop::quit);
    timer.start(msec);
    l.exec();
}

void AI::run() {
    thinkNextEvent();
}
