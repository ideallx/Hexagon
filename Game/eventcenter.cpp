#include <QMessageBox>
#include <QTimer>
#include "eventcenter.h"
#include "heroitem.h"
#include "itemcollector.h"
#include "backscene.h"
#include "menu.h"
#include "backview.h"
#include "coordinate.h"
#include "mapelement.h"
#include "carditem.h"
#include "cardengine.h"
#include "skillcenter.h"
#include "artificialintellegence.h"
#include "normalpackage.h"

#define GIVEN_CONDITION

EventCenter::EventCenter(BackScene* scene, GameMenu* menu, QWidget* parent)
    : scene(scene),
      menu(menu),
      ic(scene->pIc()),
      gameBegined(false),
      parent(parent),
      isAnimating (false),
      sem(new QSemaphore),
      askType(AskType::AskForNone) {
    setupConnection();
    theGia = new QGraphicsItemAnimation();
    roundNum = 1;
    playerHeroNum = ic->playSeq();
    qDebug() << "event center initialized";
}

void EventCenter::setupConnection() {
    connect(scene, SIGNAL(heroClicked(HeroItem*)),
            this, SLOT(heroChosen(HeroItem*)));
    connect(scene, SIGNAL(rangeClicked(QPoint)),
            this, SLOT(targetClicked(QPoint)));
    connect(scene, SIGNAL(buildMenu(HeroItem*, QPoint)),
            this, SLOT(showMenu(HeroItem*, QPoint)));
    connect(scene, SIGNAL(viewSizeChanged(QSize)),
            menu, SLOT(reSetInterface(QSize)));
    connect(scene, SIGNAL(mapElementClicked(QPoint)),
            this, SLOT(mapElementChosen(QPoint)));

//    connect(menu, SIGNAL(moveClicked()), this, SLOT(moveBegin()));
//    connect(menu, SIGNAL(attackClicked()), this, SLOT(attackBegin()));
//    connect(menu, SIGNAL(skillButtonClicked()), this, SLOT(skillBegin()));
    connect(menu, &GameMenu::menuClicked,
            this, &EventCenter::menuClickAct);

    connect(menu, SIGNAL(buttonOkClicked(QList<HandCard*>)),
            this, SLOT(cardChosen(QList<HandCard*>)));
    connect(menu, &GameMenu::buttonCancelClicked,
            this, &EventCenter::cardCancel);
    connect(menu, &GameMenu::skillUsed,
            this, &EventCenter::heroUseSkill);
    connect(menu, &GameMenu::cancelClicked,
            scene, &BackScene::clearRange);
    connect(this, &EventCenter::endTurnLater,
            this, &EventCenter::endTurn, Qt::QueuedConnection);
    connect(this, &EventCenter::changeHeroInfo,
            menu, &GameMenu::setHeroInfo);
}

void EventCenter::gameBegin() {
    heroSeq = ic->getActSequence();
#ifdef GIVEN_CONDITION
    curHero = heroSeq[0];
    curHero->addHeroSkill(new HsGuiShou());
    curHero->addHeroSkill(new HsQianXing());
    curHero->addHeroSkill(new HsLengXue());
    curHero->setPoint(QPoint(0, 12));

    curHero = heroSeq[1];
    ArtificialIntellegence* AI = new ArtificialIntellegence(curHero);
    curHero->setAI(AI);
    curHero->setPoint(QPoint(4, 1));

    curHero = heroSeq[2];
    AI = new ArtificialIntellegence(curHero);
    curHero->setAI(AI);
    curHero->setPoint(QPoint(0, 14));

    curHero = heroSeq[3];
    AI = new ArtificialIntellegence(curHero);
    curHero->setAI(AI);
    curHero->setPoint(QPoint(4, 0));

    for (int i = 0; i < heroSeq.size(); i++) {
        ArtificialIntellegence* ai = heroSeq[i]->AI();
        if (ai != NULL) {
            if (i % 2) {
                for (int j = 0; j < heroSeq.size(); j+=2) {
                    ai->addEnemy(heroSeq[j]);
                    ai->addFriend(heroSeq[j+1]);
                }
            } else {
                for (int j = 1; j < heroSeq.size(); j+=2) {
                    ai->addEnemy(heroSeq[j]);
                    ai->addFriend(heroSeq[j-1]);
                }
            }
        }
    }

    curHero = heroSeq[0];
    setCurHero(curHero);
#else
    for (int i = 0; i < heroSeq.size(); i++) {
        curHero = heroSeq[i];
        menu->setPrompt(tr("Choose Birth For Hero: %1").
                        arg(curHero->heroName()));
        QList<QPoint> l;
        scene->showBirthSquare(curHero->camp(), l);
        QPoint birth = askForSelectPoint();
        scene->clearRange();
        curHero->setPoint(birth);
    }

#endif

    scene->clearRange();
    try {
        checkHeros();
    } catch(const QString& e) {
        QMessageBox::warning(NULL, tr("LYBNS"), e);
        return;
    }

    gameBegined = true;
    curHero = heroSeq[0];
    menu->setPrompt(tr("Game Begin"));
}


/**
 * @brief EventCenter::heroChosen
 * @param hero
 * change parameter to QPoint later
 */
void EventCenter::heroChosen(HeroItem* hero) {
    if (sem->available()) {
        menu->setHeroInfo(hero);
        showCards(hero);
        return;
    } else {
        resultsPoint = hero->point();
        sem->release();
        return;
    }
}

void EventCenter::showCards(HeroItem* hero) {
//    if (heroSeq.indexOf(hero) == playerHeroNum) {
//        menu->updateCardsArea(hero->cards());
//    } else {
//        menu->updateCardsArea(ic->switchToBack(hero->cards()));
//    }
    menu->updateCardsArea(hero->cards());
}

void EventCenter::getCard(int num) {
    if (!gameBegined)
        return;
    qDebug() << curHero->heroName() << "get" << num << "cards";
    curHero->addCards(ic->getCard(num));
    showCards(curHero);
    menu->hideAllMenu();
}


void EventCenter::heroMoveToPoint(QPoint in) {
    if (!ic->isPointAvailable(in))
        return;

    scene->clearRange();
    GameMapElement* gme = ic->getMapElementByPoint(in);
    moveAnimate(curHero, gme);

    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);

    curHero->setPoint(in);

    qDebug() << curHero->heroName() <<
                "Move To Point" << curHero->point();
}

void EventCenter::heroAttackPoint(QPoint in) {
    if (!ic->isPointAvailable(in))
        return;

    scene->clearRange();
    targetHero = ic->getHeroByPoint(in);

    int hitRate = curHero->getMustHitRate();
    bool isHit = dodge(hitRate);

    if (!isHit) {
        curHero->removeAttackBouns();
        if (curHero->AI() != NULL) {
            emit endTurnLater();   // TODO(ideallx) jugg by AI after skills complete
        }
        qDebug() << targetHero->heroName() <<
                    "Dodged The Attack From" << curHero->heroName();
        return;
    }

    // if hit
    QList<SkillBase*> l = curHero->hasSkillTriggerAt(TriggerTime::TriggerAttackHit);
    if (l.size() != 0) {
        for (int i = 0; i < l.size(); i++) {
//                if (!l[i]->isWorkNow()) {   // TODO(ideallx) to fix
//                    l.removeAt(i);
//                } else {
                QVariant data;
                struct SkillPara sp;
                sp.ec = this;
                sp.data = data;
                sp.from = curHero;
                sp.to = targetHero;
                l[i]->skillFlow(sp);
                curSkill = l[i];
                listHeroInfo(curHero);
//                }
        }
    }

    attackAnimate(curHero, targetHero);
    attackCalc(curHero, targetHero);
    curHero->removeAttackBouns();
    qDebug() << curHero->heroName() <<
                "Attack" << targetHero->heroName() <<
                "And Made" << curHero->attack() << "Damage";

    if (curHero->AI() != NULL) {
        emit endTurnLater();   // TODO(ideallx) jugg by AI after skills complete
    }
    return;
}

/**
 * @brief EventCenter::dodge
 * @param hitRate
 * @return true  targetHero get Hit
 *         false targetHero doged the attack successfully
 */
bool EventCenter::dodge(int hitRate) {
    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);
    if (!curHero->isAttackAble()) {
        menu->setAttackAble(false);
    }

    if (hitRate == 0x3F) {
        return true;
    } else if (hitRate == 0){
        return !askForUseCard(targetHero, CardNormalPackageType::ShanBi);
    } else {
        if ((1 << (rollTheDice(1)[0]-1)) & hitRate) {
            return true;
        } else {
            return !askForUseCard(targetHero, CardNormalPackageType::ShanBi);
        }
    }

}

void EventCenter::skillStraightTest(QPoint in) {
    GameMapElement* gme = ic->getMapElementByPoint(in);

    struct SkillPara sp;
    sp.data = QVariant();
    sp.from = curHero;
    sp.to = gme;
    sp.ec = this;

    skillAnimate(curHero, gme);
    curSkill->skillFlow(sp);

    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);
    menu->setSkillAble(false);
}

void EventCenter::targetClicked(QPoint in) {
    if (isAnimating)
        return;

    if (askType == AskType::AskForPoint) {
        resultsPoint = in;
        sem->release();
        return;
    }
}

void EventCenter::mapClear() {
    scene->clearRange();
    menu->hideAllMenu();
}

void EventCenter::beginTurn() {
    menu->setPrompt("");
    qDebug() << curHero->heroName() + "'s" << "Turn Begin";

    getCard(HeroItem::beginTurnGetCards());
    setCurHero(curHero);
    curHero->beginTurnSettle();
    emit roundInfoChanged(buildRoundInfo());

    if (curHero->AI() == NULL) {
        sem->acquire();
        return;
    }
    /*
    ArtificialIntellegence* curAI = curHero->AI();
    moveBegin();
    int nearest = 0;
    int distance = GameCoordinate::roughDistance(
                curAI->enemys()[0]->point(), curAI->hero()->point());
    for (int i = 1; i < curAI->enemys().size(); i++) {
        int d = roughDistance(curAI->hero(), curAI->enemys()[i]);
        if (d < distance) {
            nearest = i;
            distance = d;
        }
    }
    curAI->setTarget(curAI->enemys()[nearest]);
    QPoint targetPoint = curAI->target()->point();
    QList<QPoint> result = ic->pathOnSearch(curHero->point(),
                                            targetPoint);
    int msec = 500;
    if (result.size() > curHero->moveRange()+1) {
        waitForTime(msec);
        heroMoveToPoint(result[curHero->moveRange()-1]);
        qDebug() << "not attack";
    } else {
        if (GameCoordinate::roughDistance(curHero->point(), targetPoint) != 1) {
            waitForTime(msec);
            heroMoveToPoint(result[result.size()-2]);
        }
        waitForTime(msec);
        heroAttackPoint(targetPoint);
        if (curAI->target()->AI() == NULL)
            return;
    }
    emit endTurnLater();
    */
}

void EventCenter::waitForTime(int msec) {
    QTimer timer;
    QEventLoop l;
    connect(&timer, &QTimer::timeout, &l, &QEventLoop::quit);
    timer.start(msec);
    l.exec();
}

void EventCenter::endTurn() {
    if (!gameBegined)
        return;

    listHeroInfo(curHero);
    if (curHero->cards().size() > HeroItem::endTurnMaxCards()) {
        QList<HandCard*> result = askForNCard(curHero, curHero->cards().size() -
                                              HeroItem::endTurnMaxCards());
        foreach (HandCard* hc, result) {
            curHero->removeCard(hc);
        }

        if (curHero->AI() == NULL) {
            return;
        }
    }

    if (curHero->AI() != NULL)
        waitForTime(1000);

    curHero->removeAttackBouns();
    qDebug() << curHero->heroName() + "'s" << "Turn End\n";

    curHero->setPen(QPen(Qt::black, 3));

    if (curHero == heroSeq.last()) {
        roundEnd();
        roundNum++;
        roundBegin();
    } else {
        curHero = heroSeq[heroSeq.indexOf(curHero)+1];
    }

    menu->beginTurnReset();
    beginTurn();
}

void EventCenter::roundBegin() {
    // ic->herosLoadPassiveSkill();
    // ic->mapElementAward();
    qDebug() << "Round" << roundNum << "Begin";
    curHero = heroSeq[0];
    scene->views()[0]->centerOn(curHero->pos());
}

void EventCenter::roundEnd() {
    qDebug() << "Round" << roundNum << "End\n";
    foreach(HeroItem* hi, heroSeq) {
        hi->endRoundSettle();
    }
}


QStringList EventCenter::buildRoundInfo() {
    QStringList qsl;
    QString qs;
    qs = "Camp Turn: ";
    if (curHero->camp() == Camp::CampRed)
        qs += "Red Team";
    else
        qs += "Blue Team";
    qsl.append(qs);
    qs = "Hero Turn: " + curHero->heroName();
    qsl.append(qs);
    qs = "Round Number: " + QString::number(roundNum);
    qsl.append(qs);
    return qsl;
}

void EventCenter::showMenu(HeroItem* hi, QPoint p) {
    if (isAnimating)
        return;

    if (curHero == hi) {
        menu->showMenu(p);
    }
}

void EventCenter::setCurHero(HeroItem* hi) {
    curHero = hi;
    curHero->setPen(QPen(Qt::darkMagenta, 3));
    listHeroInfo(curHero);
}

void EventCenter::listHeroInfo(HeroItem* hi) {
    emit changeHeroInfo(hi);
    scene->views()[0]->centerOn(hi);
    showCards(hi);
}

void EventCenter::moveAnimate(HeroItem* srcItem, GameMapElement* targetItem) {
    theGia->clear();
    theGia->setItem(srcItem);

    QTimeLine* moveTimer = new QTimeLine(500);
    // set time line will delete previous qtimeline
    theGia->setTimeLine(moveTimer);

    double frame = 12;

    QPointF src = ic->getBeginPosOfHero(srcItem->point());
    QPointF dst = ic->getBeginPosOfHero(targetItem->point());

    QPointF distance = dst - src;
    qDebug() << "move from" << srcItem->point() <<
                "to" << targetItem->point() << distance;

    isAnimating = true;
    for (int i = 0; i <= frame; ++i)
        theGia->setPosAt(i/frame, srcItem->scenePos()+distance*i/frame);
    moveTimer->start();
    waitForTime(moveTimer->duration());
    isAnimating = false;
}

void EventCenter::attackAnimate(HeroItem* srcItem, HeroItem* targetItem) {
    theGia->clear();
    theGia->setItem(srcItem);
    QTimeLine* attackTimer = new QTimeLine(250);
    theGia->setTimeLine(attackTimer);

    double frame = attackTimer->duration()/attackTimer->updateInterval();

    QPointF src = ic->getBeginPosOfHero(srcItem->point());
    QPointF dst = ic->getBeginPosOfHero(targetItem->point());
    QPointF distance = dst - src;

    qDebug() << "attack from" << srcItem->point() <<
                "to" << targetItem->point() << distance;
    for (int i = 0; i <= frame/2; ++i) {
        theGia->setPosAt(i/frame, src+distance*i/frame);
    }

    for (int i = 0; i <= frame/2; ++i) {
        theGia->setPosAt(i/frame+0.5, src+distance/2-distance*i/frame);
    }

    isAnimating = true;
    attackTimer->start();
    waitForTime(attackTimer->duration());
    isAnimating = false;
}

void EventCenter::attackCalc(HeroItem *from, HeroItem *to) {
    QList<SkillBase*> l = from->hasSkillTriggerAt(TriggerTime::TriggerAttackBegin);
    to->addHealth(- from->attack());
    if (l.size() != 0) {
        for (int i = 0; i < l.size(); i++) {
            if (!l[i]->isWorkNow()) {   // TODO(ideallx) to fix
                l.removeAt(i);
            } else {
                QVariant data;
                struct SkillPara sp;
                sp.ec = this;
                sp.data = data;
                sp.from = from;
                sp.to = to;
                l[i]->skillPrepare(sp);
                curSkill = l[i];
                listHeroInfo(curHero);
            }
        }
    }
}

void EventCenter::skillAnimate(HeroItem* srcItem, GameMapElement* targetItem) {
    QList<QGraphicsLineItem*> targetLines = ic->getLines();
    theGia->clear();
    theGia->setItem(targetLines[0]);
    QTimeLine* targetTimer = new QTimeLine(1000);
    theGia->setTimeLine(targetTimer);

    QPointF src = ic->getCenterPosWithCoo(srcItem->point());
    QPointF dst = ic->getCenterPosWithCoo(targetItem->point());
    QPointF distance = dst - src;

    double frame = targetTimer->duration()/targetTimer->updateInterval();

    targetLines[0]->setLine(0, 0, distance.x(), distance.y());
    targetLines[0]->setPos(5000, 5000);  // make it untouchable
    targetLines[0]->show();

    // TODO(ideallx) skill
    for (int i = 0; i <= frame/2; ++i) {
        theGia->setScaleAt(i/frame, 2*i/frame, 2*i/frame);
        theGia->setPosAt(i/frame, src);
    }

    for (int i = 0; i <= frame/2; ++i) {
        theGia->setPosAt(i/frame+0.5, src+distance*2*i/frame);
        theGia->setScaleAt(i/frame+0.5, 1-2*i/frame, 1-2*i/frame);
    }

    targetTimer->start();
}

void EventCenter::setHeroPosition(HeroItem* hi, QPoint pos) {
    hi->setPoint(pos);
    hi->setPos(ic->getBeginPosOfHero(pos));
}

void EventCenter::checkHeros() {
    for (int i = 0; i < heroSeq.size(); i++) {
        if (heroSeq[i]->point() == QPoint(300, 300)) {
            throw QString(tr("Hero %1: Wrong Birth Point").
                          arg(heroSeq[i]->heroName()));
        }
    }
}

bool EventCenter::askForUseCard(HeroItem* hi,
                                CardNormalPackageType t) {
    askCard.useCardHero = hi;
    askCard.useCardType = t;
    menu->setPrompt(QString("Please Use Card:"));
    menu->setOneCardMode(true);

    ArtificialIntellegence* ai = hi->AI();
    if (ai == NULL) {
        menu->setHeroInfo(hi);
        showCards(hi);
        sem->acquire();
// TODO  resultsCard juggment
        hi->removeCard(resultsCard[0]);
        return (resultsCard.size() == 1);
    }

    HandCard* hc = ai->useCard(t);
    if (hc) {
        hi->removeCard(hc);
        menu->updateCardsArea(curHero->cards());
        return true;
    } else {
        return false;
    }
}

QList<HandCard*> EventCenter::askForNCard(HeroItem* hi, int n) {
    askCard.useCardHero = hi;
    askCard.n = n;
    menu->setPrompt(QString("Please Use Card:"));
    menu->setOneCardMode(false);

    ArtificialIntellegence* ai = curHero->AI();
    if (ai == NULL) {
        askType = AskType::AskForCards;
        sem->acquire();
        return resultsCard;
    }

    return ai->useCard(n);
//    if (hcl.size() == n) {
//        foreach(HandCard* hc, hcl)
//            hi->removeCard(hc);
//        menu->updateCardsArea(curHero->cards());
//        return true;
//    } else {
//        (this->*waitingEvent)(false);
//        return false;
//    }
}

QList<HandCard*> EventCenter::discardCard(HeroItem* hi, int num) {
    QList<HandCard*> cards = hi->cards();
    QList<HandCard*> result;
    if (cards.size() < num) {
        foreach(HandCard* hc, cards) {
            if (!hi->removeCard(hc))
                qDebug() << "Discard Cards Error";
            else
                result.append(hc);
        }
    } else {
        for (int i = 0; i < num; i++) {
            QList<HandCard*> cards = hi->cards();
            HandCard* hc = cards.at(rand()/cards.size());
            if (!hi->removeCard(hc))
                qDebug() << "Discard Cards Error";
            else
                result.append(hc);
        }
    }
    return result;
}

void EventCenter::mapElementChosen(QPoint p) {
    Q_UNUSED(p);
    menu->hideAllMenu();
}

void EventCenter::cardChosen(QList<HandCard*> l) {
    if (isAnimating)
        return;
    if (l.size() == 0)
        return;

    if (askType == AskType::AskForCards) {
        resultsCard.clear();
        resultsCard += l;
        sem->release();
        return;
    }
/*
    switch (curPhase) {
    case GamePhase::DiscardPhase:
        if (curHero != menu->panelHero()) {
            return;
        }
        for (int i = 0; i < l.size(); i++) {
            ic->returnCard(l);
            if (!curHero->removeCard(l[i]))
                qDebug() << "discard card error";
        }
        qDebug() << "cards num:" << curHero->cards().size();
        menu->updateCardsArea(curHero->cards());
        curPhase = GamePhase::FinalPhase;
        emit endTurnLater();
        break;
    case GamePhase::BeginPhase:
        if (curHero != menu->panelHero()) {
            return;
        }
        if (l.size() == 1) {
            QVariant data;
            struct SkillPara sp;
            sp.ec = this;
            sp.data = data;
            sp.from = curHero;
            sp.to = NULL;
            if (l[0]->skill() != 0) {
                if (l[0]->skill()->isWorkNow())
                    curSkill = l[0]->skill();
                curHero->removeCard(l[0]);
                l[0]->skill()->skillPrepare(sp);
                listHeroInfo(curHero);
            }
        }
        break;
    case GamePhase::AskForCardPhase:
        if (askCard.useCardHero != menu->panelHero()) {
            return;
        }
        if ((l.size() == 1) &&
                (l[0]->cardType() == askCard.useCardType)) {
            askCard.useCardHero->removeCard(l[0]);
            menu->updateCardsArea(askCard.useCardHero->cards());
            if (waitingEvent)
                (this->*waitingEvent)(true);
        }
        break;
    case GamePhase::AskForNCards:
        if (askCard.useCardHero != menu->panelHero()) {
            return;
        }
        if (l.size() == askCard.n) {
            if (waitingEvent)
                (this->*waitingEvent)(true);
        }
        break;
    default:
        break;
    }
    */
}

void EventCenter::cardCancel() {
    if (isAnimating)
        return;
}

void EventCenter::openShop() {
    ChooseMenu cm(parent);
    cm.addRawContent(ic->getJunkCards());
    cm.setModal(true);
    cm.exec();
}

void EventCenter::heroUseSkill(int n) {
    if (isAnimating)
        return;
    QVariant data;
    struct SkillPara sp;
    sp.ec = this;
    sp.data = data;
    sp.from = curHero;
    sp.to = NULL;
    SkillBase *skl = curHero->getHeroSkill(n);
    if (skl->type() == SkillType::SkillActive) {
        skl->skillPrepare(sp);
        listHeroInfo(curHero);
    }
}

/*
void EventCenter::birthChosed(QPoint in) {
    setHeroPosition(curHero, in);
    if (curHero == heroSeq.last()) {
        gameBegin();
        return;
    } else {
        curHero = heroSeq[heroSeq.indexOf(curHero)+1];
    }
    QList<QPoint> l;
    for (int i = 0; i < heroSeq.indexOf(curHero); i++) {
        if (heroSeq[i]->point() != QPoint(300, 300) &&
                heroSeq[i]->camp() == curHero->camp()) {
            l.append(heroSeq[i]->point());
        }
    }
    // qDebug() << "list camp" << curHero->camp();
    scene->clearRange();
    scene->showBirthSquare(curHero->camp(), l);
    menu->setPrompt(tr("Choose Birth For Hero: %1").
                    arg(curHero->heroName()));
}
*/

void EventCenter::showSkillRange(QGraphicsItem* from,
                                 MapRangeType t , int r) {
    scene->showSkillRange(static_cast<HeroItem*>(from), t, r);
}

void EventCenter::showSkillRange(QList<QPoint> lp) {
    scene->showRangePoints(lp);
}

QList<HeroItem*> EventCenter::getHerosInList(QList<QPoint> lp) {
    QList<HeroItem*> result;
    foreach(QPoint p, lp) {
        HeroItem* hi = hasHeroOnPoint(p);
        if (hi)
            result.append(hi);
    }
    return result;
}

QList<QPoint> EventCenter::getPointInRange(QPoint o,
                              MapRangeType t,
                              int range) {
    return ic->listSpecialRange(o, t, range);
}

HeroItem* EventCenter::hasHeroOnPoint(QPoint p) {
    return ic->getHeroByPoint(p);
}

QList<HeroItem*> EventCenter::getHerosOfCamp(Camp c) {
    QList<HeroItem*> hl;
    foreach(HeroItem* hi, heroSeq) {
        if (hi->camp() == c) {
            hl.append(hi);
        }
    }
    return hl;
}

// insertion sort
QList<int> EventCenter::rollTheDice(int n) {
    QList<int> result;
    for (int i = 0; i < n; i++) {
        int dice = rand()%6+1;
        result.append(dice);
        for (int j = 0; j < result.size(); j++) {
            if (dice < result[j]) {
                result.insert(j, dice);
                result.removeLast();
                break;
            }
        }
    }
    if (result.size() != n) {
        qDebug() << "Roll The Dices Error";
    }
    return result;
}

void EventCenter::process() {
    while (true) {
        roundBegin();
        while (!isThisRoundComplete()) {
            beginTurn();
            while (askForNewEvent() != GameMenuType::EndTurn);
            endTurn();
        }
        roundEnd();
    }
}

bool EventCenter::isThisRoundComplete() {
    return false;
}

void EventCenter::menuClickAct(GameMenuType gmt) {
    if (sem->available() == 0) {
        sem->release();
        resultsGMT = gmt;
    }
}

QPoint EventCenter::askForSelectPoint() {
    askType = AskType::AskForPoint;
    sem->acquire();

    return resultsPoint;
}

GameMenuType EventCenter::askForNewEvent() {
    askType = AskType::AskForNone;
    sem->acquire();

    switch (resultsGMT) {
    case GameMenuType::Move:
        scene->clearRange();
        scene->showMoveRange(curHero);

        askForSelectPoint();
        heroMoveToPoint(resultsPoint);
        break;
    case GameMenuType::Attack:
        scene->clearRange();
        scene->showAttackRange(curHero);

        askForSelectPoint();
        heroAttackPoint(resultsPoint);
        break;
    case GameMenuType::Skill:
        scene->clearRange();
        scene->showSkillRange(curHero, MapRangeType::RangeTypeStraight, 5);

        askForSelectPoint();
        skillStraightTest(resultsPoint);
        break;
    case GameMenuType::Cancel:
        break;
    case GameMenuType::EndTurn:
        break;
    default:
        break;
    }
    return resultsGMT;
}

void EventCenter::run() {
    gameBegin();
    process();
}
