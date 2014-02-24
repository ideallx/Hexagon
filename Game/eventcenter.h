#ifndef GAME_EVENTCENTER_H_
#define GAME_EVENTCENTER_H_

#include <QObject>
#include <QPoint>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QStringList>
#include <QEventLoop>
#include <QStack>
#include <QThread>
#include <QSemaphore>
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
class ArtificialIntellegence;

class EventCenter : public QThread {
    Q_OBJECT

 public:
    EventCenter(BackScene* scene, GameMenu* menu, QWidget* parent = 0);
    QStringList buildRoundInfo();
    void gameBegin();
    void checkHeros();
    inline bool isGameBegined() { return gameBegined; }
    void askForDiscardCards(int num);
    bool askForUseCard(HeroItem* hi, CardNormalPackageType t);
    bool askForNCard(HeroItem* hi, int n);
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
    void dodge(bool got);

    enum class GamePhase {
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
    typedef int (EventCenter::* eventExec)(GameEvent* e);  // return exec result
    QStack<eventExec> eventStack;
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

    template <typename T1, typename T2>
    int roughDistance(T1 t1, T2 t2) {
        return GameCoordinate::roughDistance(t1->point(), t2->point());
    }
    void run();

    int roundNum;

    HeroItem* curHero;
    HeroItem* targetHero;

    struct AskForUseCard_t {
        HeroItem* useCardHero;
        CardNormalPackageType useCardType;
        int n;
    } askCard;

    BackScene *scene;
    GameMenu* menu;
    ItemCollector* ic;
    GamePhase curPhase;
    QList<HeroItem*> heroSeq;
    bool gameBegined;
    int playerHeroNum;
    Callback waitingEvent;

    SkillBase* curSkill;
    QGraphicsItemAnimation* theGia;
    QWidget* parent;
    bool isAnimating;
    QSemaphore *sem;

 signals:
    void roundInfoChanged(QStringList);
    void endTurnLater();

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
