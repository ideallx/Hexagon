#include "menu.h"

gameMenu::gameMenu(QGraphicsView *parent) :
    parent(parent),
    ui(new Ui::Form)
{
    heroHeadSlideLength = 100; //uncertain
    ui->setupUi(parent);
    interfaceInitial();
    menuInitial();
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
}

gameMenu::~gameMenu()
{
    delete moveButton;
    delete attackButton;
    delete abilityButton;
    delete cancelButton;
    delete es;
    delete ss;
}

void gameMenu::interfaceInitial()
{
    es = new essenialScene();
    ss = new skillScene();
    cs = new cardScene();

    ui->map->setFixedSize(200, 200);
    ui->shop->setFixedSize(200, 200);
    ui->head->setFixedSize(137, 200);
    ui->items->setFixedHeight(150);
    ui->essenial->setFixedSize(150, 100);
    ui->ability->setFixedSize(300, 100);
    ui->heroHp->setFixedWidth(470);

    ui->essenial->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->essenial->setScene(es);
    ui->ability->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->ability->setScene(ss);
    ui->items->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->items->setScene(cs);
}

void gameMenu::showMenu(QPoint pos)
{
    QList<QPushButton*> list;

    list = menuList;
    moveButton->setEnabled(isMoveAble);
    attackButton->setEnabled(isAttackAble);
    abilityButton->setEnabled(isAbilityAble);

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

void gameMenu::listSlideHeroHead(QList<QString>leftColumn, QList<QString>rightColumn)
{
    int num = leftColumn.size();
    for(int i=0; i<num; i++)
    {
        QLabel *heroAvater = new QLabel();
        heroAvater->setFixedSize(heroHeadSlideLength, heroHeadSlideLength);
        heroAvater->setPixmap(QPixmap(leftColumn[i]).scaledToHeight(heroHeadSlideLength));
        ui->leftHeros->addWidget(heroAvater);
    }
    num = rightColumn.size();
    for(int i=0; i<num; i++)
    {
        QLabel *heroAvater = new QLabel();
        heroAvater->setAlignment(Qt::AlignRight);
        heroAvater->setFixedSize(100, 100);
        heroAvater->setFixedSize(heroHeadSlideLength, heroHeadSlideLength);
        heroAvater->setPixmap(QPixmap(rightColumn[i]).scaledToHeight(heroHeadSlideLength));
        ui->rightHeros->addWidget(heroAvater);
    }
}

void gameMenu::setHeroHp(int curHp, int maxHp)
{
    ui->heroHp->setMaximum(maxHp);
    ui->heroHp->setValue(curHp);
}


void gameMenu::setHeroAvaters(QPixmap *p)
{
    ui->head->setPixmap(p->scaledToHeight(200));
}

void gameMenu::setDisplayCards(QList<handCard*> cards) //TOFIX
{
    cs->clear();
    for(int i=0; i<cards.size(); i++)
    {
        cards[i]->setPos(20*i, 0);
        cs->addItem(cards[i]);
    }
}
