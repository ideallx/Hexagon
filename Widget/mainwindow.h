#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "backview.h"
#include "../Game/heroitem.h"
#include "../Game/gamemenu.h"
#include "../Game/gamecoordinate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void moveToPos(heroItem*, QPoint);
    QStateMachine *stm;
    QState *freeState;
    QState *moveState;
    QState *moveStateAssure;
    QState *attackState;


    backview *widgetMain;
    gameMenu* menu;
    QGraphicsScene *scene;
    gameBackInfo* gbi;
    gameCoordinate *gc;
    QLabel *statusLabel;

    Ui::MainWindow *ui;

private slots:
    void changeStatusInfo(QString);
    void showMoveSphere();
    void heroClicked(QGraphicsSceneMouseEvent*);
    void elementClicked(QGraphicsSceneMouseEvent*);
};

#endif // MAINWINDOW_H
