#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QtWidgets>

class gameMenu
{
public:
    gameMenu(QWidget *parent = 0);
    void showMenu(enum menu_type_t, QPointF pos = QPointF());
    void hideMenu(enum menu_type_t);
    void hideAllMenu();

    enum menu_type_t
    {
        menuList,
        moveList,
        attackList,
        abilityList,
        cancelList
    };

private:
    menuInitial();

};

#endif // GAMEMENU_H
