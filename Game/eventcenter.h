#ifndef EVENTCENTER_H
#define EVENTCENTER_H

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

class EventCenter : public QObject
{
    Q_OBJECT

public:
    EventCenter(BackScene* scene, GameMenu* menu);
    QStringList buildRoundInfo();
    void chooseBirth();

    enum gamePhase_t
    {
        BeginPhase,
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
    void setCurHero(HeroItem*);
    void heroMoveToPoint(QPoint);
    void heroAttackPoint(QPoint);
    void skillStraightTest(QPoint);

    void moveAnimate(HeroItem* item, GameMapElement* gme);
    void attackAnimate(HeroItem* srcItem, HeroItem* targetItem);
    void skillAnimate(HeroItem* item, GameMapElement* gme);

    int roundNum;

    HeroItem* curHero;

    BackScene *scene;
    GameMenu* menu;
    ItemCollector* ic;

    QList<HeroItem*> heroSeq;

    enum gamePhase_t curPhase;

    QGraphicsItemAnimation* theGia;

signals:
    void roundInfoChanged(QStringList);

public slots:
    void targetClicked(QPoint);
    void heroChosen(HeroItem*);
    void getCard(int num = 1);
    void moveBegin();
    void attackBegin();
    void skillBegin();
    void endTurn();
    void mapClear();
    void showMenu(HeroItem*, QPoint p);

};

#endif // EVENTCENTER_H
