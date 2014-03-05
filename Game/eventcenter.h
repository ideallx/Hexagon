#ifndef GAME_EVENTCENTER_H_
#define GAME_EVENTCENTER_H_

#include <QObject>
#include <QPoint>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QStringList>
#include <QEventLoop>
#include <QStack>
#include "enums.h"
#include "coordinate.h"

class SkillBase;
class BackScene;
class GameMenu;
class ItemCollector;
class GameCoordinate;
class HeroItem;
class GameMapElement;
class HandCard;
class HeroFactory;
class AI;
class BackView;
class SkillPara;

class EventCenter : public QObject {
    Q_OBJECT

 public:
    EventCenter(BackView* bv, QWidget* parent = 0);
    ~EventCenter();
    QStringList buildRoundInfo();
    void gameBegin();
    void checkHeros();
    inline bool isGameBegined() { return gameBegined; }
    bool askForUseCard(HeroItem* hi, CardNormalPackageType t);
    QList<HandCard*> askForNCard(HeroItem* hi, int n);
    QList<HandCard*> discardCard(HeroItem* hi, int num);
    void showSkillRange(QGraphicsItem* from, MapRangeType,
                        int range);
    void showSkillRange(QList<QPoint> lp);
    void setHeroPosition(HeroItem* hi, QPoint pos);
    QList<HeroItem*> getHerosInList(QList<QPoint> lp);
    QList<QPoint> getPointInRange(QPoint p,
                                  MapRangeType,
                                  int range);
    HeroItem* hasHeroOnPoint(QPoint p);
    QList<HeroItem*> getHerosOfCamp(Camp c);
    static QList<int> rollTheDice(int n);
    void setCurHero(HeroItem* hi);
    void listHeroInfo(HeroItem* hi);
    bool dodge(int hitRate);

    void preGame();
    void gameReady();
    void loadResources(QString);
    void buildGameInfo(HeroNum);
    void askForChooseBox();
    void release();
    void run();

 private:
    typedef void (EventCenter::* Callback)(bool);
    void setupConnection();
    void setupAIConnection();
    void roundBegin();
    void roundEnd();
    void heroMoveToPoint(QPoint p);
    void heroAttackPoint(QPoint p);
    void attackCalc(HeroItem* from, HeroItem* to);
    void skillStraightTest(QPoint p);
    void actSkills(QList<SkillBase*> sbl);

    void menuClickAct(GameMenuType gmt);
    bool isThisRoundComplete();
    QPoint askForSelectPoint();
    GameMenuType askForNewEvent();
    void process();

    void moveAnimate(HeroItem* item, GameMapElement* gme);
    void attackAnimate(HeroItem* srcItem, HeroItem* targetItem);
    void skillAnimate(HeroItem* item, GameMapElement* gme);

    void showCards(HeroItem* hi);
    void acquire(AskType at, bool active = true);

    void waitForTime(int msec);

    template <typename T1, typename T2>
    int roughDistance(T1 t1, T2 t2) {
        return GameCoordinate::roughDistance(t1->point(), t2->point());
    }

    int roundNum;

    HeroItem* curHero;
    HeroItem* targetHero;

    class AskForUseCard_t {
     public:
        HeroItem* useCardHero;
        CardNormalPackageType useCardType;
        int n;
    } askCard;

    BackScene *scene;
    GameMenu* menu;
    ItemCollector* ic;
    GameBackInfo* gbi;
    GameCoordinate* gc;
    HeroFactory* hf;
    QList<HeroItem*> heroSeq;
    bool gameBegined;

    SkillBase* curSkill;
    QGraphicsItemAnimation* theGia;
    QWidget* parent;
    bool isAnimating;
    BackView* bv;

    QList<ExternInfo> eil;
    AskType askType;
    QPoint resultsPoint;
    QList<HandCard*> resultsCard;
    GameMenuType resultsGMT;
    int playerHeroNum;
    int resultsNum;
    bool gameTerminated;
    QEventLoop *loop;

 signals:
    void roundInfoChanged(QStringList);
    void changeHeroInfo(HeroItem* hi);
    void releaseLock();

 public slots:
    void targetClicked(QPoint p);
    void heroChosen(HeroItem* hi);
    void getCard(int num = 1);
    void mapElementChosen(QPoint p);
    void turnEnd();
    void turnBegin();
    void mapClear();
    void showMenu(HeroItem* hi, QPoint p);
    void cardChosen(QList<HandCard*> l);
    void cardCancel();
    void openShop();
    void heroUseSkill(int n);
    void endTurnSignal();
    void endLoop();
};

#endif  // GAME_EVENTCENTER_H_
