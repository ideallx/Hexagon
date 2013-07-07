#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QtWidgets>


class gameMenu
{
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
    void showMenu(gameMenu::menu_type_t, QPointF pos = QPointF());
    void hideMenu(gameMenu::menu_type_t);
    void hideAllMenu();


private:
    void menuInitial();
    QList<QPushButton*> menuList;
    QWidget* parent;
};


#endif // GAMEMENU_H
