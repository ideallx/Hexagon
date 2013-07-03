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

#ifdef debugWidget
    WidgetMainTest *dd = new WidgetMainTest();
    qDebug("fdsf");
#else
    setGeometry(400, 150, 1050, 850);
    WidgetMain *dd = new WidgetMain();
    setMaximumSize(dd->getMaxSizeHint());
#endif
    ui->scrollArea->setWidget(dd);

    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
    connect(dd, SIGNAL(parentStatusChanged(QString)), this, SLOT(changeStatusInfo(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStatusInfo(QString in)
{
    statusContent->setText(in);
}