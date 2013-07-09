#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Now the testWidget2 is in leading role
    ui->setupUi(this);

    statusContent = new QLabel(this);
    statusContent->setText("Test StatusBar Label");
    ui->statusBar->addWidget(statusContent);

    testWidget = new WidgetMainTest();
    gameWidget = new WidgetMain();
    //qDebug("%d, %d", gameWidget->sizeHint().width(), gameWidget->sizeHint().height());

    QGraphicsScene *scene = new QGraphicsScene(0, 0, gameWidget->sizeHint().width(), gameWidget->sizeHint().height());
    scene->addWidget(gameWidget);
    testWidget2 = new backview(scene, (int)(gameWidget->getLineLength()*1.6)); //sqrt 3 and margin
    //qDebug("%d, %d", testWidget2->sizeHint().width(), testWidget2->sizeHint().height());
    //qDebug("%d, %d", testWidget2->size().width(), testWidget2->size().height());

    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
    connect(ui->actionGame, SIGNAL(triggered(bool)), this, SLOT(changeViewGame(bool)));
    connect(ui->actionTest, SIGNAL(triggered(bool)), this, SLOT(changeViewTest(bool)));
    connect(ui->actionTest2, SIGNAL(triggered(bool)), this, SLOT(changeViewTest2(bool)));
    //connect(gameWidget, SIGNAL(parentStatusChanged(QString)), this, SLOT(changeStatusInfo(QString)));

    ui->scrollArea->setWidget(testWidget2);
    globol::menu = new gameMenu(testWidget2);

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
