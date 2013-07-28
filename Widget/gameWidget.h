#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "backview.h"
#include "backscene.h"
#include "menu.h"
#include "coordinate.h"
#include "eventcenter.h"
#include "sidescene.h"


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

    backview* widgetMain;
    gameMenu* menu;
    backScene *scene;
    gameBackInfo* gbi;
    gameCoordinate *gc;
    eventCenter *ec;

    sideScene* sceneLeft;
    sideScene* sceneRight;

    QLabel *itemLabel;
    QLabel *coordinateLabel;
    QLabel *heroLabel;
    QLabel *campLabel;

    QAction *endTurnAction;

    Ui::MainWindow *ui;

signals:
    void elementClickedSignal(QGraphicsSceneMouseEvent*);
    void heroClickedSignal(QGraphicsSceneMouseEvent*);

private slots:
    void restoreAll();
    void changeStatusInfo(QStringList);
    void showMoveSphere();
    void showAttackSphere();
    void heroClickedSlot(QGraphicsSceneMouseEvent*);
    void elementClickedSlot(QGraphicsSceneMouseEvent*);
};

#endif // MAINWINDOW_H
