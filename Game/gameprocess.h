#ifndef GAME_GAMEPROCESS_H_
#define GAME_GAMEPROCESS_H_

#include <QObject>
#include <QDialog>
#include "enums.h"
#include "ui_chooseHero.h"
#include "ui_chooseGame.h"
#include "ui_chooseBirth.h"

class EventCenter;
class ItemCollector;
class ModeChooseWidget;
class GameBackInfo;
class GameCoordinate;
class ItemCollector;
class BackScene;
class HeroFactory;
struct externInfo;

class GameProcess : public QObject {
    Q_OBJECT

 public:
    explicit GameProcess(QWidget *parent = 0);
    ~GameProcess();
    void preGame();
    void preGameClean();
    void inGame();
    void endGame();
    ItemCollector* getIc() { return ic; }
    QList<struct ExternInfo> getPreGameResult() { return eil; }

 private:
    void loadResources(QString path);
    void chooseBirthScreen();
    void modeChooseScreen();
    void buildGameInfo();

    Ui::chooseHero* uic;
    Ui::ChooseGame* uig;
    Ui::ChooseBirth* uib;

    QWidget* parent;
    ModeChooseWidget* mcw;
    int chosenHeroNum;
    int playerHeroSeq;
    QDialog *chooseDialog;
    EventCenter* ec;

    GameBackInfo* gbi;
    GameCoordinate* gc;
    ItemCollector* ic;
    BackScene* bs;
    HeroFactory *hf;

    QList<struct ExternInfo> eil;

 signals:
    void choseHeroChoose();
    void gameStart();

 private slots:
    void heroChosed();
    void heroChooseScreen();
    void gameChooseScreen();
    void birthChooseScreen();
};

#endif  // GAME_GAMEPROCESS_H_
