#ifndef OTHERWIDGETS_H
#define OTHERWIDGETS_H

#include <QWidget>
#include "ui_modechoose.h"


class otherWidgets : public QMainWindow
{
    Q_OBJECT
public:
    explicit otherWidgets(QWidget *parent = 0);

private:
    Ui::MainWindow *ui;
    
signals:
    
public slots:
    
};

#endif // OTHERWIDGETS_H
