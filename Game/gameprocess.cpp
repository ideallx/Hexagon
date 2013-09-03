#include <QDebug>
#include <QMessageBox>

#include "gameprocess.h"
#include "otherwidgets.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "eventcenter.h"
#include "herolabel.h"
#include "gameWidget.h"
#include "ItemCollector.h"
#include "backInfo.h"
#include "coordinate.h"
#include "backscene.h"
#include "heroEngine.h"
#include "cardengine.h"
#include "mapelement.h"

#define CONFIGPATH "C:/rsc/config.xml"

/**
 * ModeChoose -> GameChoose -> HeroChoose -> BirthChoose -> GameBegin
 */
GameProcess::GameProcess(QWidget *p):
    parent(p)
{

}

GameProcess::~GameProcess()
{
    qDebug()<<"deconstructor";
}

void GameProcess::loadResources()
{
    try
    {
        gbi = new GameBackInfo(QString(CONFIGPATH));
        qDebug()<<"gbi load complete...";

        hf = new HeroFactory(gbi);
        hf->addPackage(new HeroPackageNormal());
        qDebug()<<"hf  load complete...";
    }
    catch(const QString& e)
    {
        QMessageBox::critical(NULL, tr("LYBNS"), e);
    }
}

void GameProcess::preGame()
{
    loadResources();
    modeChooseScreen();
}

void GameProcess::preGameClean()
{
    delete mcw;
}

void GameProcess::endGame()
{

}

void GameProcess::gameChooseScreen()
{
    uig = new Ui::ChooseGame();
    heroChooseDialog = new QDialog(mcw);
    heroChooseDialog->setModal(true);
    uig->setupUi(heroChooseDialog);

    int res = heroChooseDialog->exec();
    if (res == QDialog::Accepted)
    {
        struct externInfo ei;
        int totalHero = 4;

        if(uig->mode_2person->isChecked())
            totalHero = 2;
        else if(uig->mode_4person->isChecked())
            totalHero = 4;

        ei.c = camp_blue;
        ei.h = (enum heroNum_t)(0);
        ei.p = QPoint(0, 0);

        for(int i=0; i<totalHero; i++)
            eil.append(ei);

        playerHeroSeq = rand()%totalHero;
        heroChooseScreen();
    }
}

void GameProcess::modeChooseScreen()
{
    mcw = new ModeChooseWidget(parent);
    connect(mcw->singleButton(), SIGNAL(clicked()), this, SLOT(gameChooseScreen()));
    mcw->show();
}

void GameProcess::buildGameInfo()
{
    qDebug()<<"choose num:"<<chosenHeroNum;

    QVector<int> heroCode(eil.size());
    for (int i=0; i<eil.size(); i++)
    {
        int code;
        do
        {
            code = rand()%hf->getHeroAmount();
        }
        while(heroCode.contains(code));
        heroCode.append(code);
    }

    emit gameStart();
}

void GameProcess::inGame()
{
}


void GameProcess::heroChooseScreen()
{
    qDebug()<<"chosse hero screen";
    uic = new Ui::chooseHero();
    heroChooseDialog = new QDialog(mcw);
    heroChooseDialog->setModal(true);
    uic->setupUi(heroChooseDialog);

    QList<int> heroNumList;
    qDebug()<<"Total Hero Num:"<<hf->getHeroAmount();
    for (int i=0; i<8; i++)
    {
        int code;
        do
        {
            code = rand()%hf->getHeroAmount();
        }
        while(heroNumList.contains(code));
        heroNumList.append(code);
    }
    for (int i=0; i<4; i++)
    {
        HeroLabel* ql = new HeroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" + hf->getHeroInfoByNum(heroNumList[i]).heroName + "_Whole.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    for (int i=4; i<8; i++)
    {
        HeroLabel* ql = new HeroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" + hf->getHeroInfoByNum(heroNumList[i]).heroName + "_Whole.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout1->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    int res = heroChooseDialog->exec();
    if(res != QDialog::Accepted)
        chosenHeroNum = heroNumList[rand()%8];
    eil[playerHeroSeq].h = chosenHeroNum;
    birthChooseScreen();
}

void GameProcess::heroChosed()
{
    chosenHeroNum = static_cast<HeroLabel*>(this->sender())->heroNum();
    heroChooseDialog->accept();
}

void GameProcess::birthChooseScreen()
{
    gc = new GameCoordinate(gbi);
    qDebug()<<"gc  load complete...";

    ic = new ItemCollector(gbi, gc);

    ic->setCardEngine(new CardEngine(gbi));
    ic->setMapElement(new MapEngine(gbi));
    ic->setCampHealth();
    ic->setHeroFactory(hf, eil);
    qDebug()<<"ic  load complete...";
    qDebug()<<"game start";

    QList<GameMapElement*> l = ic->getBlueTeamCamp();
    for (int i = 0; i < l.size(); i++)
    {
        qDebug()<<l[i]->point();
    }

    buildGameInfo();
}
