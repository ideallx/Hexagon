#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QObject>
#include <QDialog>
#include "ui_chooseHero.h"

class eventCenter;
class itemCollector;
class modeChooseWidget;


class gameProcess : public QObject
{
    Q_OBJECT

public:
    gameProcess();
    void preGame();
	void inGame();


private:
	void loadResources();
    void chooseBirthScreen();
	void modeChooseScreen();

    Ui::chooseHero* uic;

    int chosenHeroNum;
    QDialog *heroChooseDialog;
    eventCenter* ec;
    itemCollector* ic;
	modeChooseWidget* mcw;

signals:
    void choseHeroChoose();
	
public slots:
    void heroChosed();
    void heroChooseScreen();

};

#endif // GAMEPROCESS_H
