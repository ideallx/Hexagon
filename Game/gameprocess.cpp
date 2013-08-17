#include "gameprocess.h"
#include "otherwidgets.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "eventcenter.h"
#include "herolabel.h"
#include <QDebug>
#include <QState>
#include <QFinalState>

gameProcess::gameProcess() :
	uic(new Ui::chooseHero)
{
    preGame();
}

void gameProcess::preGame()
{
    modeChooseWidget* mcw = new modeChooseWidget();
    mcw->show();

    QEventLoop loop;
    connect(mcw, SIGNAL(destroyed()), &loop, SLOT(quit()), Qt::QueuedConnection);
    loop.exec();

    chooseHeroScreen();
    qDebug()<<"fdsf";
}


void gameProcess::chooseHeroScreen()
{
    qDebug()<<"chosse hero screen";
    heroChooseDialog = new QDialog();
    //heroChooseDialog->setModal(true);
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
}

void gameProcess::heroChosed()
{
    int i = static_cast<heroLabel*>(this->sender())->heroNum();
    qDebug()<<i;
    delete heroChooseDialog;
    emit choseHeroChoose();
}
