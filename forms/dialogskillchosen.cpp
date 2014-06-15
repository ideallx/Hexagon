#include <QDebug>
#include <QMessageBox>
#include "dialogskillchosen.h"
#include "ui_dialogskillchosen.h"

DialogSkillChosen::DialogSkillChosen(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSkillChosen),
    chosenNum(0) {
    ui->setupUi(this);
    this->setWindowTitle("Choose Your Hero Skills");
    ui->label->setPixmap(QString("%1S1.jpg").arg(path));
    ui->label_2->setPixmap(QString("%1S2.jpg").arg(path));
    ui->label_3->setPixmap(QString("%1S3.jpg").arg(path));
    qDebug() << QString("%1S1.jpg");
}

DialogSkillChosen::~DialogSkillChosen()
{
    delete ui;
}

void DialogSkillChosen::on_checkSkill1_clicked(bool checked)
{
    if (checked) {
        chosenNum++;
        if (ui->checkSkill2->isChecked())
            ui->checkSkill3->setEnabled(false);
        else if (ui->checkSkill3->isChecked())
            ui->checkSkill2->setEnabled(false);
    } else {
        chosenNum--;
        ui->checkSkill2->setEnabled(true);
        ui->checkSkill3->setEnabled(true);
    }
}

void DialogSkillChosen::on_checkSkill2_clicked(bool checked)
{
    if (checked) {
        chosenNum++;
        if (ui->checkSkill1->isChecked())
            ui->checkSkill3->setEnabled(false);
        else if (ui->checkSkill3->isChecked())
            ui->checkSkill1->setEnabled(false);
    } else {
        chosenNum--;
        ui->checkSkill1->setEnabled(true);
        ui->checkSkill3->setEnabled(true);
    }
}

void DialogSkillChosen::on_checkSkill3_clicked(bool checked)
{
    if (checked) {
        chosenNum++;
        if (ui->checkSkill1->isChecked())
            ui->checkSkill2->setEnabled(false);
        else if (ui->checkSkill2->isChecked())
            ui->checkSkill1->setEnabled(false);
    } else {
        chosenNum--;
        ui->checkSkill1->setEnabled(true);
        ui->checkSkill2->setEnabled(true);
    }
}

void DialogSkillChosen::on_buttonBox_accepted()
{
    if (2 != chosenNum) {   // every hero 2 skills
        QMessageBox::warning(NULL, tr("Choose Screen"), "Please Choose 2 Skills");
        return;
    }
    int result = 0;
    if (ui->checkSkill1->isChecked())
        result |= 0x01;
    if (ui->checkSkill2->isChecked())
        result |= 0x02;
    if (ui->checkSkill3->isChecked())
        result |= 0x04;

    done(result);
}
