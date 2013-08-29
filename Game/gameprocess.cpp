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

#define CONFIGPATH "C:/rsc/config.xml"

gameProcess::gameProcess() :
	uic(new Ui::chooseHero)
{
    preGame();
	//inGame();
}

void gameProcess::loadResources()
{
	try
	{
		gbi = new gameBackInfo(QString(CONFIGPATH));
		qDebug()<<"gbi load complete...";

		gc = new gameCoordinate(gbi);
		qDebug()<<"gc  load complete...";

		ic = new itemCollector(gbi, gc);
		qDebug()<<"ic  load complete...";

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

void gameProcess::modeChooseScreen()
{
    mcw = new modeChooseWidget();
	connect(mcw->singleButton(), SIGNAL(clicked()), this, SLOT(heroChooseScreen()));
    mcw->exec();
}

void gameProcess::inGame()
{
    MainWindow m(eil);
    m.show();

	QEventLoop loop;
	connect(&m, SIGNAL(destroyed()), &loop, SLOT(quit()), Qt::QueuedConnection);
	loop.exec();
}


void gameProcess::heroChooseScreen()
{
    qDebug()<<"chosse hero screen";
    heroChooseDialog = new QDialog(mcw);
    heroChooseDialog->setModal(true);
    heroChooseDialog->show();
    uic->setupUi(heroChooseDialog);

    QList<int> heroNumList;
    qDebug()<<hf->getHeroAmount();
    for(int i=0; i<8; i++)
    {
        heroNumList.append(rand()%hf->getHeroAmount());
    }
    for(int i=0; i<4; i++)
    {
        heroLabel* ql = new heroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" + hf->getHeroInfoByNum(heroNumList[i]).heroName + "_Head.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    for(int i=4; i<8; i++)
    {
        heroLabel* ql = new heroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" + hf->getHeroInfoByNum(heroNumList[i]).heroName + "_Head.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout1->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    int res = heroChooseDialog->exec();
    if(res == QDialog::Rejected)
        chosenHeroNum = rand()%20;

    qDebug()<<chosenHeroNum;
}

void gameProcess::heroChosed()
{
    chosenHeroNum = static_cast<heroLabel*>(this->sender())->heroNum();
	heroChooseDialog->accept();
}
