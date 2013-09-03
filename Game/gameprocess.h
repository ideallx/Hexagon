#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QObject>
#include <QDialog>
#include "enums.h"
#include "ui_chooseHero.h"
#include "ui_chooseGame.h"

class EventCenter;
class ItemCollector;
class ModeChooseWidget;
class GameBackInfo;
class GameCoordinate;
class ItemCollector;
class BackScene;
class HeroFactory;
struct externInfo;

class GameProcess : public QObject
{
    Q_OBJECT

public:
    GameProcess(QWidget *parent=0);
    ~GameProcess();
    void preGame();
    void preGameClean();
	void inGame();
    void endGame();
    ItemCollector* getIc() { return ic; }
    QList<struct externInfo> getPreGameResult() { return eil; }

private:
	void loadResources();
    void chooseBirthScreen();
    void modeChooseScreen();
    void buildGameInfo();

    Ui::chooseHero* uic;
    Ui::ChooseGame* uig;

    ModeChooseWidget* mcw;
    int chosenHeroNum;
    int playerHeroSeq;
    QWidget* parent;
    QDialog *heroChooseDialog;
    EventCenter* ec;

	GameBackInfo* gbi;
	GameCoordinate* gc;
	ItemCollector* ic;
	BackScene* bs;
    HeroFactory *hf;

	QList<struct externInfo> eil;

signals:
    void choseHeroChoose();
    void gameStart();
	
private slots:
    void heroChosed();
    void heroChooseScreen();
    void gameChooseScreen();
    void birthChooseScreen();

};

#endif // GAMEPROCESS_H
