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

#define CONFIGPATH "/home/ideallx/Downloads/rsc/"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    variableInitial();
    connect(ui->actionQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    this->show();

    gp = new GameProcess(ui->centralWidget);
    gp->preGame();

    connect(gp, SIGNAL(gameStart()), this, SLOT(gameBegin()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::gameBegin() {
    gp->preGameClean();
    sceneInitial();

    qDebug() << "build ui";
    connect(scene, SIGNAL(changeStatusBar(QStringList)),
            this, SLOT(changeStatusInfo(QStringList)));
    connect(ec, SIGNAL(roundInfoChanged(QStringList)),
            this, SLOT(changeRoundInfo(QStringList)));
    connect(getCardAction, SIGNAL(triggered()), ec, SLOT(getCard()));
    connect(endTurnAction, SIGNAL(triggered()), ec, SLOT(endTurn()));
    // changeRoundInfo(ec->buildRoundInfo());
    qDebug() << "initial complete...";
}

// AREA:element     coordinate:x, x    camp:hero
// HERO:heroName    coordinate:x, x    camp:hero
bool MainWindow::variableInitial() {
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

    HeroLabel = new QLabel(this);
    HeroLabel->setFixedWidth(200);
    ui->statusBar->addWidget(HeroLabel);

    roundLabel = new QLabel(this);
    roundLabel->setFixedWidth(200);
    ui->statusBar->addWidget(roundLabel);

    return true;
}

bool MainWindow::sceneInitial() {
    scene = new BackScene(gp->getIc(), this);
    ui->graphicsView->setScene(scene);
    gp->getIc()->addItemsToScene(scene);
    menu = new GameMenu(ui->graphicsView);
    menu->listSlideHeroHead(scene->getHeroListAvaterPath(camp_blue),
                            scene->getHeroListAvaterPath(camp_red));
    ec = new EventCenter(scene, menu);
    qDebug("backView load complete...");

    return true;
}

void MainWindow::changeStatusInfo(QStringList in) {
    if (in.size() == 0) {
        itemLabel->setText("");
        coordinateLabel->setText("");
    }
    if (in.size() == 2) {
        itemLabel->setText(in.at(0));
        coordinateLabel->setText(in.at(1));
    }
}

void MainWindow::changeRoundInfo(QStringList in) {
    campLabel->setText(in[0]);
    HeroLabel->setText(in[1]);
    roundLabel->setText(in[2]);
}

