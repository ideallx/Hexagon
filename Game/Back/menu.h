#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QList>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPushButton>
#include <QDebug>

#include "ui_front.h"

class essenialScene;
class skillScene;
class cardScene;
class handCard;
class heroItem;
struct heroInfo;


class gameMenu : public QObject
{
    Q_OBJECT

public:
    enum menu_type_t
    {
        MENULIST,
        MOVELIST,
        ATTACKLIST,
        ABILITYLIST,
        CANCELLIST
    };

    gameMenu(QGraphicsView *parent = 0);
    ~gameMenu();

    void hideMenu(gameMenu::menu_type_t);

    bool MoveAble() { return isMoveAble; }
    bool AttackAble() { return isAttackAble; }
    bool AbilityAble() { return isAbilityAble; }

    void setMoveAble(bool b = true) { isMoveAble = b; }
    void setAttackAble(bool b = true) { isAttackAble = b; }
    void setAbilityAble(bool b = true) { isAbilityAble = b; }

    void resetMenuEnable();

    void setMap(QGraphicsScene* s);
    void setHeroAvaters(QPixmap *p);
    void setHeroSkillButton(QList<QPixmap>in) { ss->setHeroSkillButton(in); }
    void setHeroHp(int curHp, int maxHp);
    void setEssenial(struct panelInfo pi) { es->setContent(pi); }

    void setHeroInfo(heroItem* hero);

private:
    void menuInitial();
    void interfaceInitial();

    QList<QPushButton*> menuList;
    QWidget* parent;

    int heroHeadSlideLength;
    bool isMoveAble;
    bool isAttackAble;
    bool isAbilityAble;

    essenialScene* es;
    skillScene* ss;
    cardScene* cs;

    Ui::Form* ui;

    QPushButton *moveButton;
    QPushButton *attackButton;
    QPushButton *abilityButton;
    QPushButton *cancelButton;

    QTabWidget* mapTable;


signals:
    void moveClicked();
    void attackClicked();
    void abilityClicked();
    void cancelClicked();

public slots:
    void resizeItems();
    void listSlideHeroHead(QList<QString>leftColumn, QList<QString>rightColumn);
    void hideAllMenu();
    void showMenu(QPoint pos = QPoint());
    void reSetInterface(QSize);
    void updateCardsArea(QList<handCard*> cards);

};


#endif // GAMEMENU_H
