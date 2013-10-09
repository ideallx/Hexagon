#ifndef GAME_EVENTCENTER_H_
#define GAME_EVENTCENTER_H_

#include <QObject>
#include <QPoint>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QStringList>
#include <QEventLoop>
#include "enums.h"

class SkillBase;
class BackScene;
class GameMenu;
class ItemCollector;
class GameCoordinate;
class HeroItem;
class GameMapElement;
class HandCard;
class ArtificialIntellegence;

class EventCenter : public QObject {
    Q_OBJECT

 public:
    EventCenter(BackScene* scene, GameMenu* menu, QWidget* parent = 0);
    QStringList buildRoundInfo();
    void gameBegin();
    void checkHeros();
    bool isGameBegined() { return gameBegined; }
    void askForDiscardCards(int num);
    bool askForUseCard(HeroItem* hi, enum Card_Normal_Package_Type_t t);
    bool askForNCard(HeroItem* hi, int n);
    QList<HandCard*> discardCard(HeroItem* hi, int num);
    void showSkillRange(QGraphicsItem* from, enum MapRangeType_t,
                        int range);
    void showSkillRange(QList<QPoint> lp);
    void setHeroPosition(HeroItem* hi, QPoint pos);
    QList<HeroItem*> getHerosInList(QList<QPoint> lp);
    QList<QPoint> getPointInRange(QPoint p,
                                  enum MapRangeType_t,
                                  int range);
    HeroItem* hasHeroOnPoint(QPoint p);
    QList<HeroItem*> getHerosOfCamp(Camp_t c);
    static QList<int> rollTheDice(int n);
    void setCurHero(HeroItem* hi);
    void listHeroInfo(HeroItem* hi);
    void dodge(bool got);

    enum gamePhase_t {
        BeginPhase,
        ChooseBirthPhase,
        MovePhase,
        AttackPhase,
        SkillPhase,
        DiscardPhase,
        FinalPhase,
        AskForCardPhase,
        AskForNCards
    };

 private:
    typedef void (EventCenter::* Callback)(bool);
    void setupConnection();
    void roundBegin();
    void roundEnd();
    void heroMoveToPoint(QPoint p);
    void heroAttackPoint(QPoint p);
    void heroAttackPointH(HeroItem* hi);
    void attackCalc(HeroItem* from, HeroItem* to);
    void skillStraightTest(QPoint p);
    void birthChosed(QPoint in);

    void moveAnimate(HeroItem* item, GameMapElement* gme);
    void attackAnimate(HeroItem* srcItem, HeroItem* targetItem);
    void skillAnimate(HeroItem* item, GameMapElement* gme);

    void showCards(HeroItem* hi);

    void waitForTime(int msec);
    int roundNum;

    HeroItem* curHero;
    HeroItem* targetHero;

    struct AskForUseCard_t {
        HeroItem* useCardHero;
        enum Card_Normal_Package_Type_t useCardType;
        int n;
    } askCard;

    BackScene *scene;
    GameMenu* menu;
    ItemCollector* ic;
    enum gamePhase_t curPhase;
    QList<HeroItem*> heroSeq;
    bool gameBegined;
    int playerHeroNum;
    Callback waitingEvent;

    SkillBase* curSkill;
    QGraphicsItemAnimation* theGia;
    QWidget* parent;
    QList<ArtificialIntellegence*> AIs;
    ArtificialIntellegence* curAI;

 signals:
    void roundInfoChanged(QStringList);

 public slots:
    void targetClicked(QPoint p);
    void heroChosen(HeroItem* hi);
    void getCard(int num = 1);
    void mapElementChosen(QPoint p);
    void moveBegin();
    void attackBegin();
    void skillBegin();
    void endTurn();
    void beginTurn();
    void mapClear();
    void showMenu(HeroItem* hi, QPoint p);
    void cardChosen(QList<HandCard*> l);
    void cardCancel();
    void openShop();
    void heroUseSkill(int n);
};

#endif  // GAME_EVENTCENTER_H_
