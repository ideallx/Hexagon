#ifndef GAME_BACK_MENU_H_
#define GAME_BACK_MENU_H_

#include <QList>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPushButton>
#include <QDebug>

#include "ui_front.h"

class EssenialScene;
class SkillScene;
class CardScene;
class HandCard;
class HeroItem;
struct heroInfo;


class GameMenu : public QObject {
    Q_OBJECT

 public:
    explicit GameMenu(QGraphicsView *parent = 0);
    ~GameMenu();
    bool MoveAble() { return isMoveAble; }
    bool AttackAble() { return isAttackAble; }
    bool AbilityAble() { return isSkillAble; }
    void setMoveAble(bool b = true) { isMoveAble = b; }
    void setAttackAble(bool b = true) { isAttackAble = b; }
    void setSkillAble(bool b = true) { isSkillAble = b; }
    void resetMenuEnable();
    void setMap(QGraphicsScene* s);
    void setHeroAvaters(QPixmap *p);
    void setHeroSkillButton(QList<QPixmap>in) { ss->setHeroSkillButton(in); }
    void setHeroHp(int curHp, int maxHp);
    void setEssenial(struct panelInfo pi) { es->setContent(pi); }
    void setHeroInfo(HeroItem* hero);
    void setPrompt(QString prompt);
    void askForNCards(int n);

 private:
    void menuInitial();
    void interfaceInitial();
    QList<HandCard*> toHandCard(QList<QGraphicsItem*> l);

    enum CardPhase_t {
        CardNormal,
        CardDiscard,
        CardChooseOne
    };
    enum CardPhase_t cardPhase;
    int waitingCardNum;

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
    void moveClicked();
    void attackClicked();
    void skillClicked();
    void cancelClicked();
    void buttonOkClicked(QList<HandCard*> l);

 public slots:
    void resizeItems();
    void listSlideHeroHead(QList<QString>leftColumn,
                           QList<QString>rightColumn);
    void hideAllMenu();
    void showMenu(QPoint pos = QPoint());
    void reSetInterface(QSize);
    void updateCardsArea(QList<HandCard*> cards);
    void chosenCardNumChanged(int n);
    void on_buttonOK_clicked();
};


#endif  // GAME_BACK_MENU_H_
