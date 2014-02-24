#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>

class GameThread : public QThread
{
public:
    GameThread();

    void movePhase();

};

#endif // GAMETHREAD_H
