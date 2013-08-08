#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QObject>

class gameProcess : public QObject
{
public:
    gameProcess(int playerNum);

    void gameBegin();

private:
    int curPlayerNum;
    int thePlayerNum;

    int gamePhase;

signals:
    void askForMove(int);



};

#endif // GAMEPROCESS_H
