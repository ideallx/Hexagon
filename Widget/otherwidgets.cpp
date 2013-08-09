#include "otherwidgets.h"
#include "ui_modechoose.h"

modeChooseWidget::modeChooseWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modeChoose)
{
    ui->setupUi(this);
}
