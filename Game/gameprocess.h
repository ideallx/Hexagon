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

    Ui::chooseHero* uic;

    modeChooseWidget* mcw;
    int chosenHeroNum;
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

};

#endif // GAMEPROCESS_H
