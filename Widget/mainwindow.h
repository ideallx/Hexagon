#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "widgetmaintest.h"
#include "widgetmain.h"

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
    void changeViewGame(bool);
    void changeViewTest(bool);
    
private:
    WidgetMainTest* testWidget;
    WidgetMain* gameWidget;
    Ui::MainWindow *ui;
    QLabel *statusContent;
};

#endif // MAINWINDOW_H
