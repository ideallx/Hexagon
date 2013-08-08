#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

class gameProcess
{
public:
    gameProcess();
    void gameBegin();

private:
    int curPlayerNum;
    int thePlayerNum;

signals:
    void askForMove(int);







private:
    int gamePhase;
};

#endif // GAMEPROCESS_H
