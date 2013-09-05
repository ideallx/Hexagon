#ifndef GAME_EVENTCENTER_H_
#define GAME_EVENTCENTER_H_

#include <QObject>
#include <QPoint>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QStringList>

class BackScene;
class GameMenu;
class ItemCollector;
class GameCoordinate;
class HeroItem;
class GameMapElement;

class EventCenter : public QObject {
    Q_OBJECT

 public:
    EventCenter(BackScene* scene, GameMenu* menu);
    QStringList buildRoundInfo();
    void gameBegin();
    void checkHeros();
    bool isGameBegined() { return gameBegined; }

    enum gamePhase_t {
        BeginPhase,
        ChooseBirthPhase,
        MovePhase,
        AttackPhase,
        SkillPhase,
        DiscardPhase,
        FinalPhase
    };

 private:
    void setupConnection();
    void roundBegin();
    void roundEnd();
    void setCurHero(HeroItem* hi);
    void heroMoveToPoint(QPoint p);
    void heroAttackPoint(QPoint p);
    void skillStraightTest(QPoint p);

    void moveAnimate(HeroItem* item, GameMapElement* gme);
    void attackAnimate(HeroItem* srcItem, HeroItem* targetItem);
    void skillAnimate(HeroItem* item, GameMapElement* gme);

    void showCards(HeroItem* hi);
    void setHeroBirth(HeroItem* hi, QPoint birthP);
    int roundNum;

    HeroItem* curHero;
    BackScene *scene;
    GameMenu* menu;
    ItemCollector* ic;
    enum gamePhase_t curPhase;
    QList<HeroItem*> heroSeq;
    bool gameBegined;
    int playerHeroNum;


    QGraphicsItemAnimation* theGia;

 signals:
    void roundInfoChanged(QStringList);

 public slots:
    void targetClicked(QPoint p);
    void heroChosen(HeroItem* hi);
    void getCard(int num = 1);
    void moveBegin();
    void attackBegin();
    void skillBegin();
    void endTurn();
    void mapClear();
    void showMenu(HeroItem* hi, QPoint p);
};

#endif  // GAME_EVENTCENTER_H_
