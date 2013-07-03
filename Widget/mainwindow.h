#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#define debugWidget

#include <QMainWindow>
#include <QtWidgets>
#ifdef debugWidget
#include "widgetmaintest.h"
#else
#include "widgetmain.h"
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void changeStatusInfo(QString);
    
private:
    Ui::MainWindow *ui;
    QLabel *statusContent;
};

#endif // MAINWINDOW_H
