#include "otherwidgets.h"
#include "ui_modechoose.h"

otherWidgets::otherWidgets(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
