#include <QDialog>
#include <QToolButton>
#include "menu.h"
#include "carditem.h"
#include "layoutscene.h"
#include "heroitem.h"

GameMenu::GameMenu(QGraphicsView *parent)
    : cardPhase(CardNormal),
    waitingCardNum(0),
    parent(parent),
    heroHeadSlideLength(80),
    ui(new Ui::Form) {  // uncertain
    interfaceInitial();
    menuInitial();
}

void GameMenu::menuInitial() {
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

    hideAllMenu();
    resetMenuEnable();

    connect(moveButton, SIGNAL(clicked()), this, SIGNAL(moveClicked()));
    connect(attackButton, SIGNAL(clicked()), this, SIGNAL(attackClicked()));
    connect(skillButton, SIGNAL(clicked()), this, SIGNAL(skillClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(hideAllMenu()));
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
}

GameMenu::~GameMenu() {
    delete moveButton;
    delete attackButton;
    delete skillButton;
    delete cancelButton;
    delete es;
    delete ss;
}

void GameMenu::interfaceInitial() {
    ui->setupUi(parent);
    es = new EssenialScene();
    ss = new SkillScene();
    cs = new CardScene();

    ui->head->setFixedSize(200, 290);
    ui->items->setFixedHeight(250);
    ui->essenial->setFixedSize(150, 100);
    ui->ability->setFixedSize(300, 100);
    ui->heroHp->setFixedWidth(470);

    ui->essenial->setRenderHints(QPainter::Antialiasing |
                                 QPainter::SmoothPixmapTransform);
    ui->essenial->setScene(es);
    ui->ability->setRenderHints(QPainter::Antialiasing |
                                QPainter::SmoothPixmapTransform);
    ui->ability->setScene(ss);
    ui->items->setRenderHints(QPainter::Antialiasing |
                              QPainter::SmoothPixmapTransform);
    ui->items->setScene(cs);
    // ui->items->setStyleSheet("background: transparent");
    ui->items->setMouseTracking(true);

    ui->buttonCancel->setFixedSize(50, 100);
    ui->buttonOK->setFixedSize(50, 100);

    connect(ui->items, SIGNAL(resized()), this, SLOT(resizeItems()));
    connect(cs, SIGNAL(chosenNCard(int)),
            this, SLOT(chosenCardNumChanged(int)));
    connect(ui->buttonOK, SIGNAL(clicked()),
            this, SLOT(on_buttonOK_clicked()));
}

void GameMenu::showMenu(QPoint pos) {
    QList<QPushButton*> list;
    list = menuList;
    moveButton->setEnabled(isMoveAble);
    attackButton->setEnabled(isAttackAble);
    skillButton->setEnabled(isSkillAble);

    for (int i = 0; i < list.count(); i++) {
        list[i]->show();
        list[i]->setGeometry(pos.x(), 30*i+pos.y(),
                             list[i]->width(), list[i]->height());
    }
}

void GameMenu::hideAllMenu() {
    for (int i = 0; i < menuList.size(); i++) {
        menuList[i]->hide();
    }
}

void GameMenu::resetMenuEnable() {
    for (int i = 0; i < menuList.size(); i++) {
        menuList[i]->setEnabled(true);
    }
    isMoveAble = isAttackAble = isSkillAble = true;
}

void GameMenu::reSetInterface(QSize s) {
    mapTable->setGeometry(0, s.height()-300, 300, 300);
    mapTable->show();
}

void GameMenu::listSlideHeroHead(QList<QString>leftColumn,
                                 QList<QString>rightColumn) {
    int num = leftColumn.size();
    for (int i = 0; i < num; i++) {
        QLabel *heroAvater = new QLabel();
        heroAvater->setFixedSize(heroHeadSlideLength, heroHeadSlideLength);
        heroAvater->setPixmap(
                    QPixmap(leftColumn[i]).
                    scaledToHeight(heroHeadSlideLength));
        ui->leftHeros->addWidget(heroAvater);
    }
    num = rightColumn.size();
    for (int i = 0; i < num; i++) {
        QLabel *heroAvater = new QLabel();
        heroAvater->setAlignment(Qt::AlignRight);
        heroAvater->setFixedSize(100, 100);
        heroAvater->setFixedSize(heroHeadSlideLength, heroHeadSlideLength);
        heroAvater->setPixmap(
                    QPixmap(rightColumn[i]).
                    scaledToHeight(heroHeadSlideLength));
        ui->rightHeros->addWidget(heroAvater);
    }
}

void GameMenu::setHeroHp(int curHp, int maxHp) {
    ui->heroHp->setMaximum(maxHp);
    ui->heroHp->setValue(curHp);
}

void GameMenu::setHeroInfo(HeroItem* hero) {
    setHeroHp(hero->health(), hero->maxHealth());
    setHeroAvaters(hero->wholePic());
    struct panelInfo pi;
    pi.attack = QString::number(hero->attack());
    pi.attackRange = QString::number(hero->attackRange());
    pi.moveRange = QString::number(hero->moveRange());
    pi.money = QString::number(hero->money());
    setEssenial(pi);
    setHeroSkillButton(hero->skillButtons());
}


void GameMenu::setHeroAvaters(QPixmap *p) {
    ui->head->setPixmap(p->scaledToHeight(ui->head->height(),
                                          Qt::SmoothTransformation));
}

void GameMenu::updateCardsArea(QList<HandCard*> cards) {
    cs->setSceneRect(0, 0, ui->items->width(), ui->items->height());
    QList<QGraphicsItem*> ims = cs->items();
    for (int i = 0; i < ims.size(); i++) {
        cs->removeItem(ims[i]);
    }

    if (cards.size() == 0)
        return;

    for (int i = 0; i < cards.size(); i++) {
        cs->addItem(cards[i]);
    }

    resizeItems();
}

void GameMenu::resizeItems() {
    cs->clearChosenItems();
    cs->listCards();
}

void GameMenu::setPrompt(QString prompt) {
    ui->prompt->setText(prompt);
}

void GameMenu::on_buttonOK_clicked() {
    qDebug() << "ok clicked";
    emit buttonOkClicked(toHandCard(cs->getChosenItems()));

    if (cardPhase == CardDiscard) {
        cardPhase = CardNormal;
        waitingCardNum = 0;
    }
}

void GameMenu::askForNCards(int n) {
    ui->buttonOK->setEnabled(false);
    cardPhase = CardDiscard;
    waitingCardNum = n;
}

void GameMenu::chosenCardNumChanged(int n) {
    if (cardPhase == CardNormal)
        return;
    if (cardPhase == CardChooseOne)
        return;

    if (n == waitingCardNum)
        ui->buttonOK->setEnabled(true);
    else
        ui->buttonOK->setEnabled(false);
}

QList<HandCard*> GameMenu::toHandCard(QList<QGraphicsItem*> l) {
    QList<HandCard*> result;
    for (int i = 0; i < l.size(); i++) {
        result.append(static_cast<HandCard*>(l[i]));
    }
    return result;
}
