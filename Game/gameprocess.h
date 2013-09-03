#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QObject>
#include <QDialog>
#include "enums.h"
#include "ui_chooseHero.h"
#include "ui_chooseGame.h"

class eventCenter;
class itemCollector;
class modeChooseWidget;
class gameBackInfo;
class gameCoordinate;
class itemCollector;
class backScene;
class heroFactory;
struct externInfo;

class gameProcess : public QObject
{
    Q_OBJECT

public:
    gameProcess(QWidget *parent=0);
    ~gameProcess();
    void preGame();
    void preGameClean();
	void inGame();
    void endGame();
    itemCollector* getIc() { return ic; }
    QList<struct externInfo> getPreGameResult() { return eil; }

private:
	void loadResources();
    void chooseBirthScreen();
    void modeChooseScreen();
    void buildGameInfo();

    Ui::chooseHero* uic;
    Ui::ChooseGame* uig;

    modeChooseWidget* mcw;
    int chosenHeroNum;
    int playerHeroSeq;
    QWidget* parent;
    QDialog *heroChooseDialog;
    eventCenter* ec;

	gameBackInfo* gbi;
	gameCoordinate* gc;
	itemCollector* ic;
	backScene* bs;
    heroFactory *hf;

	QList<struct externInfo> eil;

signals:
    void choseHeroChoose();
    void gameStart();
	
public slots:
    void heroChosed();
    void heroChooseScreen();
    void gameChooseScreen();
    void birthChooseScreen();

};

#endif // GAMEPROCESS_H
