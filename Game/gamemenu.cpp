#include "gamemenu.h"

gameMenu::gameMenu(QWidget *parent)
{
    this->parent = parent;
    menuInitial();
}

void gameMenu::menuInitial()
{
    // menuList
    QPushButton *moveButton = new QPushButton("Move", parent);
    QPushButton *attackButton = new QPushButton("Attack", parent);
    QPushButton *abilityButton = new QPushButton("Ability", parent);
    QPushButton *cancelButton = new QPushButton("cancel", parent);
    moveButton->setGeometry(0, 0, 80, 30);
    attackButton->setGeometry(0, 30, 80, 30);
    abilityButton->setGeometry(0, 60, 80, 30);
    cancelButton->setGeometry(0, 90, 80, 30);
    menuList.append(moveButton);
    menuList.append(attackButton);
    menuList.append(abilityButton);
    menuList.append(cancelButton);
    hideMenu(MENULIST);


}

void gameMenu::showMenu(gameMenu::menu_type_t type, QPointF pos)
{
    QList<QPushButton*> list;
    switch(type)
    {
    case MENULIST:
        list = menuList;
        break;

    }

    for(int i=0; i<list.count(); i++)
    {
        list[i]->show();
        list[i]->setGeometry(pos.x(), 30*i+pos.y(), list[i]->width(), list[i]->height());
    }
}

void gameMenu::hideMenu(gameMenu::menu_type_t type)
{
    QList<QPushButton*> list;
    switch(type)
    {
    case MENULIST:
        list = menuList;
        break;
    }

    for(int i=0; i<list.count(); i++)
    {
        list[i]->hide();
    }
}

void gameMenu::hideAllMenu()
{
;
}
