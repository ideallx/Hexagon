#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>

class gameMenu;
class backScene;
class gameBackInfo;
class gameCoordinate;
class eventCenter;
class heroItem;


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
