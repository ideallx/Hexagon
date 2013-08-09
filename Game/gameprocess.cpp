#include "gameprocess.h"
#include "otherwidgets.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "eventcenter.h"
#include <QDebug>
#include <QState>
#include <QFinalState>

gameProcess::gameProcess()
{
    preGame();
    //gameBegin();
}

void gameProcess::preGame()
{
    modeChooseWidget* mcw = new modeChooseWidget();
    mcw->show();
    qDebug()<<"fff";
}

void gameProcess::gameBegin()
{
    QList<heroItem*> heroSeq = ic->getActSequence();

    while(true)
    {
        roundNum ++;
        roundBegin();
        for(int i=0; i<heroSeq.size(); i++)
        {
            ec->gameFlow();
        }
        roundEnd();
    }
}

void gameProcess::roundBegin()
{
    //ic->herosLoadPassiveSkill();
    //ic->mapElementAward();
}

void gameProcess::roundEnd()
{

}
