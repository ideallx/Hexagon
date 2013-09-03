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
GameProcess::GameProcess(QWidget *p) :
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
    delete uic;
    //delete uib;
    delete uig;
}

void GameProcess::endGame()
{

}

void GameProcess::gameChooseScreen()
{
    uig = new Ui::ChooseGame();
    chooseDialog = new QDialog(mcw);
    chooseDialog->setModal(true);
    uig->setupUi(chooseDialog);

    int res = chooseDialog->exec();
    if (res == QDialog::Accepted)
    {
        struct externInfo ei;
        int totalHero = 4;

        if(uig->mode_2person->isChecked())
            totalHero = 2;
        else if(uig->mode_4person->isChecked())
            totalHero = 4;

        ei.h = (enum heroNum_t)(0);
        ei.p = QPoint(0, 0);

        for(int i=0; i<totalHero; i++)
        {
            eil.append(ei);
        }

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

    gc = new GameCoordinate(gbi);
    qDebug()<<"gc  load complete...";

    ic = new ItemCollector(gbi, gc);

    ic->setMapElement(new MapEngine(gbi));
    ic->setCardEngine(new CardEngine(gbi));
    ic->setCampHealth();

    QVector<int> heroCode(eil.size());
    for (int i=0; i<eil.size(); i++)
    {
        if(i%2)
            eil[i].c = camp_blue;
        else
            eil[i].c = camp_red;

        if (i == playerHeroSeq)
            continue;

        int code;
        do
        {
            code = rand()%hf->getHeroAmount();
        }
        while(heroCode.contains(code));

        eil[i].h = code;
    }

    ic->setHeroFactory(hf, eil);
    ic->setPlaySeq(playerHeroSeq);
    qDebug()<<"ic  load complete...";
    emit gameStart();
}

void GameProcess::inGame()
{
}


void GameProcess::heroChooseScreen()
{
    qDebug()<<"chosse hero screen";
    uic = new Ui::chooseHero();
    chooseDialog = new QDialog(mcw);
    chooseDialog->setModal(true);
    uic->setupUi(chooseDialog);

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
        HeroLabel* ql = new HeroLabel(chooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" + hf->getHeroInfoByNum(heroNumList[i]).heroName + "_Whole.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    for (int i=4; i<8; i++)
    {
        HeroLabel* ql = new HeroLabel(chooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" + hf->getHeroInfoByNum(heroNumList[i]).heroName + "_Whole.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout1->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    int res = chooseDialog->exec();
    if(res != QDialog::Accepted)
        chosenHeroNum = heroNumList[rand()%8];
    eil[playerHeroSeq].h = chosenHeroNum;
    buildGameInfo();
}

void GameProcess::heroChosed()
{
    chosenHeroNum = static_cast<HeroLabel*>(this->sender())->heroNum();
    chooseDialog->accept();
}

void GameProcess::birthChooseScreen()
{
    qDebug()<<"chosse birth screen";
    uib = new Ui::ChooseBirth();
    chooseDialog = new QDialog(mcw);
    chooseDialog->setModal(true);
    uib->setupUi(chooseDialog);


    QGraphicsScene *qgs = new QGraphicsScene();
    for(int i = 0; i < 2; i++)
    {
        GameMapElement* gme = new GameMapElement\
                (gbi->getLineLength(), (enum gameEnvironment_t)0,\
                 QPoint(i, 1), gbi->getConfigDir()+"elements/");
        gme->setPos(gc->leftUpPosNoOffset(gme->point()));
        qgs->addItem(gme);
    }
    for(int i = 0; i < 3; i++)
    {
        GameMapElement* gme = new GameMapElement\
                (gbi->getLineLength(), (enum gameEnvironment_t)0,\
                 QPoint(i, 2), gbi->getConfigDir()+"elements/");
        gme->setPos(gc->leftUpPosNoOffset(gme->point()));
        qgs->addItem(gme);
    }
    for(int i = 0; i < 2; i++)
    {
        GameMapElement* gme = new GameMapElement\
                (gbi->getLineLength(), (enum gameEnvironment_t)0,\
                 QPoint(i, 3), gbi->getConfigDir()+"elements/");
        gme->setPos(gc->leftUpPosNoOffset(gme->point()));
        qgs->addItem(gme);
    }
    for(int i = 0; i < 2; i++)
    {
        GameMapElement* gme = new GameMapElement\
                (gbi->getLineLength(), (enum gameEnvironment_t)0,\
                 QPoint(1, i*4), gbi->getConfigDir()+"elements/");
        gme->setPos(gc->leftUpPosNoOffset(gme->point()));
        qgs->addItem(gme);
    }

    uib->graphicsView->setScene(qgs);

    QList<GameMapElement*> l = ic->getBlueTeamCamp();
    for (int i = 0; i < l.size(); i++)
    {
        qDebug()<<l[i]->point();
    }

    int res = chooseDialog->exec();
}
