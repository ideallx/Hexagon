#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WidgetMain *dd = new WidgetMain;
    ui->scrollArea->setWidget(dd);
    QLabel *statusContent = new QLabel(this);
    statusContent->setText("Test StatusBar Label");
    ui->statusBar->addWidget(statusContent);
    connect(ui->actionQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
