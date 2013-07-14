#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Now the widgetMain is in leading role
    ui->setupUi(this);

    if(!variableInitial() || !sceneInitial())
    {
        qDebug("initial error");
        return;
    }

    statusLabel = new QLabel(this);
    statusLabel->setText(tr("Test StatusBar Label"));
    statusLabel->setFixedWidth(300);

    campLabel = new QLabel(this);
    campLabel->setText(tr("Red Camp: Player 1"));
    campLabel->setFixedWidth(200);

    coordinateLabel = new QLabel(this);
    coordinateLabel->setText("Coordinate: 1, 1");
    coordinateLabel->setFixedWidth(200);

    heroLabel = new QLabel(this);
    heroLabel->setText(tr("Hero 1"));
    heroLabel->setFixedWidth(100);

    ui->statusBar->addWidget(statusLabel);
    ui->statusBar->addWidget(campLabel);
    ui->statusBar->addWidget(coordinateLabel);
    ui->statusBar->addWidget(heroLabel);

    endTurnAction = new QAction(tr("End Turn"), this);
    endTurnAction->setStatusTip(tr("End Current Turn"));
    ui->mainToolBar->addAction(endTurnAction);

    heroItem *item = new heroItem(Qt::yellow, lineLength*1.6);
    connect(item, SIGNAL(changeStatus(QString)), this, SLOT(changeStatusInfo(QString)));
    item->setPos(gc->getBeginPosWithCoo(QPoint(1, 1)) += QPoint(0.2*lineLength, 0.06*lineLength));
    scene->addItem(item);
    item->installEventFilter(this);
    qDebug("hero load complete...");

    gc->setCurHero(item);
    gc->getCurHero()->setPoint(QPoint(1, 1));

    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    ui->scrollArea->setWidget(widgetMain);
    connect(item, SIGNAL(mouseClicked(QGraphicsSceneMouseEvent*)), this, SLOT(heroClicked(QGraphicsSceneMouseEvent*)));
    stateMachineInitial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::variableInitial()
{

    gbi = new gameBackInfo(QString("F:/KuGou/vv/Resource/SkinDefault/config.xml"));
    if(!gbi->isLoadSuccess())
    {
        QMessageBox::critical(this, "LYBNS", "loading error");
        return false;
    }
    qDebug("gbi load complete...");

    gc = new gameCoordinate(QPoint(0, 0), gbi);
    lineLength = gbi->getLineLength();
    qDebug("gc load complete...");

    return true;
}

bool MainWindow::sceneInitial()
{
    scene = new backScene(this);
    scene->setSceneRect(gbi->getPixmap().rect());
    widgetMain = new backview(scene, lineLength, gbi);
    qDebug("backView load complete...");
    widgetMain->setParent(this);

    menu = new gameMenu(widgetMain);
    connect(menu, SIGNAL(moveClicked()), this, SLOT(showMoveSphere()));
    connect(menu, SIGNAL(attackClicked()), this, SLOT(showAttackSphere()));
    connect(menu, SIGNAL(cancelClicked()), this, SLOT(restoreAll()));

    qDebug("menu load complete...");

    QVector<char> element = gbi->getMapElement();
    int wid = gbi->getWidthCount();
    int hei = gbi->getHeightCount();

    for(int j=0; j<hei; j++)
    {
        for(int i=0; i<wid; i++)
        {
            gameMapElement *mapItem = new gameMapElement(element[i+j*wid], QPoint(i, j));
            gc->addmapElement(mapItem);
            mapItem->hide();
            if(gc->isPointAvailable(QPoint(i, j)))
            {
                mapItem->setPos(gc->getBeginPosWithCoo(QPoint(i, j)));
                scene->addItem(mapItem);
                connect(mapItem, SIGNAL(statusInfoChanged(QString)), this, SLOT(changeStatusInfo(QString)));
                connect(mapItem, SIGNAL(elementClicked(QGraphicsSceneMouseEvent*)), this, SLOT(elementClickedSlot(QGraphicsSceneMouseEvent*)));
                mapItem->show();
            }
        }
    }

    cardItem* ci = new cardItem(gbi->getCardRect());
    scene->addItem(ci);
    ci->setPos(gbi->getBackCardLeft());
    qDebug("map load complete...");
    return true;
}

void MainWindow::stateMachineInitial()
{
    stm = new QStateMachine();
    freeState = new QState();
    moveState = new QState();
    moveComplete = new QState();
    attackState = new QState();
    attackComplete = new QState();
    abilityState = new QState();
    abilityComplete = new QState();

    freeState->addTransition(menu, SIGNAL(moveClicked()), moveState);
    freeState->addTransition(menu, SIGNAL(attackClicked()), attackState);
    freeState->addTransition(menu, SIGNAL(abilityClicked()), abilityState);
    freeState->assignProperty(menu, "isMoveAble", true);
    freeState->assignProperty(menu, "isAttackAble", true);
    freeState->assignProperty(menu, "isAbilityAble", true);

    QAbstractTransition *t1 = moveState->addTransition(this, SIGNAL(elementClickedSignal(QGraphicsSceneMouseEvent*)), moveComplete);
    QSequentialAnimationGroup *animation1SubGroup = new QSequentialAnimationGroup;
    animation1SubGroup->addPause(100);
    animation1SubGroup->addAnimation(new QPropertyAnimation(gc->getCurHero(), "pos"));
    t1->addAnimation(animation1SubGroup);


    moveState->addTransition(menu, SIGNAL(attackClicked()), attackState);
    moveComplete->addTransition(menu, SIGNAL(attackClicked()), attackState);
    moveComplete->assignProperty(menu, "isMoveAble", false);

    attackState->addTransition(this, SIGNAL(elementClickedSignal(QGraphicsSceneMouseEvent*)), attackComplete);
    attackComplete->addTransition(menu, SIGNAL(abilityClicked()), abilityState);
    attackComplete->assignProperty(menu, "isMoveAble", false);
    attackComplete->assignProperty(menu, "isAttackAble", false);

    abilityState->addTransition(this, SIGNAL(elementClickedSignal(QGraphicsSceneMouseEvent*)), abilityComplete);
    abilityComplete->addTransition(menu, SIGNAL(attackClicked()), attackState);
    attackComplete->assignProperty(menu, "isMoveAble", false);
    abilityComplete->assignProperty(menu, "isAbilityAble", false);

    moveComplete->addTransition(ui->actionEndTurn, SIGNAL(triggered()), freeState);
    attackComplete->addTransition(ui->actionEndTurn, SIGNAL(triggered()), freeState);
    abilityComplete->addTransition(ui->actionEndTurn, SIGNAL(triggered()), freeState);


    moveComplete->addTransition(endTurnAction, SIGNAL(triggered()), freeState);
    moveState->addTransition(endTurnAction, SIGNAL(triggered()), freeState);
    attackComplete->addTransition(endTurnAction, SIGNAL(triggered()), freeState);
    attackState->addTransition(endTurnAction, SIGNAL(triggered()), freeState);
    abilityComplete->addTransition(endTurnAction, SIGNAL(triggered()), freeState);
    abilityState->addTransition(endTurnAction, SIGNAL(triggered()), freeState);


    stm->addState(freeState);
    stm->addState(moveState);
    stm->addState(moveComplete);
    stm->addState(attackState);
    stm->addState(attackComplete);
    stm->addState(abilityState);
    stm->addState(abilityComplete);

    stm->setInitialState(freeState);
    stm->start();

    qDebug("stm load complete...");
}

void MainWindow::changeStatusInfo(QString in)
{
    QStringList str = in.split(';');
    statusLabel->setText(str[0]);
    if(str.size()>1)
        coordinateLabel->setText(str[1]);
}

void MainWindow::showMoveSphere()
{
    gc->clearMoveSphere();
    gc->listMoveSphere(gc->getCurHero()->getPoint(), gc->getCurHero()->getMoveSphere());
    QList<QPoint> point = gc->getMovePoint();
    QList<gameMapElement*> element = gc->getMapList();
    for(int i=0; i<point.size(); ++i)
    {
        element.at(gc->getBlockNumber(point[i]))->setPen(QPen(Qt::yellow, 5));
    }
}

void MainWindow::showAttackSphere()
{

    gc->clearMoveSphere();
    gc->listMoveSphere(gc->getCurHero()->getPoint(), gc->getCurHero()->getAttackSphere());
    QList<QPoint> point = gc->getMovePoint();
    QList<gameMapElement*> element = gc->getMapList();
    for(int i=0; i<point.size(); ++i)
    {
        element.at(gc->getBlockNumber(point[i]))->setPen(QPen(Qt::red, 5));
    }

}

void MainWindow::heroClicked(QGraphicsSceneMouseEvent* e)
{
    menu->hideAllMenu();
    gc->restoreAllPen();
    gc->clearMoveSphere();

    if(e->button() & Qt::LeftButton)
    {
        menu->showMenu(gameMenu::MENULIST, e->scenePos());
    }
}

void MainWindow::elementClickedSlot(QGraphicsSceneMouseEvent *e)
{
    menu->hideAllMenu();
    gc->restoreAllPen();

    gc->setCurPoint(static_cast<gameMapElement*>(this->sender())->getPoint());

    if(gc->isPointAvailable(gc->getCurPoint()) && gc->getMovePoint().contains(gc->getCurPoint()))
    {
        moveComplete->assignProperty(gc->getCurHero(), "point", gc->getCurPoint());
        moveComplete->assignProperty(gc->getCurHero(), "pos", gc->getBeginPosOfHero(gc->getCurPoint()));
        if(e->button() == Qt::LeftButton)
        {
            emit elementClickedSignal(e);
        }
        else
        {
            restoreAll();
        }
    }

}

void MainWindow::moveToPos(heroItem *hi, QPoint p)
{

    QGraphicsItemAnimation* gia = gc->getGia();
    QTimeLine *giaTimer = gc->getGiaTimer();

    QPointF oldPos = hi->scenePos();
    QPointF newPos = gc->getBeginPosOfHero(p);

    qDebug("%f, %f", oldPos.x(), oldPos.y());
    qDebug("%f, %f", newPos.x(), newPos.y());

    if(gc->isPointAvailable(p))
    {
        gc->setCurPoint(p);
        gia->setItem(hi);
        //giaTimer->setFrameRange(0, 100);
        gia->setTimeLine(giaTimer);

        double frame = giaTimer->duration()*60/1000;

        double x = (newPos.x() - oldPos.x())/frame;
        double y = (newPos.y() - oldPos.y())/frame;

        for(int i=0; i<=frame; ++i)
            gia->setPosAt(i/frame, oldPos+QPoint(x*i, y*i));

        giaTimer->start();
    }
}

void MainWindow::restoreAll()
{
    menu->hideAllMenu();
    gc->restoreAllPen();
    gc->clearMoveSphere();
}
