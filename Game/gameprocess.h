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
    void preGame();



    eventCenter* ec;
    itemCollector* ic;



};

#endif // GAMEPROCESS_H
