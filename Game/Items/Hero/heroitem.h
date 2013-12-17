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

    inline Camp camp() const { return theCamp;}
    inline void setCamp(Camp c) { theCamp = c; }
    inline Sexual sexual() const { return theSexual; }

    inline int attackRange() const { return theAttackRange; }
    inline int moveRange() const { return theMoveRange; }

    inline int health() const { return theHealth; }
    void addHealth(int n);
    inline int maxHealth() const { return theMaxHealth; }
    void setHealth(int h) { theHealth = h; }

    bool addEquipment(Equipment* eq);
    bool removeEquipment(Equipment* eq);
    inline QList<Equipment*> equipmentList() { return equipments; }

    inline QPixmap* avaterPic() const { return theAvaPic; }
    inline QPixmap* wholePic() const { return theWhoPic; }
    void setAvaterPic(QPixmap* p) { theAvaPic = p;}
    void setwholePic(QString path);
    void setSkillPics(QString path);
    inline QList<QPixmap> skillButtons() { return theSkillButtons; }
    QList<int> skillCoolDown();

    int attack() const { return theAttack; }
    void setAttack(int i) { theAttack = i; }
    void addNextAttackBouns(AttackBuff ab);

    void removetAttackBouns();
    void beginTurnSettle();
    void endRoundSettle();
    void reduceAllSkillCooldown();
    void reduceAllStatesCooldown();

    inline QString playerName() const { return thePlayerName; }
    inline QString heroName() const { return theHeroName; }
    inline void setHeroName(QString n) { theHeroName = n; }

    inline QPoint point() const { return thePoint;}
    inline void setPoint(QPoint p) { thePoint = p; }

    inline void setCards(QList<HandCard*> c) { theCards = c; }
    void addCards(QList<HandCard*> c);
    inline QList<HandCard*> cards() { return theCards; }
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

    inline int money() { return theMoney; }
    inline QList<int> moneyLists() { return moneyList; }
    inline void addMoney(int mo) { theMoney += mo; moneyList.append(mo);}
    inline void setMoney(int mo) { theMoney = mo; }
    SkillBase* getHeroSkill(int n);
    void addState(HeroState state, int lastTime);
    inline QList<SkillBase*> getSkills() { return heroSkills; }
    inline int getMustHitRate() { return nextMustHit; }
    inline bool isAttackAble() { return hitCount; }

    inline void setAI(ArtificialIntellegence* a) { ai = a; }
    inline ArtificialIntellegence* AI() { return ai; }

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
