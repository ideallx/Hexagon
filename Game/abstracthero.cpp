#include "abstracthero.h"

abstractHero::abstractHero()
{
    variableInitial();
}

void abstractHero::variableInitial()
{
    // menuList
    QPushButton *moveButton = new QPushButton("Move");
    QPushButton *attackButton = new QPushButton("Attack");
    QPushButton *abilityButton = new QPushButton("Ability");
    QPushButton *cancelButton = new QPushButton("cancel");
    moveButton->setGeometry(0, 0, 80, 30);
    attackButton->setGeometry(0, 30, 80, 30);
    abilityButton->setGeometry(0, 60, 80, 30);
    cancelButton->setGeometry(0, 90, 80, 30);
    menuList.append(moveButton);
    menuList.append(attackButton);
    menuList.append(abilityButton);
    menuList.append(cancelButton);
    showHideAllList(menuList, 'h');
}


void abstractHero::showHideAllList(QList<QPushButton *> list, char s, QPointF pos)
{
    QPushButton* button;
    if(s == 's')
    {
        foreach(button, list)
        {
            button->show();
            button->setGeometry(button->x()+pos.x(), button->y()+pos.y(),
                                button->width(), button->height());
        }
    }
    else if(s == 'h')
    {
        foreach(button, list)
        {
            button->hide();
        }
    }
}
