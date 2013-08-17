#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QObject>
#include <QDialog>
#include "ui_chooseHero.h"

class eventCenter;
class itemCollector;


class gameProcess : public QObject
{
    Q_OBJECT

public:
    gameProcess();
    void preGame();


private:
    void chooseHeroScreen();
    void heroChosed();

    Ui::chooseHero* uic;

    QDialog *heroChooseDialog;
    eventCenter* ec;
    itemCollector* ic;

signals:
    void choseHeroChoose();

};

#endif // GAMEPROCESS_H
