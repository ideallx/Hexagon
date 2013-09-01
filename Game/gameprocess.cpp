#include <QDebug>
#include <QMessageBox>

#include "gameprocess.h"
#include "otherwidgets.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "eventcenter.h"
#include "herolabel.h"
#include "gameWidget.h"
#include "itemCollector.h"
#include "backInfo.h"
#include "coordinate.h"
#include "backscene.h"
#include "heroEngine.h"
#include "cardengine.h"
#include "mapelement.h"

#define CONFIGPATH "C:/rsc/config.xml"

gameProcess::gameProcess(QWidget *p):
    parent(p)
{

}

gameProcess::~gameProcess()
{
    qDebug()<<"deconstructor";
}

void gameProcess::loadResources()
{
    try
    {
        gbi = new gameBackInfo(QString(CONFIGPATH));
        qDebug()<<"gbi load complete...";

        hf = new heroFactory(gbi);
        hf->addPackage(new HeroPackageNormal());
        qDebug()<<"hf  load complete...";
    }
    catch(QString e)
    {
        QMessageBox::critical(NULL, tr("LYBNS"), e);
    }
}

void gameProcess::preGame()
{
    loadResources();
    modeChooseScreen();
}

void gameProcess::preGameClean()
{
    delete mcw;
}

void gameProcess::endGame()
{

}

void gameProcess::modeChooseScreen()
{
    mcw = new modeChooseWidget(parent);
    connect(mcw->singleButton(), SIGNAL(clicked()), this, SLOT(heroChooseScreen()));
    mcw->show();

//    QEventLoop loop;
//    QObject::connect(mcw, SIGNAL(destroyed()), &loop, SLOT(quit()), Qt::QueuedConnection);
//    loop.exec();
}

void gameProcess::inGame()
{
}


void gameProcess::heroChooseScreen()
{
    qDebug()<<"chosse hero screen";
    uic = new Ui::chooseHero();
    heroChooseDialog = new QDialog(mcw);
    heroChooseDialog->setModal(true);
    uic->setupUi(heroChooseDialog);

    QList<int> heroNumList;
    qDebug()<<"Total Hero Num:"<<hf->getHeroAmount();
    for(int i=0; i<8; i++)
    {
        int code;
        do
        {
            code = rand()%hf->getHeroAmount();
        }
        while(heroNumList.contains(code));
        heroNumList.append(code);
    }
    for(int i=0; i<4; i++)
    {
        heroLabel* ql = new heroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" + hf->getHeroInfoByNum(heroNumList[i]).heroName + "_Whole.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    for(int i=4; i<8; i++)
    {
        heroLabel* ql = new heroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" + hf->getHeroInfoByNum(heroNumList[i]).heroName + "_Whole.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout1->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    int res = heroChooseDialog->exec();
    if(res != QDialog::Accepted)
    {
        chosenHeroNum = heroNumList[rand()%8];
    }


    qDebug()<<"choose num:"<<chosenHeroNum;
    QList<struct externInfo> result;
    struct externInfo ei;
    QVector<int> heroCode;
    heroCode.append(chosenHeroNum);
    for(int i=0; i<3; i++)
    {
        int code;
        do
        {
            code = rand()%hf->getHeroAmount();
        }
        while(heroCode.contains(code));
        heroCode.append(code);
    }

    ei.c = camp_blue;
    ei.h = (enum heroNum_t)(heroCode[0]);
    ei.p = QPoint(1, 20);
    result.append(ei);

    ei.c = camp_red;
    ei.h = (enum heroNum_t)(heroCode[1]);
    ei.p = QPoint(1, 0);
    result.append(ei);

    ei.c = camp_blue;
    ei.h = (enum heroNum_t)(heroCode[2]);
    ei.p = QPoint(2, 20);
    result.append(ei);

    ei.c = camp_red;
    ei.h = (enum heroNum_t)(heroCode[3]);
    ei.p = QPoint(2, 0);
    result.append(ei);

    eil = result;

    gc = new gameCoordinate(gbi);
    qDebug()<<"gc  load complete...";

    ic = new itemCollector(gbi, gc);

    ic->setCardEngine(new cardEngine(gbi));
    ic->setMapElement(new mapEngine(gbi));
    ic->setCampHealth();
    ic->setHeroFactory(hf, eil);
    qDebug()<<"ic  load complete...";
    qDebug()<<"game start";
    emit gameStart();
}

void gameProcess::heroChosed()
{
    chosenHeroNum = static_cast<heroLabel*>(this->sender())->heroNum();
    heroChooseDialog->accept();
}
