#include <QDialog>
#include <QToolButton>
#include "menu.h"
#include "carditem.h"
#include "layoutscene.h"
#include "heroitem.h"
#include "skillcenter.h"

ChooseMenu::ChooseMenu(QWidget* parent)
    : QDialog(parent) {
    qgb = new QGroupBox(this);
    setFixedSize(300, 200);
    mapper = new QSignalMapper(this);
    connect(mapper,
            static_cast<void (QSignalMapper::*)(int)> (&QSignalMapper::mapped),
            this, &QDialog::done);
}

GameMenu::GameMenu(QGraphicsView *parent)
    : cardPhase(CardPhase::CardNormal),
      waitingCardNum(1),
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

    connect(moveButton, &QPushButton::clicked,
            this, &GameMenu::moveClicked);
    connect(attackButton, &QPushButton::clicked,
            this, &GameMenu::attackClicked);
    connect(skillButton, &QPushButton::clicked,
            this, &GameMenu::skillButtonClicked);
    connect(cancelButton, &QPushButton::clicked,
            this, &GameMenu::cancelClicked);

    connect(cancelButton, &QPushButton::clicked,
            this, &GameMenu::hideAllMenu);

    connect(ss, &SkillScene::heroSkillUsed,
            this, &GameMenu::skillClicked);
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

    connect(ui->items, &ViewSendResize::resized,
            this, &GameMenu::resizeItems);
    connect(cs, &CardScene::chosenNCard,
            this, &GameMenu::chosenCardNumChanged);
    connect(ui->buttonOK, &QPushButton::clicked,
            this, &GameMenu::on_buttonOK_clicked);
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
    panelInfo pi;
    HeroInfo hi = hero->getBaseInfo();
    pi.attack = 1;
    pi.attackBouns = hero->aa->attack() - pi.attack;
    pi.attackRange = hi.attackRange;
    pi.attackRangeBouns = hero->aa->attackRange() - pi.attackRange;
    pi.moveRange = hi.moveRange;
    pi.moveRangeBouns = hero->ma->moveRange() - pi.moveRange;

    pi.moneyList = hero->moneyLists();
    es->setContent(pi);
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
    emit buttonOkClicked(cs->getChosenItems());

    if (cardPhase == CardPhase::CardDiscard) {
        cardPhase = CardPhase::CardNormal;
        waitingCardNum = 1;
    }
}

void GameMenu::on_buttonCancel_clicked() {
    qDebug() << "Cancel Clicked";
    emit buttonCancelClicked();
    cs->clearChosenItems();
    cs->listCards();
}

void GameMenu::beginTurnReset() {
    resetMenuEnable();
    cs->setChosenCardNumber(1);
    cs->listCards();
}

void GameMenu::chosenCardNumChanged(int n) {
//    if (cardPhase == CardPhase::CardNormal)
//        return;
//    if (cardPhase == CardPhase::CardChooseOne)
//        return;

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
    if (skills.size() == 0 || skills[n] == NULL) {
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
        ss->getSkill(n)->setOpacity(1.0);   // no skill done by me.
        return;
    }
    SkillBase* sk = skills[n];
    if (NULL == sk) {
        return; //TODO no skill
    }
    ss->getSkill(n)->setToolTip(QString("%1/%2").arg(sk->cdNow()).arg(sk->cdMax()));

    // 2 benefits:
    // (1) not divede by 0
    // (2) not completely transparent
    ss->getSkill(n)->setOpacity(qreal(sk->cdNow() + 0.5) /
                                qreal(sk->cdMax() + 0.5));
}

void GameMenu::setSkillTips() {
    setSkillTip(0);
    setSkillTip(1);
    setSkillTip(2);
}

void GameMenu::moveClicked() {
    emit menuClicked(GameMenuType::Move);
}

void GameMenu::attackClicked() {
    emit menuClicked(GameMenuType::Attack);
}

void GameMenu::skillButtonClicked() {
    emit menuClicked(GameMenuType::SkillTest);
}

void GameMenu::cancelClicked() {
    emit menuClicked(GameMenuType::Cancel);
}
