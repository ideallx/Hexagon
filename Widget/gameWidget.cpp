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

#define CONFIGPATH "C:/rsc/config.xml"

MainWindow::MainWindow(QList<struct externInfo> info, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    endTurnAction = new QAction(tr("End Turn"), this);
    ui->mainToolBar->addAction(endTurnAction);

    getCardAction = new QAction(tr("Get Card"), this);
    ui->mainToolBar->addAction(getCardAction);

    variableInitial();
    sceneInitial(info);

    connect(ui->actionQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    connect(getCardAction, SIGNAL(triggered()), ec, SLOT(getCard()));
    connect(endTurnAction, SIGNAL(triggered()), ec, SLOT(endTurn()));
    connect(scene, SIGNAL(changeStatusBar(QStringList)), this, SLOT(changeStatusInfo(QStringList)));
    connect(ec, SIGNAL(roundInfoChanged(QStringList)), this, SLOT(changeRoundInfo(QStringList)));

    //changeRoundInfo(ec->buildRoundInfo());
    qDebug("initial complete...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// AREA:element     coordinate:x, x    camp:hero
// HERO:heroName    coordinate:x, x    camp:hero
bool MainWindow::variableInitial()
{


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

bool MainWindow::sceneInitial(QList<struct externInfo>)
{
    QList<struct externInfo> info = chooseHero();

    scene = new backScene(gbi, gc, info, this);
    ui->graphicsView->setScene(scene);
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

QList<struct externInfo> MainWindow::chooseHero()
{
    QList<struct externInfo> result;
    struct externInfo ei;

    QVector<int> heroCode;
    for(int i=0; i<4; i++)
    {
        int code;
        do
        {
            code = rand()%20;
            qDebug()<<code;
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

    return result;
}
