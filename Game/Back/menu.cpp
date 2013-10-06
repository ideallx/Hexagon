#include <QDialog>
#include <QToolButton>
#include "menu.h"
#include "carditem.h"
#include "layoutscene.h"
#include "heroitem.h"

ChooseMenu::ChooseMenu(QWidget* parent)
    : QDialog(parent) {
    qgb = new QGroupBox(this);
    setFixedSize(300, 200);
    mapper = new QSignalMapper(this);
    connect(mapper, static_cast<void (QSignalMapper::*)(int)>
            (&QSignalMapper::mapped),
            this, &QDialog::done);
}

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
    connect(skillButton, SIGNAL(clicked()), this, SIGNAL(skillButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(hideAllMenu()));
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
    connect(ss, &SkillScene::heroSkillUsed, this, &GameMenu::skillClicked);
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
    ui->items->setStyleSheet("background: transparent");
    ui->items->setMouseTracking(true);

    ui->buttonCancel->setFixedSize(50, 100);
    ui->buttonOK->setFixedSize(50, 100);

    connect(ui->items, SIGNAL(resized()), this, SLOT(resizeItems()));
    connect(cs, SIGNAL(chosenNCard(int)),
            this, SLOT(chosenCardNumChanged(int)));
    connect(ui->buttonOK, SIGNAL(clicked()),
            this, SLOT(on_buttonOK_clicked()));
    connect(ui->buttonCancel, &QToolButton::clicked,
            this, &GameMenu::on_buttonCancel_clicked);
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
        heroAvater->setPixmap(QPixmap(leftColumn[i]).
                    scaledToHeight(heroHeadSlideLength,
                    Qt::SmoothTransformation));
        ui->leftHeros->addWidget(heroAvater);
    }
    num = rightColumn.size();
    for (int i = 0; i < num; i++) {
        QLabel *heroAvater = new QLabel();
        heroAvater->setAlignment(Qt::AlignRight);
        heroAvater->setFixedSize(heroHeadSlideLength, heroHeadSlideLength);
        heroAvater->setPixmap(QPixmap(rightColumn[i]).
                    scaledToHeight(heroHeadSlideLength,
                    Qt::SmoothTransformation));
        ui->rightHeros->addWidget(heroAvater);
    }
}

void GameMenu::setHeroHp(int curHp, int maxHp) {
    ui->heroHp->setMaximum(maxHp);
    ui->heroHp->setValue(curHp);
}

void GameMenu::setHeroInfo(HeroItem* hero) {
    infoHero = hero;
    setHeroHp(hero->health(), hero->maxHealth());
    setHeroAvaters(hero->wholePic());
    struct panelInfo pi;
    struct HeroInfo hi = hero->getBaseInfo();
    pi.attack = 1;
    pi.attackBouns = hero->attack() - pi.attack;
    pi.attackRange = hi.attackRange;
    pi.attackRangeBouns = hero->attackRange() - pi.attackRange;
    pi.moveRange = hi.moveRange;
    pi.moveRangeBouns = hero->moveRange() - pi.moveRange;

    pi.moneyList = hero->moneyLists();
    setEssenial(pi);
    setHeroSkillButton(hero->skillButtons());
    setHeroSkillCoolDown(hero->getSkills());
    setSkillTips();
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
    qDebug() << "Ok Clicked";
    emit buttonOkClicked(toHandCard(cs->getChosenItems()));

    if (cardPhase == CardDiscard) {
        cardPhase = CardNormal;
        waitingCardNum = 0;
    }
}

void GameMenu::on_buttonCancel_clicked() {
    qDebug() << "Cancel Clicked";
    emit buttonCancelClicked();
    cs->clearChosenItems();
    cs->listCards();
}

void GameMenu::askForNCards(int n) {
    ui->buttonOK->setEnabled(false);
    cardPhase = CardDiscard;
    waitingCardNum = n;
    cs->setOneCardMode(false);
}

void GameMenu::beginTurnReset() {
    resetMenuEnable();
    cs->setOneCardMode(true);
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

void GameMenu::setHeroSkillCoolDown(QList<SkillBase*> in) {
    skills = in;
}

void GameMenu::skillClicked(int n) {
    if (skills.size() == 0) {
        return;
    }
    if (skills[n]->cdNow() != 0) {
        setPrompt("Waiting For CoolDown: " + skills[n]->objectName());
    } else {
        emit skillUsed(n);
    }
}

void GameMenu::setSkillTip(int n) {
    if (skills.size() == 0) {
        return;
    }
    ss->getSkill(n)->setToolTip(QString("%1/%2").arg(skills[n]->cdNow()).arg(skills[n]->cdMax()));
}

void GameMenu::setSkillTips() {
    setSkillTip(0);
    setSkillTip(1);
    setSkillTip(2);
}
