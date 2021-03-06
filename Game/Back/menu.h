#ifndef GAME_BACK_MENU_H_
#define GAME_BACK_MENU_H_

#include <QList>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPushButton>
#include <QDialog>
#include <QDebug>
#include <QGroupBox>
#include <QSizePolicy>
#include <QSignalMapper>
#include "ui_front.h"
#include "enums.h"

class EssenialScene;
class SkillScene;
class CardScene;
class HandCard;
class HeroItem;
class SkillBase;
class heroInfo;

class ChooseMenu : public QDialog {
    Q_OBJECT

 public:
    explicit ChooseMenu(QWidget* parent = 0);

    template <typename T>
    void addRawContent(QList<T> l) {
        if (l.size() == 0) {
            return;
        }
        QHBoxLayout *qvbl = new QHBoxLayout(qgb);
        foreach(QGraphicsRectItem* T, l) {
            QToolButton* qtb = new QToolButton(this);
            qtb->setIcon(T->brush().texture());
            qtb->setIconSize(T->rect().size().toSize());
            qvbl->addWidget(qtb);
            connect(qtb, SIGNAL(clicked()),
                    mapper, SLOT(map()));
            mapper->setMapping(qtb, T->type());
            buttons.append(qtb);
        }
        verticalLayout.append(qvbl);
        setFixedSize(300, verticalLayout.size()*200);
    }

 public slots:

 private:
    QSignalMapper *mapper;
    QGroupBox* qgb;
    QList<QToolButton*> buttons;
    QList<QHBoxLayout*> verticalLayout;
};

class GameMenu : public QObject {
    Q_OBJECT

 public:
    explicit GameMenu(QGraphicsView *parent = 0);
    ~GameMenu();
    inline bool MoveAble() { return isMoveAble; }
    inline bool AttackAble() { return isAttackAble; }
    inline bool AbilityAble() { return isSkillAble; }
    inline void setMoveAble(bool b = true) { isMoveAble = b; }
    inline void setAttackAble(bool b = true) { isAttackAble = b; }
    inline void setSkillAble(bool b = true) {isSkillAble = b; }
    void resetMenuEnable();
    void setMap(QGraphicsScene* s);
    void setHeroAvaters(QPixmap *p);
    inline void setHeroSkillButton(QList<QPixmap>in) {
        ss->setHeroSkillButton(in);
    }
    void setHeroSkillCoolDown(QList<SkillBase*> in);
    void setHeroHp(int curHp, int maxHp);
    void setHeroInfo(HeroItem* hero);
    void setPrompt(QString prompt);
    void beginTurnReset();
    void setChosenCardNumber(int in) { cs->setChosenCardNumber(in); waitingCardNum = in;}
    void setSkillTip(int);
    void setSkillTips();
    HeroItem* panelHero() { return infoHero; }

 private:
    void menuInitial();
    void interfaceInitial();
    QList<HandCard*> toHandCard(QList<QGraphicsItem*> l);
    QList<SkillBase*> skills;

    enum class CardPhase {
        CardNormal,
        CardDiscard,
        CardChooseOne
    };
    CardPhase cardPhase;


    int waitingCardNum;
    HeroItem* infoHero;

    QList<QPushButton*> menuList;
    QWidget* parent;
    int heroHeadSlideLength;
    bool isMoveAble;
    bool isAttackAble;
    bool isSkillAble;
    EssenialScene* es;
    SkillScene* ss;
    CardScene* cs;
    Ui::Form* ui;
    QPushButton *moveButton;
    QPushButton *attackButton;
    QPushButton *skillButton;
    QPushButton *cancelButton;
    QTabWidget* mapTable;

 signals:
    void buttonOkClicked(QList<int> l);
    void buttonCancelClicked();
    void skillUsed(int n);
    void menuClicked(GameMenuType gmt);

 public slots:
    void moveClicked();
    void attackClicked();
    void skillButtonClicked();
    void cancelClicked();

    void resizeItems();
    void skillClicked(int n);
    void listSlideHeroHead(QList<QString>leftColumn,
                           QList<QString>rightColumn);
    void hideAllMenu();
    void showMenu(QPoint pos = QPoint());
    void reSetInterface(QSize);
    void updateCardsArea(QList<HandCard*> cards);
    void chosenCardNumChanged(int n);
    void on_buttonOK_clicked();
    void on_buttonCancel_clicked();
};


#endif  // GAME_BACK_MENU_H_
