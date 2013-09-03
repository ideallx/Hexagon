#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QStringList>

#include "ui_mainwindow.h"

class GameMenu;
class BackScene;
class GameBackInfo;
class GameCoordinate;
class EventCenter;
class HeroItem;
class GameProcess;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool variableInitial();
    bool sceneInitial();
    void chooseBirth();
    void stateMachineInitial();
    void moveToPos(HeroItem*, QPoint);

    GameMenu* menu;
    BackScene *scene;
    GameBackInfo* gbi;
    GameCoordinate *gc;
    EventCenter *ec;

    GameProcess *gp;

    QLabel *itemLabel;
    QLabel *coordinateLabel;
    QLabel *HeroLabel;
    QLabel *campLabel;
    QLabel *roundLabel;

    QAction *endTurnAction;
    QAction *getCardAction;

    Ui::MainWindow *ui;

public slots:
    void gameBegin();
    void changeStatusInfo(QStringList);
    void changeRoundInfo(QStringList);
};

#endif // MAINWINDOW_H
