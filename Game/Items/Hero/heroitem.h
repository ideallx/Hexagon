#ifndef GAME_ITEMS_HERO_HEROITEM_H_
#define GAME_ITEMS_HERO_HEROITEM_H_

#include <QGraphicsItem>
#include <QPainter>
#include "enums.h"

class HandCard;
class SkillBase;

class HeroItem : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(QPoint thePoint READ point WRITE setPoint)

 public:
    explicit HeroItem(int lineLength);
    void setHeroProperty(Sexual_t s, int a, int m, int h);
    void setHeroProperty(struct HeroInfo);
    struct HeroInfo getBaseInfo() { return baseInfo; }

    enum Camp_t camp() const { return theCamp;}
    void setCamp(enum Camp_t c) { theCamp = c; }
    enum Sexual_t sexual() const { return theSexual; }

    int attackRange() const { return theAttackRange; }
    int moveRange() const { return theMoveRange; }

    int health() const { return theHealth; }
    void addHealth(int n);
    int maxHealth() const { return theMaxHealth; }
    void setHealth(int h) { theHealth = h; }

    QPixmap* avaterPic() const { return theAvaPic; }
    QPixmap* wholePic() const { return theWhoPic; }
    void setAvaterPic(QPixmap* p) { theAvaPic = p;}
    void setwholePic(QPixmap*p);
    QList<QPixmap> skillButtons() { return theSkillButtons; }

    int attack() const { return theAttack; }
    void setAttack(int i) { theAttack = i; }
    void addNextAttackBouns(struct AttackBuff ab);
    void removetAttackBouns();

    QString playerName() const { return thePlayerName; }
    QString heroName() const { return theHeroName; }
    void setHeroName(QString n) { theHeroName = n; }

    QPoint point() const { return thePoint;}
    void setPoint(QPoint p) { thePoint = p; }

    void setCards(QList<HandCard*> c) { theCards = c; }
    void addCards(QList<HandCard*> c);
    QList<HandCard*> cards() { return theCards; }
    HandCard* removeCard(HandCard* hc);

    void addSkill(SkillBase* s);
    void addHeroSkill(SkillBase* s);
    void removeSkill(SkillBase* s);
    QList<SkillBase*> hasSkillTriggerAt(enum TriggerTime_t);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    static int beginTurnGetCards() { return 2; }
    static int endTurnMaxCards() { return 3; }

    int money() { return theMoney; }
    QList<int> moneyLists() { return moneyList; }
    void addMoney(int mo) { theMoney += mo; moneyList.append(mo);}
    void setMoney(int mo) { theMoney = mo; }

 private:
    QString thePlayerName;
    QList<SkillBase*> skills;
    QList<SkillBase*> heroSkills;
    QList<HandCard*> theCards;
    QList<QPixmap> theSkillButtons;
    QList<struct AttackBuff> tempBuff;
    QList<int> moneyList;
    int theAttack;
    QPixmap* theAvaPic;
    QPixmap* theWhoPic;
    int theHealth;
    int theMaxHealth;
    enum Camp_t theCamp;
    QPoint thePoint;
    enum Sexual_t theSexual;
    int theMoveRange;
    int theAttackRange;
    QString theHeroName;

    struct HeroInfo baseInfo;

    int lineLength;
    QColor color;
    int theMoney;

 signals:
    void mouseClicked(QGraphicsSceneMouseEvent *event);
    void heroInvokeMenu(QPointF);
    void changeStatus(QString);
};

#endif  // GAME_ITEMS_HERO_HEROITEM_H_
