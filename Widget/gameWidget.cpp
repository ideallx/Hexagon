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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    variableInitial();
    connect(ui->actionQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    this->show();

    gp = new GameProcess(ui->centralWidget);
    connect(gp, &GameProcess::gameStart, this, &MainWindow::gameBegin);
    gp->preGame();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::gameBegin() {
    gp->preGameClean();
    sceneInitial();

    qDebug() << "build ui";
    connect(scene, &BackScene::changeStatusBar,
            this, &MainWindow::changeStatusInfo);
    connect(ec, &EventCenter::roundInfoChanged,
            this, &MainWindow::changeRoundInfo);
    connect(getCardAction, &QAction::triggered, ec, &EventCenter::getCard);
    connect(endTurnAction, &QAction::triggered, ec, &EventCenter::endTurnSignal);
    connect(openShop, &QAction::triggered, ec, &EventCenter::openShop);
    // changeRoundInfo(ec->buildRoundInfo());
    qDebug() << "initial complete...";
    ec->start();
}

// AREA:element     coordinate:x, x    camp:hero
// HERO:heroName    coordinate:x, x    camp:hero
bool MainWindow::variableInitial() {
    endTurnAction = new QAction(tr("End Turn"), this);
    ui->mainToolBar->addAction(endTurnAction);

    getCardAction = new QAction(tr("Get Card"), this);
    ui->mainToolBar->addAction(getCardAction);

    openShop = new QAction(tr("Shop"), this);
    ui->mainToolBar->addAction(openShop);

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
    menu->listSlideHeroHead(scene->getHeroListAvaterPath(Camp::CampBlue),
                            scene->getHeroListAvaterPath(Camp::CampRed));
    ec = new EventCenter(scene, menu, this);
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

