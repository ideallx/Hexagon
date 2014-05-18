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
#include "ai.h"
#include "normalpackage.h"
#include "backinfo.h"

#define GIVEN_CONDITION

EventCenter::EventCenter(BackView *bv, QWidget* parent)
    : roundNum(0),
      gameBegined(false),
      parent(parent),
      isAnimating(false),
      bv(bv),
      askType(AskType::AskForNone),
      playerHeroNum(0),
      resultsNum(0),
      gameTerminated(false),
      loop(new QEventLoop) {
}

EventCenter::~EventCenter() {
    qDebug() << "loop quit";
}

void EventCenter::setupConnection() {
    connect(scene, &BackScene::heroClicked,
            this, &EventCenter::chosenHero);
    connect(scene, &BackScene::rangeClicked,
            this, &EventCenter::chosenTarget);
    connect(scene, &BackScene::buildMenu,
            this, &EventCenter::showMenu);
    connect(scene, &BackScene::mapElementClicked,
            this, &EventCenter::chosenMapElement);

    connect(scene, &BackScene::viewSizeChanged,
            menu, &GameMenu::reSetInterface);

    connect(menu, &GameMenu::menuClicked,
            this, &EventCenter::chosenMenu);

    connect(menu, &GameMenu::buttonOkClicked,
            this, &EventCenter::chosenCard, Qt::QueuedConnection);
    connect(menu, &GameMenu::buttonCancelClicked,
            this, &EventCenter::chosenCancel, Qt::QueuedConnection);
    connect(menu, &GameMenu::skillUsed,
            this, &EventCenter::heroUseSkill);
//    connect(menu, &GameMenu::cancelClicked,
//            scene, &BackScene::clearRange);
    connect(this, &EventCenter::changeHeroInfo,
            menu, &GameMenu::setHeroInfo);

    connect(this, &EventCenter::releaseLock,
            loop, &QEventLoop::quit);
}

void EventCenter::setupAIConnection() {
    foreach (HeroItem* hi, heroSeq) {
        AI *ai = hi->getAI();
        if (ai == NULL) {
            continue;
        }
        connect(ai, &AI::heroClicked, this, &EventCenter::chosenHero,
                Qt::DirectConnection);
        connect(ai, &AI::rangeClicked, this, &EventCenter::chosenTarget,
                Qt::DirectConnection);
        connect(ai, &AI::menuClicked, this, &EventCenter::chosenMenu,
                Qt::DirectConnection);
        connect(ai, &AI::skillUsed, this, &EventCenter::heroUseSkill,
                Qt::DirectConnection);
        connect(ai, &AI::turnEnd, this, &EventCenter::endTurnSignal,
                Qt::DirectConnection);

        connect(ai, &AI::buttonOkClicked, this, &EventCenter::chosenCard,
                Qt::DirectConnection);
        connect(ai, &AI::buttonCancelClicked, this, &EventCenter::chosenCancel,
                Qt::DirectConnection);
        ai->start();
    }
}

// 1 BEFORE GAME START
void EventCenter::preGame() {
#ifdef GIVEN_CONDITION
    loadResources("../rsc/DeathDesert2.xml");
    for (int i = 0; i < 4; i++) {
        ExternInfo ei;
        ei.h = static_cast<HeroNum>(rand() % hf->getHeroAmount());
        ei.p = QPoint(300, 300);  // untouchable point
        eil.append(ei);
    }
    eil[0].h = HeroNum::AnYingZhiRen;
    buildGameInfo(HeroNum::MieShaZhe);
#else
    modeChooseScreen();
#endif
    gameReady();
}

void EventCenter::gameReady() {
    scene = new BackScene(ic, bv);
    bv->setScene(scene);
    ic->addItemsToScene(scene);
    menu = new GameMenu(bv);
    menu->listSlideHeroHead(scene->getHeroListAvaterPath(Camp::CampBlue),
                            scene->getHeroListAvaterPath(Camp::CampRed));
    qDebug("backView load complete...");

    setupConnection();
    theGia = new QGraphicsItemAnimation(this);
    playerHeroNum = ic->playSeq();
    qDebug() << "event center initialized";
}

void EventCenter::buildGameInfo(HeroNum chosenHeroNum) {
    qDebug() << "choose num:" << static_cast<int>(chosenHeroNum);

    gc = new GameCoordinate(gbi);
    qDebug() << "gc  load complete...";

    ic = new ItemCollector(gbi, gc);

    ic->setMapElement(new MapEngine(gbi));

    CardEngine *ce = new CardEngine(gbi);
    ce->addPackage(new CardPackageNormal());
    ic->setCardEngine(ce);

    ic->setCampHealth();

    QVector<HeroNum> heroCode;
    heroCode.append(eil[playerHeroNum].h);
    for (int i = 0; i < eil.size(); i++) {
        if (i%2)
            eil[i].c = Camp::CampRed;
        else
            eil[i].c = Camp::CampBlue;

        if (i == playerHeroNum)
            continue;

        HeroNum code;
        do {
            code = static_cast<HeroNum>(rand()%hf->getHeroAmount());
        } while (heroCode.contains(code));
        heroCode.append(code);

        eil[i].h = code;
    }

    ic->setHeroFactory(hf, eil);
    ic->setPlaySeq(playerHeroNum);
    qDebug() << "ic  load complete...";
    EquipmentShop* es = new EquipmentShop(gbi->getConfigDir());
    es->addEquipmentPackage(new EquipmentPackageNormal());
    ic->setEquipmentShop(es);
}

void EventCenter::loadResources(QString path) {
    try {
        gbi = new GameBackInfo(path);
        qDebug() << "gbi load complete...";

        hf = new HeroFactory(gbi);
        hf->addPackage(new HeroPackageNormal());
        qDebug() << "hf  load complete...";
    } catch(const QString& e) {
        QMessageBox::critical(NULL, tr("LYBNS"), e);
    }
}

void EventCenter::checkHeros() {
    for (int i = 0; i < heroSeq.size(); i++) {
        if (heroSeq[i]->point() == QPoint(300, 300)) {
            throw QString(tr("Hero %1: Wrong Birth Point").
                          arg(heroSeq[i]->heroName()));
        }
    }
}
// 1 BEFORE GAME END

// 2 GAME PROCESS START
void EventCenter::run() {
    try {
        gameBegin();
        process();
    } catch(const QString& e) {
        qDebug() << e;
    }
}

void EventCenter::gameBegin() {
    heroSeq = ic->getActSequence();
#ifdef GIVEN_CONDITION
    curHero = heroSeq[0];
    curHero->addHeroSkill(new HsGuiShou());
    curHero->addHeroSkill(new HsQianXing());
    curHero->addHeroSkill(new HsLengXue());
    setHeroPosition(curHero, QPoint(0, 12));

    curHero = heroSeq[1];
    AI* ai = new AI(curHero, ic);
    curHero->setAI(ai);
    setHeroPosition(curHero, QPoint(4, 1));

    curHero = heroSeq[2];
    ai = new AI(curHero, ic);
    curHero->setAI(ai);
    setHeroPosition(curHero, QPoint(0, 14));

    curHero = heroSeq[3];
    ai = new AI(curHero, ic);
    curHero->setAI(ai);
    setHeroPosition(curHero, QPoint(4, 0));

    for (int i = 0; i < heroSeq.size(); i++) {
        AI* ai = heroSeq[i]->getAI();
        if (ai == NULL) {
            continue;
        }
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
    setupAIConnection();

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



void EventCenter::process() {
    while (true) {
        roundBegin();
        do {
            turnBegin();
            while (askForNewEvent() != GameMenuType::EndTurn);
            turnEnd();
        } while (!isThisRoundComplete());
        roundEnd();
    }
}
void EventCenter::turnBegin() {
    menu->setPrompt("");
    qDebug() << curHero->heroName() + "'s" << "Turn Begin";

    getCard(HeroItem::beginTurnGetCards());
    setCurHero(curHero);
    curHero->beginTurnSettle();
    menu->beginTurnReset();
    emit roundInfoChanged(buildRoundInfo());
}

void EventCenter::turnEnd() {
    if (!gameBegined)
        return;

    listHeroInfo(curHero);
    if (curHero->cards().size() > HeroItem::endTurnMaxCards()) {
        askForNCard(curHero, curHero->cards().size() -
                    HeroItem::endTurnMaxCards());
        foreach (HandCard* hc, resultsCard) {
            curHero->removeCard(hc);
        }
    }

    if (curHero->getAI() != NULL)
        waitForTime(1000);

    curHero->aa->removeAttackBouns();
    qDebug() << curHero->heroName() + "'s" << "Turn End\n";

    curHero->setPen(QPen(Qt::black, 3));
}

void EventCenter::roundBegin() {
    // ic->herosLoadPassiveSkill();
    // ic->mapElementAward();
    roundNum++;
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
// 2 GAME PROCESS END

// 3 SINGLE PROCESS START
void EventCenter::heroMoveToPoint(QPoint in) {
    if (!ic->isPointAvailable(in))
        throw QString("Move To Point: target is not available");

    if (!curHero->ma->remainingTimes())
        throw QString("Move To Point: hero cannot move now");

    Q_ASSERT(ic->getHeroByPoint(in) == NULL);

    scene->clearRange();
    GameMapElement* gme = ic->getMapElementByPoint(in);
    moveAnimate(curHero, gme);

    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);

    curHero->setPoint(in);
    curHero->ma->moveTimeMinus();

    qDebug() << curHero->heroName() <<
                "Move To Point" << curHero->point();
}

void EventCenter::heroAttackPoint(QPoint in) {
    if (!ic->isPointAvailable(in))
        throw QString(tr("Attack Target Not Found"));

    scene->clearRange();
    targetHero = ic->getHeroByPoint(in);

    runSkills(TriggerTime::TriggerAttackBegin, curHero, targetHero);
    int hitRate = curHero->aa->mustHitRate();
    bool isHit = heroDodge(hitRate);

    if (!isHit) {
        curHero->aa->removeAttackBouns();
        qDebug() << targetHero->heroName() <<
                    "Dodged The Attack From" << curHero->heroName();
        return;
    }

    // if hit
    runSkills(TriggerTime::TriggerAttackHit, curHero, targetHero);
    runSkills(TriggerTime::TriggerAttackEnd, curHero, targetHero);

    attackAnimate(curHero, targetHero);
    // attackCalc(curHero, targetHero);
    curHero->aa->removeAttackBouns();
    listHeroInfo(curHero);
    qDebug() << curHero->heroName() <<
                "Attack" << targetHero->heroName() <<
                "And Made" << curHero->aa->attack() << "Damage";
    return;
}

/**
 * @brief EventCenter::dodge
 * @param hitRate
 * @return true  targetHero get Hit
 *         false targetHero doged the attack successfully
 */
bool EventCenter::heroDodge(int hitRate) {
    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);
    if (!curHero->aa->remainingTimes()) {
        menu->setAttackAble(false);
    }

    // if 100%hit  or  dice rolls at a certain num  you cant dodge
    if ((hitRate == 0x3F) || ((1 << (rollTheDice(1)[0]-1)) & hitRate)) {
        return true;
    } else {
        return !askForUseCard(targetHero, CardNormalPackageType::ShanBi);
    }

//    if (hitRate == 0x3F) {
//        return true;
//    } else if (hitRate == 0){
//        return !askForUseCard(targetHero, CardNormalPackageType::ShanBi);
//    } else {
//        if ((1 << (rollTheDice(1)[0]-1)) & hitRate) {
//            return true;
//        } else {
//            return !askForUseCard(targetHero, CardNormalPackageType::ShanBi);
//        }
//    }

}

void EventCenter::heroUseSkill(int n) {
    if (isAnimating)
        return;

    if ((askType != AskType::AskForNone) &&
            (askType != AskType::AskForSkill)) {
        return;
    }

    resultsGMT = GameMenuType::Skill;
    resultsNum = n;
    release();
    return;
}

void EventCenter::heroSkillTest(QPoint in) {
    GameMapElement* gme = ic->getMapElementByPoint(in);

    SkillPara sp(this, QVariant(), curHero, gme);

    skillAnimate(curHero, gme);
    curSkill->skillFlow(sp);

    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);
    menu->setSkillAble(false);
}
// 3 SINGLE PROCESS END

// 4 PLAYER EVENT START
GameMenuType EventCenter::askForNewEvent() {
    qDebug() << "Wait For New Event";
    AI* ai = curHero->getAI();
    if (ai) {
        ai->aisTurn();
    }

    acquire(AskType::AskForNone);

    try {
        scene->clearRange();
        switch (resultsGMT) {
        case GameMenuType::Move:
            scene->showMoveRange(curHero);
            heroMoveToPoint(askForSelectPoint());
            break;
        case GameMenuType::Attack:
            scene->showAttackRange(curHero);
            heroAttackPoint(askForSelectPoint());
            break;
        case GameMenuType::Skill:
            SkillPara sp(this, QVariant(), curHero, NULL);
            SkillBase *skl = curHero->getHeroSkill(resultsNum);
            if (skl->type() == SkillType::SkillActive) {
                skl->skillPrepare(sp);
                listHeroInfo(curHero);
            }
            break;
        case GameMenuType::SkillTest:
            scene->showSkillRange(curHero, MapRangeType::RangeTypeStraight, 5);

            heroSkillTest(askForSelectPoint());
            break;
        case GameMenuType::Cancel:
            break;
        case GameMenuType::EndTurn:
            break;
        default:
            break;
        }
    } catch (QString e) {
        qDebug() << e;
    }

    return resultsGMT;
}


bool EventCenter::askForUseCard(HeroItem* hi,
                                CardNormalPackageType t) {
    askCard.useCardHero = hi;
    askCard.useCardType = t;
    menu->setPrompt(QString("Please Use Card:"));  // type
    menu->setOneCardMode(true);

    AI* ai = hi->getAI();
    if (ai == NULL) {
        menu->setHeroInfo(hi);
        showCards(hi);
        acquire(AskType::AskForCards);
    } else {
        acquireAI(ai, AskType::AskForCards);
        ai->askCard(t, 1);
        ai->dothings(AskType::AskForCards);
        loopExec();
    }
    if (resultsCard.size() > 1) {
        throw QString(tr("chose more than 1 card"));
    } else if (resultsCard.size() == 1) {
        hi->removeCard(resultsCard[0]);
        return true;
    } else {
        return false;
    }
}

bool EventCenter::askForNCard(HeroItem* hi, int n) {
    askCard.useCardHero = hi;
    askCard.n = n;
    menu->setPrompt(QString("Please Use %1 Cards:").arg(n));
    menu->setOneCardMode(false);

    AI* ai = curHero->getAI();
    if (ai == NULL) {
        acquire(AskType::AskForCards);
        return true;
    }

    ai->askCard(CardNormalPackageType::Any, n);
    return true;
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

QPoint EventCenter::askForSelectPoint() {
    acquire(AskType::AskForPoint);

    return resultsPoint;
}


void EventCenter::askForChooseBox() {

}

void EventCenter::acquire(AskType at) {
    askType = at;

    AI* ai = curHero->getAI();
    if (ai) {
        ai->dothings(at);
    }
    loopExec();
}

void EventCenter::loopExec() {
    loop->exec();
    if (gameTerminated) {
        throw QString(tr("Game Terminated"));
    }
}

void EventCenter::acquireAI(AI* ai, AskType at) {
    Q_ASSERT(ai != NULL);
    askType = at;
    ai->aisReact();
}

void EventCenter::release() {
    // sem->release();
    emit releaseLock();
}

/**
 * @brief EventCenter::chosenHero
 * @param hero
 * change parameter to QPoint later
 */
void EventCenter::chosenHero(HeroItem* hero) {
    if (askType != AskType::AskForPoint) {
        menu->setHeroInfo(hero);
        return;
    }
//    if (sem->available()) {
//        menu->setHeroInfo(hero);
//        showCards(hero);
//        return;
//    } else {
//        resultsPoint = hero->point();
//        sem->release();
//        return;
//    }
}

void EventCenter::chosenTarget(QPoint in) {
    if (askType != AskType::AskForPoint) {
        return;
    }
    if (isAnimating)
        return;

    if (askType == AskType::AskForPoint) {
        resultsPoint = in;
        release();
        return;
    }
}


void EventCenter::chosenMenu(GameMenuType gmt) {
    if (askType != AskType::AskForNone) {
        return;
    }

    resultsGMT = gmt;
    release();
}


void EventCenter::chosenMapElement(QPoint p) {
    Q_UNUSED(p);
    menu->hideAllMenu();
}

void EventCenter::chosenCard(QList<HandCard*> l) {
    if (isAnimating)
        return;
    if (l.size() == 0)
        return;

    if (askType == AskType::AskForCards) {
        qDebug() << "card chosen";
        resultsCard.clear();
        resultsCard += l;
        release();
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
            SkillPara sp;
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

void EventCenter::chosenCancel() {
    if (isAnimating)
        return;
    if (askType == AskType::AskForCards) {
        resultsCard.clear();
        qDebug() << "card cancel";
        release();
        return;
    }
}

void EventCenter::openShop() {
    ChooseMenu cm(parent);
    cm.addRawContent(ic->getJunkCards());
    cm.setModal(true);
    cm.exec();
}

void EventCenter::endTurnSignal() {
    resultsGMT = GameMenuType::EndTurn;
    qDebug() << "End Turn";
    release();
}

void EventCenter::endLoop() {
    gameTerminated = true;
    release();
    qDebug() << "End Loop";
}


// 4 PLAYER EVENT START

// 5 FUNCTION START
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

void EventCenter::getCard(int num) {
    if (!gameBegined)
        return;
    qDebug() << curHero->heroName() << "get" << num << "cards";
    curHero->addCards(ic->getCard(num));
    showCards(curHero);
    menu->hideAllMenu();
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
    curHero->setPos(dst);
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
    to->addHealth(- from->aa->attack());
    if (l.size() != 0) {
        for (int i = 0; i < l.size(); i++) {
            if (!l[i]->isWorkNow()) {   // TODO(ideallx) to fix
                l.removeAt(i);
            } else {
                SkillPara sp(this, QVariant(), from, to);

                l[i]->skillFlow(sp);
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

bool EventCenter::isThisRoundComplete() {
    if (curHero == heroSeq.last()) {
        return true;
    } else {
        curHero = heroSeq[heroSeq.indexOf(curHero)+1];
        return false;
    }
}


void EventCenter::runSkills(TriggerTime tt,
                            HeroItem* from, QGraphicsItem* to) {
    QList<SkillBase*> l = from->hasSkillTriggerAt(tt);
    if (l.size() != 0) {
        for (int i = 0; i < l.size(); i++) {
            SkillPara sp(this, QVariant(), from, to);

            l[i]->skillFlow(sp);
        }
    }
}

void EventCenter::mapClear() {
    scene->clearRange();
    menu->hideAllMenu();
}

void EventCenter::waitForTime(int msec) {
    QTimer timer;
    QEventLoop l;
    connect(&timer, &QTimer::timeout, &l, &QEventLoop::quit);
    timer.start(msec);
    l.exec();
}

void EventCenter::showCards(HeroItem* hero) {
//    if (heroSeq.indexOf(hero) == playerHeroNum) {
//        menu->updateCardsArea(hero->cards());
//    } else {
//        menu->updateCardsArea(ic->switchToBack(hero->cards()));
//    }
    menu->updateCardsArea(hero->cards());
}
