#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>

#include "ui_mainwindow.h"

class gameMenu;
class backScene;
class gameBackInfo;
class gameCoordinate;
class eventCenter;
class heroItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool variableInitial();
    bool sceneInitial();
    QList<struct externInfo> chooseHero();
    void stateMachineInitial();
    void moveToPos(heroItem*, QPoint);

    gameMenu* menu;
    backScene *scene;
    gameBackInfo* gbi;
    gameCoordinate *gc;
    eventCenter *ec;

    QLabel *itemLabel;
    QLabel *coordinateLabel;
    QLabel *heroLabel;
    QLabel *campLabel;

    QAction *endTurnAction;
    QAction *getCardAction;

    Ui::MainWindow *ui;

private slots:
    void changeStatusInfo(QStringList);
};

#endif // MAINWINDOW_H
