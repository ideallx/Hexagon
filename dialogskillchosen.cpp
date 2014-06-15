#include "dialogskillchosen.h"
#include "ui_dialogskillchosen.h"

DialogSkillChosen::DialogSkillChosen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSkillChosen)
{
    ui->setupUi(this);
}

DialogSkillChosen::~DialogSkillChosen()
{
    delete ui;
}
