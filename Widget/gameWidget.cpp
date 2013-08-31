#include "gameWidget.h"
#include "ui_mainwindow.h"
#include "heroitem.h"
#include "heroengine.h"
#include "backinfo.h"
#include "backview.h"
#include "backscene.h"
#include "menu.h"
#include "coordinate.h"
#include "eventcenter.h"
#include "gameprocess.h"
#include "itemcollector.h"

#define CONFIGPATH "C:/rsc/config.xml"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gp = new gameProcess(this);
    ui->setupUi(this);
    variableInitial();
    connect(ui->actionQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    this->show();

    try
    {
        gp->preGame();
        gp->inGame();

        qDebug()<<"build ui";

        sceneInitial();
        connect(scene, SIGNAL(changeStatusBar(QStringList)), this, SLOT(changeStatusInfo(QStringList)));
        connect(ec, SIGNAL(roundInfoChanged(QStringList)), this, SLOT(changeRoundInfo(QStringList)));
        connect(getCardAction, SIGNAL(triggered()), ec, SLOT(getCard()));
        connect(endTurnAction, SIGNAL(triggered()), ec, SLOT(endTurn()));



        //changeRoundInfo(ec->buildRoundInfo());
        qDebug("initial complete...");
    }
    catch(QString e)
    {
        qDebug()<<e;
        qApp->closeAllWindows();
        qApp->quit();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// AREA:element     coordinate:x, x    camp:hero
// HERO:heroName    coordinate:x, x    camp:hero
bool MainWindow::variableInitial()
{
    endTurnAction = new QAction(tr("End Turn"), this);
    ui->mainToolBar->addAction(endTurnAction);

    getCardAction = new QAction(tr("Get Card"), this);
    ui->mainToolBar->addAction(getCardAction);

    itemLabel = new QLabel(this);
    itemLabel->setFixedWidth(200);
    ui->statusBar->addWidget(itemLabel);

    coordinateLabel = new QLabel(this);
    coordinateLabel->setFixedWidth(200);
    ui->statusBar->addWidget(coordinateLabel);

    campLabel = new QLabel(this);
    campLabel->setFixedWidth(200);
    ui->statusBar->addWidget(campLabel);

    heroLabel = new QLabel(this);
    heroLabel->setFixedWidth(200);
    ui->statusBar->addWidget(heroLabel);

    roundLabel = new QLabel(this);
    roundLabel->setFixedWidth(200);
    ui->statusBar->addWidget(roundLabel);

    return true;
}

bool MainWindow::sceneInitial()
{
    scene = new backScene(gp->getIc(), this);
    ui->graphicsView->setScene(scene);
    gp->getIc()->addItemsToScene(scene);
    menu = new gameMenu(ui->graphicsView);
    //menu->listSlideHeroHead(scene->getHeroListAvaterPath('b'), scene->getHeroListAvaterPath('r'));
    ec = new eventCenter(scene, menu);
    qDebug("backView load complete...");

    return true;
}

void MainWindow::changeStatusInfo(QStringList in)
{
    if(in.size() == 0)
    {
        itemLabel->setText("");
        coordinateLabel->setText("");
    }
    if(in.size() == 2)
    {
        itemLabel->setText(in.at(0));
        coordinateLabel->setText(in.at(1));
    }
}

void MainWindow::changeRoundInfo(QStringList in)
{
    campLabel->setText(in[0]);
    heroLabel->setText(in[1]);
    roundLabel->setText(in[2]);
}
