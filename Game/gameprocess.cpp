#include "gameprocess.h"
#include "otherwidgets.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "eventcenter.h"
#include "herolabel.h"
#include "gameWidget.h"
#include <QDebug>
#include <QState>
#include <QFinalState>

gameProcess::gameProcess() :
	uic(new Ui::chooseHero)
{
    preGame();
	//inGame();
}

void gameProcess::loadResources()
{

}

void gameProcess::preGame()
{
	loadResources();
	modeChooseScreen();
}

void gameProcess::modeChooseScreen()
{
    mcw = new modeChooseWidget();
    mcw->show();
	
	connect(mcw->singleButton(), SIGNAL(clicked()), this, SLOT(heroChooseScreen()));

    mcw->exec();
}

void gameProcess::inGame()
{
    MainWindow m;
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
    for(int i=0; i<4; i++)
    {
        heroLabel* ql = new heroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap("c:/rsc/eee.png"));
        ql->setHeroNum(i);
        uic->horizontalLayout->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    for(int i=0; i<4; i++)
    {
        heroLabel* ql = new heroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap("c:/rsc/eee.png"));
        ql->setHeroNum(i+4);
        uic->horizontalLayout1->addWidget(ql);
        connect(ql, SIGNAL(clicked()), this, SLOT(heroChosed()));
    }
    int res = heroChooseDialog->exec();
    if(res == QDialog::Rejected)
        chosenHeroNum = rand()%20;
	qDebug()<<chosenHeroNum;
	mcw->deleteLater();
}

void gameProcess::heroChosed()
{
    chosenHeroNum = static_cast<heroLabel*>(this->sender())->heroNum();
	heroChooseDialog->accept();
}
