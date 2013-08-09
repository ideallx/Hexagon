#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QObject>
#include <QStateMachine>

class eventCenter;
class itemCollector;

class gameProcess : public QObject
{
public:
    gameProcess();


private:
    void initStatusMachine();
    void preGame();
    void gameBegin();

    void roundBegin();
    void roundEnd();

    int roundNum;

    eventCenter* ec;
    itemCollector* ic;

signals:
    void askForMove(int);



};

#endif // GAMEPROCESS_H
