#include "otherwidgets.h"
#include "ui_modechoose.h"
#include "gameWidget.h"
#include "ui_gameSetting.h"

#include <QDebug>

modeChooseWidget::modeChooseWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modeChoose),
    uig(new Ui::gameSetting),
    uie(new Ui::enviroSetting)
{
    ui->setupUi(this);
    ui->singleGame->setFixedSize(100, 30);
    ui->lanGame->setFixedSize(100, 30);
    ui->replay->setFixedSize(100, 30);
    ui->settings->setFixedSize(100, 30);
    ui->cardsView->setFixedSize(100, 30);
    ui->mapsView->setFixedSize(100, 30);
    ui->herosView->setFixedSize(100, 30);
    ui->about->setFixedSize(100, 30);

    qdlg = new QDialog(this);
    qdlg->hide();
}

void modeChooseWidget::on_singleGame_clicked()
{
//    delete qdlg;
//    qdlg = new QDialog(this);
//    uig->setupUi(qdlg);
//    qdlg->show();
    delete this;
    MainWindow *a = new MainWindow;
    a->show();
}

void modeChooseWidget::on_settings_clicked()
{
    delete qdlg;
    qdlg = new QDialog(this);
    uie->setupUi(qdlg);
    qdlg->show();
}

