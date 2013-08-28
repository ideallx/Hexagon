#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QObject>
#include <QDialog>
#include "enums.h"
#include "ui_chooseHero.h"

class eventCenter;
class itemCollector;
class modeChooseWidget;
class gameBackInfo;
class gameCoordinate;
class itemCollector;
class backScene;
struct externInfo;

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
	modeChooseWidget* mcw;

	gameBackInfo* gbi;
	gameCoordinate* gc;
	itemCollector* ic;
	backScene* bs;

	QList<struct externInfo> eil;

signals:
    void choseHeroChoose();
	
public slots:
    void heroChosed();
    void heroChooseScreen();

};

#endif // GAMEPROCESS_H
