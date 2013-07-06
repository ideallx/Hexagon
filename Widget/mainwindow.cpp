#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusContent = new QLabel(this);
    statusContent->setText("Test StatusBar Label");
    ui->statusBar->addWidget(statusContent);

    setGeometry(400, 150, 1050, 850);

    testWidget = new WidgetMainTest();
    gameWidget = new WidgetMain();

    setMaximumSize(gameWidget->getMaxSizeHint());

    //ui->scrollArea->setWidget(gameWidget);

    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
    connect(ui->actionGame, SIGNAL(triggered(bool)), this, SLOT(changeViewGame(bool)));
    connect(ui->actionTest, SIGNAL(triggered(bool)), this, SLOT(changeViewTest(bool)));
    connect(ui->actionTest2, SIGNAL(triggered(bool)), this, SLOT(changeViewTest2(bool)));
    connect(gameWidget, SIGNAL(parentStatusChanged(QString)), this, SLOT(changeStatusInfo(QString)));


    QGraphicsItem *item = new heroItem(QColor("red"), gameWidget->getLineLength());
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 700, 700);
    scene->addItem(item);
    scene->addText("fuck all");
    testWidget2 = new QGraphicsView(scene);
    QBrush b(QColor("darkGray"));
    testWidget2->setBackgroundBrush(b);
//    testWidget2->setBackgroundBrush(QBrush(QColor("red")));
//    testWidget2->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Animated Tiles"));
//    testWidget2->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    testWidget2->setCacheMode(QGraphicsView::CacheBackground);
//    testWidget2->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    ui->scrollArea->setWidget(gameWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStatusInfo(QString in)
{
    statusContent->setText(in);
}

void MainWindow::changeViewGame(bool ok)
{
    ui->actionGame->setChecked(ok);
    if(ok == false)
    {
        ui->scrollArea->takeWidget();
    }
    else
    {
        changeViewTest(false);
        changeViewTest2(false);
        ui->scrollArea->setWidget(gameWidget);
    }

}

void MainWindow::changeViewTest(bool ok)
{
    ui->actionTest->setChecked(ok);
    if(ok == false)
    {
        ui->scrollArea->takeWidget();
    }
    else
    {
        changeViewGame(false);
        changeViewTest2(false);
        ui->scrollArea->setWidget(testWidget);
    }

}

void MainWindow::changeViewTest2(bool ok)
{
    ui->actionTest2->setChecked(ok);
    if(ok == false)
    {
        ui->scrollArea->takeWidget();
    }
    else
    {
        changeViewGame(false);
        changeViewTest(false);
        ui->scrollArea->setWidget(testWidget2);
    }

}
