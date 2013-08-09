#ifndef EVENTCENTER_H
#define EVENTCENTER_H

#include <QObject>

class backScene;
class gameMenu;
class itemCollector;
class heroItem;

class eventCenter : public QObject
{
    Q_OBJECT
public:
    eventCenter(backScene* scene, gameMenu* menu);
    void gameFlow();

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
    backScene *scene;
    gameMenu* menu;
    itemCollector* ic;

public slots:
    void targetClicked(QPoint);
    void heroChosen(heroItem*);
    void getCard(int num = 1);
    void moveBegin();
    void attackBegin();

};

#endif // EVENTCENTER_H
