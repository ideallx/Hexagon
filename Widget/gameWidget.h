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

class gameMenu;
class backScene;
class gameBackInfo;
class gameCoordinate;
class eventCenter;
class heroItem;
class gameProcess;

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

    gameMenu* menu;
    backScene *scene;
    gameBackInfo* gbi;
    gameCoordinate *gc;
    eventCenter *ec;

    gameProcess *gp;

    QLabel *itemLabel;
    QLabel *coordinateLabel;
    QLabel *heroLabel;
    QLabel *campLabel;
    QLabel *roundLabel;

    QAction *endTurnAction;
    QAction *getCardAction;

    Ui::MainWindow *ui;

public slots:
    void changeStatusInfo(QStringList);
    void changeRoundInfo(QStringList);
};

#endif // MAINWINDOW_H
