#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "backview.h"
#include "backscene.h"
#include "../Game/heroitem.h"
#include "../Game/gamemenu.h"
#include "../Game/gamecoordinate.h"
#include "../Game/carditem.h"

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
    bool variableInitial();
    bool sceneInitial();
    void stateMachineInitial();
    void moveToPos(heroItem*, QPoint);

    QStateMachine *stm;
    QState *freeState;
    QState *moveState;
    QState *moveComplete;
    QState *attackState;
    QState *attackComplete;
    QState *abilityState;
    QState *abilityComplete;

    backview *widgetMain;
    gameMenu* menu;
    backScene *scene;
    gameBackInfo* gbi;
    gameCoordinate *gc;

    QLabel *statusLabel;
    QLabel *coordinateLabel;
    QLabel *heroLabel;
    QLabel *campLabel;

    QAction *endTurnAction;

    Ui::MainWindow *ui;

signals:
    void elementClickedSignal(QGraphicsSceneMouseEvent*);

private slots:
    void restoreAll();
    void changeStatusInfo(QString);
    void showMoveSphere();
    void showAttackSphere();
    void heroClicked(QGraphicsSceneMouseEvent*);
    void elementClickedSlot(QGraphicsSceneMouseEvent*);
};

#endif // MAINWINDOW_H
