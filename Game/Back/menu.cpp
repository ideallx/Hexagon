#include "menu.h"
#include "carditem.h"
#include "layoutscene.h"
#include "heroitem.h"
#include "herolabel.h"
#include <QDialog>
#include <QToolButton>

gameMenu::gameMenu(QGraphicsView *parent) :
    parent(parent),
    ui(new Ui::Form),
    uic(new Ui::chooseHero)
{
    heroHeadSlideLength = 80; //uncertain
    chooseHeroScreen();
    //interfaceInitial();
    menuInitial();
}

void gameMenu::menuInitial()
{
    // menuList
    moveButton = new QPushButton(tr("move"), parent);
    attackButton = new QPushButton(tr("attack"), parent);
    skillButton = new QPushButton(tr("skill"), parent);
    cancelButton = new QPushButton(tr("cancel"), parent);

    moveButton->setGeometry(0, 0, 80, 30);
    attackButton->setGeometry(0, 30, 80, 30);
    skillButton->setGeometry(0, 60, 80, 30);
    cancelButton->setGeometry(0, 90, 80, 30);

    menuList.append(moveButton);
    menuList.append(attackButton);
    menuList.append(skillButton);
    menuList.append(cancelButton);

    hideMenu(MENULIST);
    resetMenuEnable();

    connect(moveButton, SIGNAL(clicked()), this, SIGNAL(moveClicked()));
    connect(attackButton, SIGNAL(clicked()), this, SIGNAL(attackClicked()));
    connect(skillButton, SIGNAL(clicked()), this, SIGNAL(skillClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(hideAllMenu()));
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
}

gameMenu::~gameMenu()
{
    delete moveButton;
    delete attackButton;
    delete skillButton;
    delete cancelButton;
    delete es;
    delete ss;
}

void gameMenu::interfaceInitial()
{
    ui->setupUi(parent);
    es = new essenialScene();
    ss = new skillScene();
    cs = new cardScene();

    ui->head->setFixedSize(200, 290);
    ui->items->setFixedHeight(250);
    ui->essenial->setFixedSize(150, 100);
    ui->ability->setFixedSize(300, 100);
    ui->heroHp->setFixedWidth(470);

    ui->essenial->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->essenial->setScene(es);
    ui->ability->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->ability->setScene(ss);
    ui->items->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->items->setScene(cs);
    ui->items->setStyleSheet("background: transparent");
    ui->items->setMouseTracking(true);

    connect(ui->items, SIGNAL(resized()), this, SLOT(resizeItems()));
}

void gameMenu::showMenu(QPoint pos)
{
    QList<QPushButton*> list;

    list = menuList;
    moveButton->setEnabled(isMoveAble);
    attackButton->setEnabled(isAttackAble);
    skillButton->setEnabled(isSkillAble);

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
    for(int i=0; i<menuList.size(); i++)
    {
        menuList[i]->hide();
    }
}

void gameMenu::resetMenuEnable()
{
    for(int i=0; i<menuList.size(); i++)
    {
        menuList[i]->setEnabled(true);
    }
    isMoveAble = isAttackAble = isSkillAble = true;
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

void gameMenu::setHeroInfo(heroItem* hero)
{
    setHeroHp(hero->health(), hero->maxHealth());
    setHeroAvaters(hero->wholePic());
    struct panelInfo pi;
    pi.attack = QString::number(hero->attack());
    pi.attackRange = QString::number(hero->attackRange());
    pi.moveRange = QString::number(hero->moveRange());
    setEssenial(pi);
    setHeroSkillButton(hero->skillButtons());
}


void gameMenu::setHeroAvaters(QPixmap *p)
{
    ui->head->setPixmap(p->scaledToHeight(ui->head->height(), Qt::SmoothTransformation));
}

void gameMenu::updateCardsArea(QList<handCard*> cards)
{
    cs->setSceneRect(0, 0, ui->items->width(), ui->items->height());
    QList<QGraphicsItem*> ims = cs->items();

    for(int i=0; i<ims.size(); i++)
    {
        cs->removeItem(ims[i]);
    }

    if(cards.size() == 0)
        return;

    for(int i=0; i<cards.size(); i++)
    {
        cs->addItem(cards[i]);
    }
    resizeItems();
}

void gameMenu::resizeItems()
{
    cs->clearChosenItems();
    cs->listCards();
}

void gameMenu::chooseHeroScreen()
{
    heroChooseDialog = new QDialog(parent);
    heroChooseDialog->setModal(true);
    heroChooseDialog->setMouseTracking(true);
    heroChooseDialog->show();
    uic->setupUi(heroChooseDialog);
    for(int i=0; i<4; i++)
    {
        heroLabel* ql = new heroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap("c:/rsc/eee.png"));
        uic->horizontalLayout->addWidget(ql);
        connect(ql, SIGNAL(heroChosen(int)), this, SLOT(heroChosed(int)));
    }
    for(int i=0; i<4; i++)
    {
        heroLabel* ql = new heroLabel(heroChooseDialog);
        ql->setPixmap(QPixmap("c:/rsc/eee.png"));
        uic->horizontalLayout1->addWidget(ql);
        connect(ql, SIGNAL(heroChosen(int)), this, SLOT(heroChosed(int)));
    }
}

void gameMenu::heroChosed(int)
{
    delete heroChooseDialog;
}
