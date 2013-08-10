#include "eventcenter.h"
#include "heroitem.h"
#include "itemcollector.h"
#include "backscene.h"
#include "menu.h"
#include "backview.h"
#include "coordinate.h"
#include "animationcenter.h"

eventCenter::eventCenter(backScene* scene, gameMenu* menu):
    scene(scene),
    menu(menu),
    ic(scene->pIc()),
    gc(scene->pGc()),
    ac(new animationCenter)
{
    setupConnection();
    curPhase = BeginPhase;

    gia = ac->gia();
    giaTimer = ac->giaTimer();

    qDebug()<<"event center initialized";

    heroSeq = ic->getActSequence();
    curHero = heroSeq[0];
    roundNum = 1;
    menu->setHeroInfo(curHero);
}

void eventCenter::setupConnection()
{
    connect(scene, SIGNAL(heroClicked(heroItem*)), this, SLOT(heroChosen(heroItem*)));
    connect(scene, SIGNAL(sphereClicked(QPoint)), this, SLOT(targetClicked(QPoint)));

    connect(scene, SIGNAL(mapElementClicked(QPoint)), menu, SLOT(hideAllMenu()));
    connect(scene, SIGNAL(mapElementClicked(QPoint)), scene, SLOT(clearSphere()));


    connect(scene, SIGNAL(buildMenu(heroItem*, QPoint)), this, SLOT(showMenu(heroItem*, QPoint)));
    connect(scene, SIGNAL(viewSizeChanged(QSize)), menu, SLOT(reSetInterface(QSize)));
    connect(scene, SIGNAL(listSlideAvaters(QList<QString>,QList<QString>)), menu, SLOT(listSlideHeroHead(QList<QString>,QList<QString>)));

    connect(menu, SIGNAL(moveClicked()), this, SLOT(moveBegin()));
    connect(menu, SIGNAL(attackClicked()), this, SLOT(attackBegin()));

}

void eventCenter::heroChosen(heroItem* hero)
{
    menu->setHeroInfo(hero);
    menu->updateCardsArea(hero->cards());
}

void eventCenter::getCard(int num)
{
    qDebug()<<"get"<<num<<"cards";
    curHero->addCards(ic->getCard(num));
    menu->updateCardsArea(curHero->cards());
    menu->hideAllMenu();
}

void eventCenter::moveBegin()
{
    scene->clearSphere();
    scene->showMoveSphere(curHero);
    curPhase = MovePhase;
}


void eventCenter::heroMoveToPoint(QPoint in)
{
    QPointF oldPos = curHero->scenePos();
    QPointF newPos = gc->getBeginPosOfHero(in);

    if(ic->isPointAvailable(in))
    {
        gia->setItem(curHero);
        gia->setTimeLine(giaTimer);

        double frame = giaTimer->duration()*60/1000;

        double x = (newPos.x() - oldPos.x())/frame;
        double y = (newPos.y() - oldPos.y())/frame;

        for(int i=0; i<=frame; ++i)
            gia->setPosAt(i/frame, oldPos+QPoint(x*i, y*i));

        giaTimer->start();
        scene->clearSphere();
        menu->hideAllMenu();
        menu->setMoveAble(false);

        curHero->setPoint(in);
        curPhase = BeginPhase;
    }
}

void eventCenter::targetClicked(QPoint in)
{
    if(curPhase == MovePhase)
    {
        heroMoveToPoint(in);
    }
    else if(curPhase == AttackPhase)
    {
        heroItem* hi = ic->getHeroByPoint(in);
        hi->setHealth(hi->health()-curHero->attack());
        menu->hideAllMenu();
        menu->setMoveAble(false);
        menu->setAttackAble(false);
        curPhase = BeginPhase;
        scene->clearSphere();
    }
}

void eventCenter::attackBegin()
{
    scene->clearSphere();
    scene->showAttackSphere(curHero);
    curPhase = AttackPhase;
}

void eventCenter::endTurn()
{
    curPhase = FinalPhase;
    menu->resetMenuEnable();

    if(curHero == heroSeq.last())
    {
        curHero = heroSeq[0];
        roundEnd();
        roundNum++;
        roundBegin();
    }
    else
        curHero = heroSeq[heroSeq.indexOf(curHero)+1];


    curPhase = BeginPhase;
    menu->setHeroInfo(curHero);
    menu->updateCardsArea(curHero->cards());
    emit roundInfoChanged(buildRoundInfo());
}

void eventCenter::roundBegin()
{
    //ic->herosLoadPassiveSkill();
    //ic->mapElementAward();
}

void eventCenter::roundEnd()
{

}


QStringList eventCenter::buildRoundInfo()
{
    QStringList qsl;
    QString qs;
    qs = "Camp Turn: ";
    if(curHero->camp() == camp_red)
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

void eventCenter::showMenu(heroItem* hi, QPoint p)
{//TODO for test
    if(curHero == hi)
    {
        menu->showMenu(p);
    }
}
