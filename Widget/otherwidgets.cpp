#include <QDebug>
#include "otherwidgets.h"
#include "ui_modechoose.h"
#include "gameWidget.h"

const int ModeIconWidth = 100;
const int ModeIconHeight = 30;

ModeChooseWidget::ModeChooseWidget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::modeChoose) {
    ui->setupUi(this);
    ui->singleGame->setFixedSize(ModeIconWidth, ModeIconHeight);
    ui->lanGame->setFixedSize(ModeIconWidth, ModeIconHeight);
    ui->replay->setFixedSize(ModeIconWidth, ModeIconHeight);
    ui->settings->setFixedSize(ModeIconWidth, ModeIconHeight);
    ui->cardsView->setFixedSize(ModeIconWidth, ModeIconHeight);
    ui->mapsView->setFixedSize(ModeIconWidth, ModeIconHeight);
    ui->herosView->setFixedSize(ModeIconWidth, ModeIconHeight);
    ui->about->setFixedSize(ModeIconWidth, ModeIconHeight);
}

ModeChooseWidget::~ModeChooseWidget() {
    delete ui;
}


void ModeChooseWidget::on_settings_clicked() {
    delete qdlg;
    qdlg = new QDialog(this);
    uie->setupUi(qdlg);
    qdlg->show();
}

