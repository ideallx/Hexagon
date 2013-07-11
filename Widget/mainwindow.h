#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "widgetmaintest.h"
#include "widgetmain.h"
#include "../Game/heroitem.h"
#include "../Game/gamemenu.h"
#include "backview.h"
#include "../commonvariable.h"

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
    void changeViewTest2(bool);
    
private:
    WidgetMainTest* testWidget;
    WidgetMain* gameWidget;
    Ui::MainWindow *ui;
    QGraphicsView *testWidget2;
    gameMenu* menu;
};

#endif // MAINWINDOW_H
