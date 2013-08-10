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
}

void gameProcess::preGame()
{
    modeChooseWidget* mcw = new modeChooseWidget();
    mcw->show();
}

