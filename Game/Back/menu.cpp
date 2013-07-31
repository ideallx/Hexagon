#include "menu.h"

gameMenu::gameMenu(QGraphicsView *parent)
    :parent(parent)
{
    menuInitial();
    interfaceInitial();
}

void gameMenu::menuInitial()
{
    // menuList
    moveButton = new QPushButton(tr("move"), parent);
    attackButton = new QPushButton(tr("attack"), parent);
    abilityButton = new QPushButton(tr("ability"), parent);
    cancelButton = new QPushButton(tr("cancel"), parent);

    moveButton->setGeometry(0, 0, 80, 30);
    attackButton->setGeometry(0, 30, 80, 30);
    abilityButton->setGeometry(0, 60, 80, 30);
    cancelButton->setGeometry(0, 90, 80, 30);

    menuList.append(moveButton);
    menuList.append(attackButton);
    menuList.append(abilityButton);
    menuList.append(cancelButton);

    //hideMenu(MENULIST);

    isMoveAble = isAttackAble = isAbilityAble = true;

    connect(moveButton, SIGNAL(clicked()), this, SIGNAL(moveClicked()));
    connect(attackButton, SIGNAL(clicked()), this, SIGNAL(attackClicked()));
    connect(abilityButton, SIGNAL(clicked()), this, SIGNAL(abilityClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(hideAllMenu()));
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
}

void gameMenu::interfaceInitial()
{
    mapTable = new QTableView(parent);
    mapTable->hide();
}

void gameMenu::showMenu(QPointF pos)
{
    QList<QPushButton*> list;

    list = menuList;
    moveButton->setEnabled(isMoveAble);
    attackButton->setEnabled(isAttackAble);
    abilityButton->setEnabled(isAbilityAble);

    for(int i=0; i<list.count(); i++)
    {
        list[i]->show();
        //list[i]->setGeometry((int)pos.x(), (int)(30*i+pos.y()), list[i]->width(), list[i]->height());
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
    for(int i=0; i<menuList.count(); i++)
    {
        menuList[i]->hide();
    }
}

void gameMenu::reSetInterface(QSize s)
{
    mapTable->setGeometry(0, s.height()-300, 300, 300);
    mapTable->show();
}
