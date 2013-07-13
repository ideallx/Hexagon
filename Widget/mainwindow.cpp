#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Now the widgetMain is in leading role
    ui->setupUi(this);
    statusLabel = new QLabel(this);
    statusLabel->setText("Test StatusBar Label");
    ui->statusBar->addWidget(statusLabel);

    gbi = new gameBackInfo(QString("F:/KuGou/vv/Resource/SkinDefault/config.xml"));
    gc = new gameCoordinate(QPoint(0, 0), gbi);

    int lineLength = gbi->getLineLength();

    scene = new QGraphicsScene(gbi->getPixmap().rect());
    widgetMain = new backview(scene, lineLength, gbi);
    widgetMain->setParent(this);
    menu = new gameMenu(widgetMain);

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
                connect(mapItem, SIGNAL(elementClicked(QGraphicsSceneMouseEvent*)), this, SLOT(elementClicked(QGraphicsSceneMouseEvent*)));
                mapItem->show();
            }
        }
    }

    heroItem *item = new heroItem(Qt::yellow, lineLength*1.6);
    item->setPos(QPoint(1, 1));
    connect(item, SIGNAL(changeStatus(QString)), this, SLOT(changeStatusInfo(QString)));
    item->setPos(gc->getBeginPosWithCoo(QPoint(1, 1)) += QPoint(0.2*lineLength, 0.06*lineLength));
    scene->addItem(item);

    gc->setCurHero(item);
    gc->getCurHero()->setPoint(QPoint(1, 1));

    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    ui->scrollArea->setWidget(widgetMain);
    connect(menu, SIGNAL(moveClicked()), this, SLOT(showMoveSphere()));
    connect(item, SIGNAL(mouseClicked(QGraphicsSceneMouseEvent*)), this, SLOT(heroClicked(QGraphicsSceneMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStatusInfo(QString in)
{
    statusLabel->setText(in);
}

void MainWindow::showMoveSphere()
{
    gc->listMoveSphere(gc->getCurHero()->getCurPos(), gc->getCurHero()->getMoveSphere());
    QList<QPoint> point = gc->getMoveSphere();
    QList<gameMapElement*> element = gc->getMapList();
    for(int i=0; i<point.size(); ++i)
    {
        qDebug("%d %d", point[i].x(), point[i].y());
        element.at(gc->getBlockNumber(point[i]))->setPen(QPen(Qt::yellow, 5));
    }
}

void MainWindow::heroClicked(QGraphicsSceneMouseEvent* e)
{
    menu->hideAllMenu();
    gc->restoreAllPen();
    if(e->button() & Qt::LeftButton)
    {
        menu->showMenu(gameMenu::MENULIST, e->scenePos());
    }
}

void MainWindow::elementClicked(QGraphicsSceneMouseEvent *e)
{
    menu->hideAllMenu();
    gc->restoreAllPen();
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
