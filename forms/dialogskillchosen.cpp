#include <QDebug>
#include <QMessageBox>
#include "dialogskillchosen.h"
#include "ui_dialogskillchosen.h"
#include "picturelabel.h"

DialogSkillChosen::DialogSkillChosen(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSkillChosen),
    chosenNum(0) {
    ui->setupUi(this);
    int commonWidth = 300;
    this->setWindowTitle("Choose Your Hero Skills");

    labels.append(ui->label);
    labels.append(ui->label_2);
    labels.append(ui->label_3);

    checkboxs.append(ui->checkSkill1);
    checkboxs.append(ui->checkSkill2);
    checkboxs.append(ui->checkSkill3);

    qsm = new QSignalMapper(this);
    connect(qsm, SIGNAL(mapped(int)),
            this, SLOT(labelClicked(int)));

    for (int i = 0; i < 3; i++) {
        labels[i]->setPixmap(QPixmap(QString("%1S%2.jpg").arg(path).arg(i + 1))
                             .scaledToWidth(commonWidth,
                                            Qt::SmoothTransformation));
        connect(labels[i], SIGNAL(clicked()),
                qsm, SLOT(map()));
        qsm->setMapping(labels[i], i);
    }

}

DialogSkillChosen::~DialogSkillChosen()
{
    delete ui;
}

void DialogSkillChosen::on_checkSkill1_clicked(bool checked)
{
    Q_UNUSED(checked);
    checkCheckBoxes();
}

void DialogSkillChosen::on_checkSkill2_clicked(bool checked)
{
    Q_UNUSED(checked);
    checkCheckBoxes();
}

void DialogSkillChosen::on_checkSkill3_clicked(bool checked)
{
    Q_UNUSED(checked);
    checkCheckBoxes();
}

void DialogSkillChosen::on_buttonBox_accepted()
{
    int result = 0;
    if (ui->checkSkill1->isChecked())
        result |= 0x01;
    if (ui->checkSkill2->isChecked())
        result |= 0x02;
    if (ui->checkSkill3->isChecked())
        result |= 0x04;

    done(result);
}

void DialogSkillChosen::checkCheckBoxes() {
    QList<QCheckBox*> notChecked;
    for (int i = 0; i < 3; i++) {
        if (!checkboxs[i]->isChecked()) {
            notChecked.append(checkboxs[i]);
        }
    }
    if (notChecked.size() == 0) {
        throw QString("All Skills are available");
    } else if (notChecked.size() == 1) {
        notChecked[0]->setEnabled(false);
        ui->buttonBox->setEnabled(true);
    } else {
        ui->buttonBox->setEnabled(false);
        foreach (QCheckBox* cb, notChecked)
            cb->setEnabled(true);
    }
}

void DialogSkillChosen::labelClicked(int n) {
    QCheckBox* cb = checkboxs[n];
    if (cb->isEnabled()) {
        cb->setChecked(!cb->isChecked());
        checkCheckBoxes();
    }
}

// 3 5 6
void DialogSkillChosen::on_buttonBox_rejected()
{
    switch (rand() % 3) {
    case 0:
        done(3); break;
    case 1:
        done(5); break;
    case 2:
        done(6); break;
    default:        // if you can do this
        done(7); break;
    }
}

void DialogSkillChosen::on_DialogSkillChosen_rejected()
{
    on_buttonBox_rejected();
}
