#include "gameprocess.h"
#include "otherwidgets.h"
#include <QDebug>

gameProcess::gameProcess(int playerNum)
{
    thePlayerNum = playerNum;
    curPlayerNum = 0;
    qDebug()<<"sfa";

    otherWidgets* ow = new otherWidgets();
    ow->show();
}

void gameProcess::gameBegin()
{
    qDebug()<<"game begin";
}
