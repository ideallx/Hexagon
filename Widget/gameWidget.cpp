#include "gameWidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(!variableInitial() || !sceneInitial())
    {
        qDebug("initial error");
        return;
    }

    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
    endTurnAction = new QAction(tr("End Turn"), this);
    endTurnAction->setStatusTip(tr("End Current Turn"));
    ui->mainToolBar->addAction(endTurnAction);

    connect(scene, SIGNAL(changeStatusBar(QStringList)), this, SLOT(changeStatusInfo(QStringList)));

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
    gbi = new gameBackInfo(QString("C:/Users/xiang/Documents/GitHub/rsc/config.xml"));
    if(!gbi->isLoadSuccess())
    {
        QMessageBox::critical(this, tr("LYBNS"), tr("loading error"));
        return false;
    }
    qDebug("gbi load complete...");

    gc = new gameCoordinate(gbi);
    qDebug("gc load complete...");

    itemLabel = new QLabel(this);
    itemLabel->setFixedWidth(200);
    ui->statusBar->addWidget(itemLabel);

    coordinateLabel = new QLabel(this);
    coordinateLabel->setFixedWidth(400);
    ui->statusBar->addWidget(coordinateLabel);

    campLabel = new QLabel(this);
    campLabel->setFixedWidth(100);
    ui->statusBar->addWidget(campLabel);

    heroLabel = new QLabel(this);
    heroLabel->setFixedWidth(100);
    ui->statusBar->addWidget(heroLabel);

    return true;
}

bool MainWindow::sceneInitial()
{
    QList<heroFactory::ExternInfo> info;
    heroFactory::ExternInfo exInfo;

    exInfo.c = heroItem::camp_blue;
    exInfo.h = heroFactory::LeiShen;
    exInfo.p = QPoint(1, 20);
    info.append(exInfo);

    exInfo.c = heroItem::camp_red;
    exInfo.h = heroFactory::MieShaZhe;
    exInfo.p = QPoint(1, 1);
    info.append(exInfo);

    scene = new backScene(gbi, gc, info, this);
    ui->graphicsView->setScene(scene);
    menu = new gameMenu(ui->graphicsView);
    ec = new eventCenter(scene, menu, ui->graphicsView);
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
    /*
    QStringList str = in.split(';');
    statusLabel->setText(str[0]);
    if(str.size()>1)
        coordinateLabel->setText(tr("coordinate: ") + str[1]);
        */
}

void MainWindow::showMoveSphere()
{
    /*
    gc->clearMoveSphere();
    QList<QPoint> point = gc->listMoveSphere(gc->getCurHero()->getPoint(), gc->getCurHero()->getMoveSphere());
    QList<gameMapElement*> element = gc->getMapList();
    for(int i=0; i<point.size(); ++i)
    {
        element.at(gc->getBlockNumber(point[i]))->setPen(QPen(Qt::yellow, 5));
    }
    */
}

void MainWindow::showAttackSphere()
{
    /*
    gc->clearMoveSphere();
    gc->listMoveSphere(gc->getCurHero()->getPoint(), gc->getCurHero()->getAttackSphere());
    QList<QPoint> point = gc->getMovePoint();
    QList<gameMapElement*> element = gc->getMapList();
    for(int i=0; i<point.size(); ++i)
    {
        element.at(gc->getBlockNumber(point[i]))->setPen(QPen(Qt::red, 5));
    }
    */
}

void MainWindow::heroClickedSlot(QGraphicsSceneMouseEvent* e)
{
    menu->hideAllMenu();
    /*
    gc->restoreAllPen();
    gc->clearMoveSphere();

    if(gc->getCurHero() != static_cast<heroItem*>(this->sender()))
    {
        qDebug("not cur hero");
        emit heroClickedSignal(e);
    }
    else if(e->button() & Qt::LeftButton)
    {
        menu->showMenu(gameMenu::MENULIST, e->scenePos());
    }
    */
}

void MainWindow::elementClickedSlot(QGraphicsSceneMouseEvent *e)
{
    menu->hideAllMenu();
    /*
    gc->restoreAllPen();

    gc->setCurPoint(static_cast<gameMapElement*>(this->sender())->getPoint());

    if(gc->isPointAvailable(gc->getCurPoint()) && gc->getMovePoint().contains(gc->getCurPoint()))
    {
        if(e->button() == Qt::LeftButton)
        {
            emit elementClickedSignal(e);
        }
        else
        {
            restoreAll();
        }
    }*/

}
/*
void MainWindow::moveToPos(heroItem *hi, QPoint p)
{
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
*/
void MainWindow::restoreAll()
{
    menu->hideAllMenu();
}
