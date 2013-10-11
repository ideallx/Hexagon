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
      curPhase(ChooseBirthPhase),
      gameBegined(false),
      parent(parent),
      isAnimating (false) {
    setupConnection();
    theGia = new QGraphicsItemAnimation();
    heroSeq = ic->getActSequence();
    roundNum = 1;
    playerHeroNum = ic->playSeq();
    qDebug() << "event center initialized";
#ifdef GIVEN_CONDITION
    curHero = heroSeq[0];
    curHero->addHeroSkill(new HsGuiShou());
    curHero->addHeroSkill(new HsQianXing());
    curHero->addHeroSkill(new HsLengXue());
    birthChosed(QPoint(0, 12));

    curHero = heroSeq[1];
    ArtificialIntellegence* AI = new ArtificialIntellegence(curHero);
    birthChosed(QPoint(4, 1));
    curHero->setAI(AI);

    curHero = heroSeq[2];
    AI = new ArtificialIntellegence(curHero);
    birthChosed(QPoint(0, 14));
    curHero->setAI(AI);

    curHero = heroSeq[3];
    AI = new ArtificialIntellegence(curHero);
    birthChosed(QPoint(4, 0));
    curHero->setAI(AI);

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
    curPhase = BeginPhase;
#else
    menu->setPrompt(tr("Choose Birth For Hero: %1").arg(curHero->heroName()));
    QList<QPoint> l;
    scene->showBirthSquare(curHero->camp(), l);
#endif
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
    connect(menu, SIGNAL(moveClicked()), this, SLOT(moveBegin()));
    connect(menu, SIGNAL(attackClicked()), this, SLOT(attackBegin()));
    connect(menu, SIGNAL(skillButtonClicked()), this, SLOT(skillBegin()));
    connect(menu, SIGNAL(buttonOkClicked(QList<HandCard*>)),
            this, SLOT(cardChosen(QList<HandCard*>)));
    connect(menu, &GameMenu::buttonCancelClicked,
            this, &EventCenter::cardCancel);
    connect(menu, &GameMenu::skillUsed,
            this, &EventCenter::heroUseSkill);
}

void EventCenter::gameBegin() {
    scene->clearRange();
    try {
        checkHeros();
    } catch(const QString& e) {
        QMessageBox::warning(NULL, tr("LYBNS"), e);
        return;
    }

    curPhase = BeginPhase;
    gameBegined = true;
    curHero = heroSeq[0];
    beginTurn();
    menu->setPrompt(tr("Game Begin"));
}

void EventCenter::heroChosen(HeroItem* hero) {
    if (curPhase == ChooseBirthPhase)
        return;
    menu->setHeroInfo(hero);
    showCards(hero);
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

void EventCenter::moveBegin() {
    if (curPhase == ChooseBirthPhase)
        return;
    scene->clearRange();
    scene->showMoveRange(curHero);
    curPhase = MovePhase;
}

void EventCenter::heroMoveToPoint(QPoint in) {
    if (!ic->isPointAvailable(in))
        return;

    GameMapElement* gme = ic->getMapElementByPoint(in);
    moveAnimate(curHero, gme);

    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);

    curHero->setPoint(in);
    curPhase = BeginPhase;

    qDebug() << curHero->heroName() <<
                "Move To Point" << curHero->point();
}

void EventCenter::heroAttackPoint(QPoint in) {
    if (!ic->isPointAvailable(in))
        return;

    waitingEvent = NULL;
    targetHero = ic->getHeroByPoint(in);
    int hitRate = curHero->getMustHitRate();

    if (hitRate == 0x3F) {
        dodge(true);
    } else if (hitRate == 0){
        waitingEvent = &EventCenter::dodge;
        askForUseCard(targetHero, ShanBi);
    } else {
        if ((1 << (rollTheDice(1)[0]-1)) & hitRate) {
            dodge(true);
        } else {
            waitingEvent = &EventCenter::dodge;
            askForUseCard(targetHero, ShanBi);
        }
    }
    return;
}

void EventCenter::dodge(bool got) {
    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);
    if (!curHero->isAttackAble()) {
        menu->setAttackAble(false);
    }
    curPhase = BeginPhase;

    if (got) {
        curHero->removetAttackBouns();
        return;
    }

    QList<SkillBase*> l = curHero->hasSkillTriggerAt(TriggerAttackHit);
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
    curHero->removetAttackBouns();
    qDebug() << curHero->heroName() <<
                "Attack" << targetHero->heroName() <<
                "And Made" << curHero->attack() << "Damage";

    if (curHero->AI() != NULL) {
        endTurn();   // TODO(ideallx) jugg by AI after skills complete
    }
}

void EventCenter::heroAttackPointH(HeroItem* hi) {
    heroAttackPoint(hi->point());
    qDebug() << "Hero Attack Point H";
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
    curPhase = BeginPhase;
}

void EventCenter::targetClicked(QPoint in) {
    if (isAnimating)
        return;
    switch (curPhase) {
    case MovePhase:
        heroMoveToPoint(in);
        break;
    case AttackPhase:
        heroAttackPoint(in);
        break;
    case SkillPhase:
        skillStraightTest(in);
        break;
    case ChooseBirthPhase:
        birthChosed(in);
        break;
    default:
        return;
    }
}

void EventCenter::attackBegin() {
    scene->clearRange();
    scene->showAttackRange(curHero);
    curPhase = AttackPhase;

//    if (!scene->isPointInRange(scene->getLastPoint())) {
//        curPhase = BeginPhase;
//        return;
//    }
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
    curPhase = BeginPhase;
    emit roundInfoChanged(buildRoundInfo());

    if (curHero->AI() == NULL) {
        return;
    }
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
    } else {
        waitForTime(msec);
        heroMoveToPoint(result[result.size()-2]);
        waitForTime(msec);
        heroAttackPoint(targetPoint);
        if (curAI->target()->AI() == NULL)
            return;
    }
    endTurn();
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

    if (curPhase == DiscardPhase)
        return;

    listHeroInfo(curHero);
    if (curHero->cards().size() > HeroItem::endTurnMaxCards()) {
        curPhase = DiscardPhase;
        askForDiscardCards(curHero->cards().size() -
                           HeroItem::endTurnMaxCards());
        if (curHero->AI() != NULL) {
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
        return;
    }

    if (curHero->AI() == NULL)
        waitForTime(1000);

    curPhase = FinalPhase;
    curHero->removetAttackBouns();
    qDebug() << curHero->heroName() + "'s" << "Turn End";

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
    qDebug() << "Round" << roundNum << "End";
    foreach(HeroItem* hi, heroSeq) {
        hi->endRoundSettle();
    }
}


QStringList EventCenter::buildRoundInfo() {
    QStringList qsl;
    QString qs;
    qs = "Camp Turn: ";
    if (curHero->camp() == camp_red)
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

    if (curPhase == ChooseBirthPhase)
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
    menu->setHeroInfo(hi);
    scene->views()[0]->centerOn(hi);
    showCards(hi);
}

void EventCenter::skillBegin() {
    scene->clearRange();
    scene->showSkillRange(curHero, RangeTypeStraight, 5);
    curPhase = SkillPhase;
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
    QList<SkillBase*> l = from->hasSkillTriggerAt(TriggerAttackBegin);
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


void EventCenter::askForDiscardCards(int num) {
    if (num <= 0)
        return;

    menu->setPrompt(QString("Please Discard %1 Cards").arg(num));

    ArtificialIntellegence* ai = curHero->AI();
    if (ai == NULL) {
        return;
    }
    QList<HandCard*> hcl = ai->useCard(num);
    foreach(HandCard* hc, hcl)
        curHero->removeCard(hc);
    menu->updateCardsArea(curHero->cards());
    return;
}

bool EventCenter::askForUseCard(HeroItem* hi,
                                enum Card_Normal_Package_Type_t t) {
    askCard.useCardHero = hi;
    askCard.useCardType = t;
    menu->setPrompt(QString("Please Use Card:"));
    menu->setOneCardMode(true);
    curPhase = AskForCardPhase;

    ArtificialIntellegence* ai = curHero->AI();
    if (ai == NULL)
        return false;

    HandCard* hc = ai->useCard(t);
    if (hc) {
        hi->removeCard(hc);
        menu->updateCardsArea(curHero->cards());
        (this->*waitingEvent)(true);
        return true;
    } else {
        (this->*waitingEvent)(false);
        return false;
    }
}

bool EventCenter::askForNCard(HeroItem* hi, int n) {
    askCard.useCardHero = hi;
    askCard.n = n;
    menu->setPrompt(QString("Please Use Card:"));
    menu->setOneCardMode(false);
    curPhase = AskForCardPhase;

    ArtificialIntellegence* ai = curHero->AI();
    if (ai == NULL)
        return false;

    QList<HandCard*> hcl = ai->useCard(n);
    if (hcl.size() == n) {
        foreach(HandCard* hc, hcl)
            hi->removeCard(hc);
        menu->updateCardsArea(curHero->cards());
        (this->*waitingEvent)(true);
        return true;
    } else {
        (this->*waitingEvent)(false);
        return false;
    }
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

    switch (curPhase) {
    case DiscardPhase:
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
        curPhase = FinalPhase;
        endTurn();
        break;
    case BeginPhase:
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
    case AskForCardPhase:
        if (askCard.useCardHero != menu->panelHero()) {
            return;
        }
        if ((l.size() == 1) && (l[0]->cardType() == askCard.useCardType)) {
            if (waitingEvent)
                (this->*waitingEvent)(true);
        }
        break;
    case AskForNCards:
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
}

void EventCenter::cardCancel() {
    if (isAnimating)
        return;
    switch (curPhase) {
    case AskForCardPhase:
    case AskForNCards:
    case DiscardPhase:
        if (waitingEvent)
            (this->*waitingEvent)(false);
        break;
    default:
        break;
    }
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
    if (skl->type() == SkillActive) {
        skl->skillPrepare(sp);
        listHeroInfo(curHero);
    }
}


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
    qDebug() << "list camp" << curHero->camp();
    scene->clearRange();
    scene->showBirthSquare(curHero->camp(), l);
    menu->setPrompt(tr("Choose Birth For Hero: %1").
                    arg(curHero->heroName()));
}

void EventCenter::showSkillRange(QGraphicsItem* from,
                                 enum MapRangeType_t t , int r) {
    scene->showSkillRange(static_cast<HeroItem*>(from), t, r);
    curPhase = SkillPhase;
}

void EventCenter::showSkillRange(QList<QPoint> lp) {
    scene->showRangePoints(lp);
    curPhase = SkillPhase;
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
                              enum MapRangeType_t t,
                              int range) {
    return ic->listSpecialRange(o, t, range);
}

HeroItem* EventCenter::hasHeroOnPoint(QPoint p) {
    return ic->getHeroByPoint(p);
}

QList<HeroItem*> EventCenter::getHerosOfCamp(Camp_t c) {
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
