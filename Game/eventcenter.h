#ifndef EVENTCENTER_H
#define EVENTCENTER_H

#include <QObject>
#include <QPoint>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QStringList>

class animationCenter;
class backScene;
class gameMenu;
class itemCollector;
class gameCoordinate;
class heroItem;

class eventCenter : public QObject
{
    Q_OBJECT

public:
    eventCenter(backScene* scene, gameMenu* menu);
    QStringList buildRoundInfo();

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

    int roundNum;

    heroItem* curHero;

    backScene *scene;
    gameMenu* menu;
    gameCoordinate* gc;
    itemCollector* ic;
    animationCenter* ac;

    QList<heroItem*> heroSeq;
    QGraphicsItemAnimation *gia;
    QTimeLine *giaTimer;
    enum gamePhase_t curPhase;

signals:
    void roundInfoChanged(QStringList);

public slots:
    void heroMoveToPoint(QPoint);
    void targetClicked(QPoint);
    void heroChosen(heroItem*);
    void getCard(int num = 1);
    void moveBegin();
    void attackBegin();
    void endTurn();
    void showMenu(heroItem*, QPoint p);

};

#endif // EVENTCENTER_H
