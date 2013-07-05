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

    ui->scrollArea->setWidget(gameWidget);

    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
    connect(ui->actionGame, SIGNAL(triggered(bool)), this, SLOT(changeViewGame(bool)));
    connect(ui->actionTest, SIGNAL(triggered(bool)), this, SLOT(changeViewTest(bool)));
    connect(gameWidget, SIGNAL(parentStatusChanged(QString)), this, SLOT(changeStatusInfo(QString)));
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
        ui->scrollArea->setWidget(testWidget);
    }

}
