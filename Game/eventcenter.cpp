#include <QMessageBox>
#include "eventcenter.h"
#include "heroitem.h"
#include "itemcollector.h"
#include "backscene.h"
#include "menu.h"
#include "BackView.h"
#include "coordinate.h"
#include "mapelement.h"
#include "carditem.h"


EventCenter::EventCenter(BackScene* scene, GameMenu* menu)
    : scene(scene),
    menu(menu),
    ic(scene->pIc()),
    curPhase(ChooseBirthPhase),
    gameBegined(false) {
    setupConnection();
    theGia = new QGraphicsItemAnimation();
    heroSeq = ic->getActSequence();
    roundNum = 1;
    setCurHero(heroSeq[0]);
    playerHeroNum = ic->playSeq();
    qDebug() << "event center initialized";
    menu->setPrompt(tr("Choose Birth For Hero: %1").arg(curHero->heroName()));
    QList<QPoint> l;
    scene->showBirthSquare(curHero->camp(), l);
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
    connect(menu, SIGNAL(skillClicked()), this, SLOT(skillBegin()));
    connect(menu, SIGNAL(buttonOkClicked(QList<HandCard*>)),
            this, SLOT(cardChosen(QList<HandCard*>)));
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

    HeroItem* hi = ic->getHeroByPoint(in);

    attackAnimate(curHero, hi);
    attackCalc(curHero, hi);

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
    } else if (curPhase == ChooseBirthPhase) {
        birthChosed(in);
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

void EventCenter::beginTurn() {
    curHero->setPen(QPen(Qt::black, 3));
    menu->resetMenuEnable();
    if (curHero == heroSeq.last()) {
        curHero = heroSeq[0];
        roundEnd();
        roundNum++;
        roundBegin();
    } else {
        curHero = heroSeq[heroSeq.indexOf(curHero)+1];
    }

    qDebug() << curHero->heroName() + "'s" << "Turn Begin";
    menu->setPrompt("");
    getCard(HeroItem::beginTurnGetCards());
    curPhase = BeginPhase;
    setCurHero(curHero);
    emit roundInfoChanged(buildRoundInfo());
}

void EventCenter::endTurn() {
    if (!gameBegined)
        return;

    if (curPhase == DiscardPhase)
        return;

    if (curHero->cards().size() > HeroItem::endTurnMaxCards()) {
        curPhase = DiscardPhase;
        askForDiscardCards(curHero->cards().size() -
                           HeroItem::endTurnMaxCards());
        return;
    }

    curPhase = FinalPhase;
    qDebug() << curHero->heroName() + "'s" << "Turn End";

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
    if (curPhase == ChooseBirthPhase)
        return;
    if (curHero == hi) {
        menu->showMenu(p);
    }
}

void EventCenter::setCurHero(HeroItem* hi) {
    curHero = hi;
    menu->setHeroInfo(curHero);
    curHero->setPen(QPen(Qt::darkMagenta, 3));
    scene->views()[0]->centerOn(curHero);
    showCards(curHero);
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

    for (int i = 0; i <= frame; ++i)
        theGia->setPosAt(i/frame, srcItem->scenePos()+distance*i/frame);
    moveTimer->start();
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

void EventCenter::attackCalc(HeroItem *from, HeroItem *to) {
    QList<SkillBase*> l = from->hasSkillTriggerAt(TriggerAttackBegin);
    if (l.size() != 0) {
        for (int i = 0; i < l.size(); i++) {

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

void EventCenter::setHeroBirth(HeroItem* hi, QPoint birthP) {
    hi->setPoint(birthP);
    hi->setPos(ic->getBeginPosOfHero(birthP));
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
    menu->askForNCards(num);
    curPhase = DiscardPhase;
}

void EventCenter::mapElementChosen(QPoint p) {
    menu->hideAllMenu();
}

void EventCenter::cardChosen(QList<HandCard*> l) {
    if (l.size() == 0)
        return;

    switch (curPhase) {
    case DiscardPhase:
        for (int i = 0; i < l.size(); i++) {
            ic->returnCard(l);
            if (!curHero->removeCard(l[i]))
                qDebug() << "discard card error";
        }
        qDebug() << "cards num:" << curHero->cards().size();
        menu->updateCardsArea(curHero->cards());
        curPhase = FinalPhase;
        beginTurn();
    case BeginPhase:
        if (l.size() == 1) {
            switch (l[0]->cardType()) {
            case KuangBao:
                curHero->setAttack(curHero->attack()+1);
                // TODO(ideallx) skill function point
                break;

            case ShengMingLiZan:
                break;

            case ZheYue:
                curHero->removeCard(l[0]);
                scene->showSkillRange(curHero, RangeTypeRound, 2);

            case JinBi_2:
                curHero->addMoney(2);
                menu->setHeroInfo(curHero);
                break;

            case JinBi_3:
                curHero->addMoney(3);
                menu->setHeroInfo(curHero);
                break;

            case JinBi_4:
                curHero->addMoney(4);
                menu->setHeroInfo(curHero);
                break;

            default:
                break;
            }
            curHero->removeCard(l[0]);
            menu->updateCardsArea(curHero->cards());


        } else {
        }
    }
}

void EventCenter::birthChosed(QPoint in) {
    setHeroBirth(curHero, in);
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
