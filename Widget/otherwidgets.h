#ifndef OTHERWIDGETS_H
#define OTHERWIDGETS_H

#include <QWidget>
#include "ui_modechoose.h"


class modeChooseWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit modeChooseWidget(QWidget *parent = 0);

private:
    Ui::modeChoose *ui;
    
signals:
    
public slots:
    
};

#endif // OTHERWIDGETS_H
