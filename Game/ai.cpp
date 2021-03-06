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
      askForWhat(AskType::AskForMenu) {
    qDebug() << "AI";
}

void AI::askCard(CardNormalPackageType cnpt, int n) {
    resultsCardNum = n;
    resultsCardType = cnpt;
    return;
}

void AI::dothings(AskType at) {
    Q_UNUSED(at);
    qDebug() << "AI do things";
    sem->release();
    askForWhat = at;
}

HeroItem* AI::findAttackTarget() {
    int nearest = 0;
    int distance = 500;
    for (int i = 0; i < enemyHeros.size(); i++) {
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
    sem->acquire();
    if (AiHero->ma->remainingTimes() && !isTargetNearAI()) {
        qDebug() << "AI ready to move";
        processMove();
    } else if (AiHero->aa->remainingTimes() && isTargetNearAI()) {
        qDebug() << "AI ready to attack";
        processAttack();
    } else {
        processTurnEnd();
    }
}

void AI::processTurnEnd() {
    emit turnEnd();
    if (AiHero->cards().size() > AiHero->endTurnMaxCards()) {
        thinkHowToReact();   // How to react turn end
        emit turnEnd();
    }
    qDebug() << "AI Turn End";
}

void AI::processMove() {
    emit menuClicked(GameMenuType::Move);
    sem->acquire();

    QList<QPoint> result =
            ic->pathOnSearch(AiHero->point(), targetEnemyHero->point());

    int msec = 500;
    QPoint targetPoint;
    if (result.size() > AiHero->ma->moveRange() + 1) {
        waitForTime(msec);
        qDebug() << "not attack";
        targetPoint = result[AiHero->ma->moveRange() - 1];
    } else {
        if (!isTargetNearAI()) {
            waitForTime(msec);
            targetPoint = result[result.size() - 2];
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
        findAttackTarget();
        try {
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
        } catch (QString e) {
            qDebug() << e;
        }
        qDebug() << "AI finished an event\n";
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
    sem->acquire();
    qDebug() << "AI Prepare to React";

    switch (askForWhat) {
    case AskType::AskForCards:
        useCard();
        break;
    case AskType::AskForAIReact:    // due to some error, keep the status
        break;
    default:
        qDebug() << "Think Error" << static_cast<int>(askForWhat);
        break;
    }
}

void AI::useCard() {
    waitForTime(500);
    QList<int> result;
    foreach(int hc, AiHero->theCards) {
        if (ic->card(hc)->cardType() == resultsCardType ||
                resultsCardType == CardNormalPackageType::Any) {
            result.append(hc);
            if (result.size() == resultsCardNum) {
                break;
            }
        }
    }
    if (result.size() != resultsCardNum) {
        qDebug() << "AI canceled using card";
        emit buttonCancelClicked();
    } else {
        qDebug() << "AI using card";
        emit buttonOkClicked(result);
    }
}
