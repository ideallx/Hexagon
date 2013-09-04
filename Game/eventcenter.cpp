#include "eventcenter.h"
#include "heroitem.h"
#include "itemcollector.h"
#include "backscene.h"
#include "menu.h"
#include "BackView.h"
#include "coordinate.h"
#include "mapelement.h"

/*
 *  gc not get
 */

EventCenter::EventCenter(BackScene* scene, GameMenu* menu)
    : scene(scene),
    menu(menu),
    ic(scene->pIc()) {
    setupConnection();
    curPhase = BeginPhase;

    theGia = new QGraphicsItemAnimation();
    qDebug() << "event center initialized";

    heroSeq = ic->getActSequence();
    roundNum = 1;
    setCurHero(heroSeq[0]);
}

void EventCenter::setupConnection() {
    connect(scene, SIGNAL(heroClicked(HeroItem* hi)),
            this, SLOT(heroChosen(HeroItem* hi)));
    connect(scene, SIGNAL(rangeClicked(QPoint p)),
            this, SLOT(targetClicked(QPoint p)));

    connect(scene, SIGNAL(buildMenu(HeroItem* hi, QPoint p)),
            this, SLOT(showMenu(HeroItem* hi, QPoint p)));
    connect(scene, SIGNAL(viewSizeChanged(QSize s)),
            menu, SLOT(reSetInterface(QSize s)));

    connect(menu, SIGNAL(moveClicked()), this, SLOT(moveBegin()));
    connect(menu, SIGNAL(attackClicked()), this, SLOT(attackBegin()));
    connect(menu, SIGNAL(skillClicked()), this, SLOT(skillBegin()));
}

void EventCenter::heroChosen(HeroItem* hero) {
    menu->setHeroInfo(hero);
    menu->updateCardsArea(hero->cards());
    qDebug() << hero->heroName() << "at" << hero->point();
}

void EventCenter::getCard(int num) {
    qDebug() << "get" << num << "cards";
    curHero->addCards(ic->getCard(num));
    menu->updateCardsArea(curHero->cards());
    menu->hideAllMenu();
}

void EventCenter::moveBegin() {
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

    HeroItem* hi = ic->getHeroByPoint(in);

    attackAnimate(curHero, hi);
    hi->setHealth(hi->health() - curHero->attack());

    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);
    menu->setAttackAble(false);
    curPhase = BeginPhase;

    qDebug() << curHero->heroName() <<
                "Attack" << hi->heroName() <<
                "And Made" << curHero->attack() << "Damage";
}

void EventCenter::skillStraightTest(QPoint in) {
    GameMapElement* gme = ic->getMapElementByPoint(in);

    skillAnimate(curHero, gme);

    scene->clearRange();
    menu->hideAllMenu();
    menu->setMoveAble(false);
    menu->setSkillAble(false);
    curPhase = BeginPhase;
}

void EventCenter::targetClicked(QPoint in) {
    if (curPhase == MovePhase) {
        heroMoveToPoint(in);
    } else if (curPhase == AttackPhase) {
        heroAttackPoint(in);
    } else if (curPhase == SkillPhase) {
        skillStraightTest(in);
    }
}

void EventCenter::attackBegin() {
    scene->clearRange();
    scene->showAttackRange(curHero);
    curPhase = AttackPhase;
}

void EventCenter::mapClear() {
    scene->clearRange();
    menu->hideAllMenu();
}

void EventCenter::endTurn() {
    curPhase = FinalPhase;
    menu->resetMenuEnable();
    curHero->setPen(QPen(Qt::black, 3));
    qDebug() << curHero->heroName() + "'s" << "Turn End";

    if (curHero == heroSeq.last()) {
        curHero = heroSeq[0];
        roundEnd();
        roundNum++;
        roundBegin();
    } else {
        curHero = heroSeq[heroSeq.indexOf(curHero)+1];
    }

    qDebug() << curHero->heroName() + "'s" << "Turn Begin";
    curPhase = BeginPhase;
    setCurHero(curHero);
    emit roundInfoChanged(buildRoundInfo());
}

void EventCenter::roundBegin() {
    // ic->herosLoadPassiveSkill();
    // ic->mapElementAward();
    qDebug() << "Round" << roundNum << "Begin";
}

void EventCenter::roundEnd() {
    qDebug() << "Round" << roundNum << "End";
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
    if (curHero == hi) {
        menu->showMenu(p);
    }
}

void EventCenter::setCurHero(HeroItem* hi) {
    curHero = hi;
    menu->setHeroInfo(curHero);
    curHero->setPen(QPen(Qt::darkMagenta, 3));
    scene->views()[0]->centerOn(curHero);
    menu->updateCardsArea(curHero->cards());
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
    qDebug() << "Move Animate Prepare";

    double frame = 12;
    qDebug() << "move from" << srcItem->point() <<
                "to" << targetItem->point();

    QPointF src = ic->getBeginPosOfHero(srcItem->point());
    QPointF dst = ic->getBeginPosOfHero(targetItem->point());

    QPointF distance = dst - src;
    qDebug() << "move from" << srcItem->point() <<
                "to" << targetItem->point() << distance;

    for (int i = 0; i <= frame; ++i)
        theGia->setPosAt(i/frame, srcItem->scenePos()+distance*i/frame);
    moveTimer->start();
    qDebug() << "Move Animate Start";
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

    attackTimer->start();
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


void EventCenter::chooseBirth() {
    scene->showBirthSquare(camp_red);
}
