#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QtWidgets>

class gameMenu : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isMoveAble READ MoveAble WRITE setisMoveAble)
    Q_PROPERTY(bool isAttackAble READ AttackAble WRITE setisAttackAble)
    Q_PROPERTY(bool isAbilityAble READ AbilityAble WRITE setisAbilityAble)

public:
    enum menu_type_t
    {
        MENULIST,
        MOVELIST,
        ATTACKLIST,
        ABILITYLIST,
        CANCELLIST
    };

    gameMenu(QWidget *parent = 0);
    void hideMenu(gameMenu::menu_type_t);

    bool MoveAble() { return isMoveAble; }
    bool AttackAble() { return isAttackAble; }
    bool AbilityAble() { return isAbilityAble; }

    void setisMoveAble(bool b) { isMoveAble = b; }
    void setisAttackAble(bool b) { isAttackAble = b; }
    void setisAbilityAble(bool b) { isAbilityAble = b; }

private:
    void menuInitial();

    QList<QPushButton*> menuList;
    QWidget* parent;
    bool isMoveAble;
    bool isAttackAble;
    bool isAbilityAble;

    QPushButton *moveButton;
    QPushButton *attackButton;
    QPushButton *abilityButton;
    QPushButton *cancelButton;

signals:
    void moveClicked();
    void attackClicked();
    void abilityClicked();
    void cancelClicked();

public slots:
    void hideAllMenu();
    void showMenu(QPointF pos = QPointF());

};


#endif // GAMEMENU_H
