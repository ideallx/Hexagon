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
      ic(ic),
      askForWhat(AskType::AskForNone) {
    qDebug() << "AI";
}

QList<HandCard*> AI::useCard(CardNormalPackageType cnpt) {
    QList<HandCard*> result;
    foreach(HandCard* hc, AiHero->cards()) {
        if (hc->cardType() == cnpt) {
            result.append(hc);
            break;
        }
    }
    if (result.size() == 0) {
        emit buttonCancelClicked();
        qDebug() << "AI use single card";
    } else {
        emit buttonOkClicked(result);
        qDebug() << "AI not use single card";
    }
    return result;
}

QList<HandCard*> AI::useCards(int n) {
    QList<HandCard*> result;
    if (AiHero->cards().size() <= n) {
        result = AiHero->cards();
    } else {
        QList<HandCard*> result;
        while (n != 0) {
            result.append(AiHero->cards()[n-1]);
            n--;
        }
        result = result;
    }
    emit buttonOkClicked(result);

    askForWhat = AskType::AskForAIReact;
    sem->acquire();
    return result;
}

void AI::dothings(AskType at) {
    Q_UNUSED(at);
    qDebug() << "AI do things";
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
    if (AiHero->ma->remainingTimes()) {
        qDebug() << "AI ready to move";
        processMove();
    } else if (AiHero->aa->remainingTimes() && isTargetNearAI()) {
        qDebug() << "AI ready to attack";
        processAttack();
    } else {
        emit turnEnd();
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
    if (result.size() > AiHero->ma->moveRange()+1) {
        waitForTime(msec);
        qDebug() << "not attack";
        targetPoint = result[AiHero->ma->moveRange()-1];
    } else {
        if (!isTargetNearAI()) {
            waitForTime(msec);
            targetPoint = result[AiHero->ma->moveRange()-1];
        } else {
            return;  // your target in your range
        }
    }
    emit rangeClicked(targetPoint);
}

bool AI::isTargetNearAI() {
    return GameCoordinate::roughDistance(
                AiHero->point(), targetEnemyHero->point()) <=
            AiHero->aa->attackRange();
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
    while (true) {
        sem->acquire();
        switch (askForWhat) {
        case AskType::AskForAITurn:
            thinkNextEvent();
            break;
        case AskType::AskForAIReact:
            thinkHowToReact();
            break;
        default:
            continue;
        }
        qDebug() << "AI finished an event";
    }
}


void AI::aisTurn() {
    askForWhat = AskType::AskForAITurn;
    sem->release();
}

void AI::aisReact() {
    askForWhat = AskType::AskForAIReact;
    sem->release();
}

void AI::thinkHowToReact() {
    qDebug() << "wake up AI";
    sem->acquire();

    switch (askForWhat) {
    case AskType::AskForCards:
        break;

    }
}
