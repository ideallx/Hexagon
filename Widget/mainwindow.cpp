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
    stateMachineInitial();

    statusLabel = new QLabel(this);
    statusLabel->setText(tr("Test StatusBar Label"));
    statusLabel->setFixedWidth(300);

    campLabel = new QLabel(this);
    campLabel->setText(tr("Red Camp: Player 1"));
    campLabel->setFixedWidth(200);

    coordinateLabel = new QLabel(this);
    coordinateLabel->setText(tr("Coordinate: 1, 1"));
    coordinateLabel->setFixedWidth(200);

    heroLabel = new QLabel(this);
    heroLabel->setText(tr("Hero 1"));
    heroLabel->setFixedWidth(100);

    ui->statusBar->addWidget(statusLabel);
    ui->statusBar->addWidget(campLabel);
    ui->statusBar->addWidget(coordinateLabel);
    ui->statusBar->addWidget(heroLabel);



    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    ui->scrollArea->setWidget(widgetMain);
    qDebug("initial complete...");
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
        QMessageBox::critical(this, tr("LYBNS"), tr("loading error"));
        return false;
    }
    qDebug("gbi load complete...");

    gc = new gameCoordinate(QPoint(0, 0), gbi);
    qDebug("gc load complete...");

    endTurnAction = new QAction(tr("End Turn"), this);
    endTurnAction->setStatusTip(tr("End Current Turn"));
    ui->mainToolBar->addAction(endTurnAction);

    return true;
}

bool MainWindow::sceneInitial()
{
    scene = new backScene(this);
    scene->setSceneRect(gbi->getPixmap().rect());

    widgetMain = new backview(scene, gbi->getLineLength());
    widgetMain->setBackgroundBrush(QBrush(gbi->getPixmap()));
    widgetMain->setParent(this);
    menu = new gameMenu(widgetMain);
    qDebug("backView load complete...");

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
            gameMapElement *mapItem = new gameMapElement(gbi->getLineLength(), element[i+j*wid], QPoint(i, j), gbi->getConfigDir());
            gc->addmapElement(mapItem);  // gc->add should be deleted later...
            mapItem->hide();
            if(gc->isPointAvailable(QPoint(i, j)))
            {
                mapItem->setPos(gc->getBeginPosWithCoo(QPoint(i, j)));
                //mapItem->setZValue((i+j)/(hei*wid)); should be done later
                mapItem->show();
                scene->addItem(mapItem);
                connect(mapItem, SIGNAL(statusInfoChanged(QString)), this, SLOT(changeStatusInfo(QString)));
                connect(mapItem, SIGNAL(elementClicked(QGraphicsSceneMouseEvent*)), this, SLOT(elementClickedSlot(QGraphicsSceneMouseEvent*)));
            }
        }
    }

    cardItem* ci = new cardItem(gbi->getCardRect(), gbi->getConfigDir());
    scene->addItem(ci);
    //gc->addCard(ci);
    ci->setPos(gbi->getBackCardLeft());
    qDebug("map load complete...");

    heroItem *item = new heroItem(gbi->getLineLength()*1.6, gbi->getConfigDir());
    item->setBrush(QPixmap(gbi->getConfigDir() + "hero1.png").scaledToWidth(gbi->getLineLength()*1.6));
    item->setPos(gc->getBeginPosOfHero(QPoint(1, 1)));
    item->setHeroProperty(heroItem::camp_red, heroItem::sex_female, 2, 4);
    connect(item, SIGNAL(changeStatus(QString)), this, SLOT(changeStatusInfo(QString)));
    connect(item, SIGNAL(mouseClicked(QGraphicsSceneMouseEvent*)), this, SLOT(heroClickedSlot(QGraphicsSceneMouseEvent*)));
    gc->addHero(item);
    scene->addItem(item);


    heroItem *item2 = new heroItem(gbi->getLineLength()*1.6, gbi->getConfigDir());
    item2->setBrush(QPixmap(gbi->getConfigDir() + "hero2.png").scaledToWidth(gbi->getLineLength()*1.6));
    item2->setPos(gc->getBeginPosOfHero(QPoint(2, 20)));
    item2->setHeroProperty(heroItem::camp_blue, heroItem::sex_male, 1, 3);
    connect(item2, SIGNAL(changeStatus(QString)), this, SLOT(changeStatusInfo(QString)));
    connect(item2, SIGNAL(mouseClicked(QGraphicsSceneMouseEvent*)), this, SLOT(heroClickedSlot(QGraphicsSceneMouseEvent*)));
    gc->addHero(item2);
    scene->addItem(item2);


    qDebug("hero load complete...");

    gc->setCurHero(item);
    gc->getCurHero()->setPoint(QPoint(1, 1));

    return true;
}


void MainWindow::stateMachineInitial()
{
    stm = new QStateMachine();
    freeState = new QState();

    moveState = new QState();
    {
        moveComplete = new QState(moveState);
    }

    attackAndAbility = new QState(QState::ParallelStates);
    {
        attackState = new QState(attackAndAbility);
        {
            attackComplete = new QState(attackState);
        }
        abilityState = new QState(attackAndAbility);
        {
            abilityComplete = new QState(abilityState);
        }
    }

    finalState = new QFinalState();



    freeState->addTransition(menu, SIGNAL(moveClicked()), moveState);
    freeState->addTransition(menu, SIGNAL(attackClicked()), attackAndAbility);
    freeState->addTransition(menu, SIGNAL(abilityClicked()), attackAndAbility);
    freeState->addTransition(endTurnAction, SIGNAL(triggered()), freeState);

    moveState->addTransition(menu, SIGNAL(attackClicked()), attackState);
    moveState->addTransition(endTurnAction, SIGNAL(triggered()), freeState);
    moveComplete->addTransition(menu, SIGNAL(attackClicked()), attackState);
    moveComplete->addTransition(menu, SIGNAL(abilityClicked()), abilityState);
    moveComplete->addTransition(endTurnAction, SIGNAL(triggered()), freeState);



    attackState->addTransition(this, SIGNAL(heroClickedSignal(QGraphicsSceneMouseEvent*)), attackComplete);
    attackComplete->addTransition(menu, SIGNAL(abilityClicked()), abilityState);
    abilityState->addTransition(this, SIGNAL(elementClickedSignal(QGraphicsSceneMouseEvent*)), abilityComplete);
    abilityComplete->addTransition(menu, SIGNAL(attackClicked()), attackState);
    attackAndAbility->addTransition(endTurnAction, SIGNAL(triggered()), freeState);


    freeState->assignProperty(menu, "isMoveAble", true);
    moveComplete->assignProperty(menu, "isMoveAble", false);
    attackComplete->assignProperty(menu, "isMoveAble", false);
    attackComplete->assignProperty(menu, "isAttackAble", false);
    attackAndAbility->assignProperty(menu, "isMoveAble", false);
    abilityComplete->assignProperty(menu, "isAbilityAble", false);



    QAbstractTransition *t1 = moveState->addTransition(this, SIGNAL(elementClickedSignal(QGraphicsSceneMouseEvent*)), moveComplete);
    QSequentialAnimationGroup *animation1SubGroup = new QSequentialAnimationGroup;
    animation1SubGroup->addPause(100);
    animation1SubGroup->addAnimation(new QPropertyAnimation(gc->getCurHero(), "pos"));
    t1->addAnimation(animation1SubGroup);

    stm->addState(freeState);
    stm->addState(moveState);
    stm->addState(attackAndAbility);
    stm->addState(finalState);

    stm->setInitialState(freeState);
    stm->start();

    qDebug("stm load complete...");
}

void MainWindow::changeStatusInfo(QString in)
{
    QStringList str = in.split(';');
    statusLabel->setText(str[0]);
    if(str.size()>1)
        coordinateLabel->setText(tr("coordinate: ") + str[1]);
}

void MainWindow::showMoveSphere()
{
    gc->clearMoveSphere();
    QList<QPoint> point = gc->listMoveSphere(gc->getCurHero()->getPoint(), gc->getCurHero()->getMoveSphere());
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

void MainWindow::heroClickedSlot(QGraphicsSceneMouseEvent* e)
{
    menu->hideAllMenu();
    gc->restoreAllPen();
    gc->clearMoveSphere();

    gc->setCurHero(static_cast<heroItem*>(this->sender()));

    if(e->button() & Qt::LeftButton)
    {
        menu->showMenu(gameMenu::MENULIST, e->scenePos());
    }
    emit heroClickedSignal(e);
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
