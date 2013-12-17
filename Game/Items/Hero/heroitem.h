#ifndef GAME_ITEMS_HERO_HEROITEM_H_
#define GAME_ITEMS_HERO_HEROITEM_H_

#include <QGraphicsItem>
#include <QPainter>
#include "enums.h"
#include "skillcenter.h"

class HandCard;
class SkillBase;
class Equipment;
class ArtificialIntellegence;

class HeroItem : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(QPoint thePoint READ point WRITE setPoint)

    class AttackAbility {
     public:
        AttackAbility(int initAttack, int initRange);

     private:
        int attackTime;
    };

    class OtherInfo {
     public:
        OtherInfo();

        int theCamp;

    };

 public:
    explicit HeroItem(int lineLength);
    void setHeroProperty(Sexual s, int ar, int m, int h);
    void setHeroProperty(HeroInfo);
    inline HeroInfo getBaseInfo() {return baseInfo; }

    Camp camp() const { return theCamp;}
    void setCamp(Camp c) { theCamp = c; }
    Sexual sexual() const { return theSexual; }

    int attackRange() const { return theAttackRange; }
    int moveRange() const { return theMoveRange; }

    int health() const { return theHealth; }
    void addHealth(int n);
    int maxHealth() const { return theMaxHealth; }
    void setHealth(int h) { theHealth = h; }

    bool addEquipment(Equipment* eq);
    bool removeEquipment(Equipment* eq);
    QList<Equipment*> equipmentList() { return equipments; }

    QPixmap* avaterPic() const { return theAvaPic; }
    QPixmap* wholePic() const { return theWhoPic; }
    void setAvaterPic(QPixmap* p) { theAvaPic = p;}
    void setwholePic(QString path);
    void setSkillPics(QString path);
    QList<QPixmap> skillButtons() { return theSkillButtons; }
    QList<int> skillCoolDown();

    int attack() const { return theAttack; }
    void setAttack(int i) { theAttack = i; }
    void addNextAttackBouns(AttackBuff ab);

    void removetAttackBouns();
    void beginTurnSettle();
    void endRoundSettle();
    void reduceAllSkillCooldown();
    void reduceAllStatesCooldown();

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
    QList<SkillBase*> hasSkillTriggerAt(TriggerTime);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    static int beginTurnGetCards() { return 2; }
    static int endTurnMaxCards() { return 3; }

    int money() { return theMoney; }
    QList<int> moneyLists() { return moneyList; }
    void addMoney(int mo) { theMoney += mo; moneyList.append(mo);}
    void setMoney(int mo) { theMoney = mo; }
    SkillBase* getHeroSkill(int n);
    void addState(HeroState state, int lastTime);
    QList<SkillBase*> getSkills() { return heroSkills; }
    int getMustHitRate() { return nextMustHit; }
    bool isAttackAble() { return hitCount; }

    void setAI(ArtificialIntellegence* a) { ai = a; }
    ArtificialIntellegence* AI() { return ai; }

 private:
    QString thePlayerName;
    QList<SkillBase*> skills;
    QList<SkillBase*> heroSkills;
    QList<HandCard*> theCards;
    QList<QPixmap> theSkillButtons;
    QList<AttackBuff> tempBuff;
    QList<int> moneyList;
    QList<Equipment*> equipments;
    QList<QPair<HeroState, int> > heroStates;
    int theAttack;
    QPixmap* theAvaPic;
    QPixmap* theWhoPic;
    int theHealth;
    int theMaxHealth;
    Camp theCamp;
    QPoint thePoint;
    Sexual theSexual;
    int theMoveRange;
    int theAttackRange;
    QString theHeroName;

    HeroInfo baseInfo;

    int lineLength;
    QColor color;
    int theMoney;
    int nextMustHit;
    int hitCount;
    ArtificialIntellegence* ai;

 signals:
    void mouseClicked(QGraphicsSceneMouseEvent *event);
    void heroInvokeMenu(QPointF);
    void changeStatus(QString);
};

#endif  // GAME_ITEMS_HERO_HEROITEM_H_
