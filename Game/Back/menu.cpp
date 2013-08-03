#include "menu.h"

gameMenu::gameMenu(QGraphicsView *parent) :
    parent(parent),
    ui(new Ui::Form)
{
    ui->setupUi(parent);
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

    hideMenu(MENULIST);

    isMoveAble = isAttackAble = isAbilityAble = true;

    connect(moveButton, SIGNAL(clicked()), this, SIGNAL(moveClicked()));
    connect(attackButton, SIGNAL(clicked()), this, SIGNAL(attackClicked()));
    connect(abilityButton, SIGNAL(clicked()), this, SIGNAL(abilityClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(hideAllMenu()));
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));

    path = "C:/Users/xiang/Documents/GitHub/rsc/heros/";
}

gameMenu::~gameMenu()
{
    delete moveButton;
    delete attackButton;
    delete abilityButton;
    delete cancelButton;
}

void gameMenu::interfaceInitial()
{
    ui->map->setFixedSize(200, 200);
    ui->shop->setFixedSize(200, 200);
    ui->head->setFixedSize(90, 150);
    ui->items->setFixedHeight(150);
    ui->essenial->setFixedSize(100, 100);
    ui->ability->setFixedSize(300, 100);
    ui->heroHp->setFixedWidth(420);

    int height = 70;

    ui->leftHero1->setPixmap(QPixmap(path + "mieShaZhe_Head.png").scaledToHeight(height));
    ui->leftHero2->setPixmap(QPixmap(path + "leiShen_Head.png").scaledToHeight(height));
    ui->leftHero3->setPixmap(QPixmap(path + "duTu_Head.png").scaledToHeight(height));
    ui->leftHero4->setPixmap(QPixmap(path + "huoWuZhe_Head.png").scaledToHeight(height));
    ui->leftHero5->setPixmap(QPixmap(path + "baoXiong_Head.png").scaledToHeight(height));
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
