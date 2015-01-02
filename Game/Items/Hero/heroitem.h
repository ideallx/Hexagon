#ifndef GAME_ITEMS_HERO_HEROITEM_H_
#define GAME_ITEMS_HERO_HEROITEM_H_

#include <QGraphicsItem>
#include <QPainter>
#include "enums.h"
#include "skillcenter.h"
#include "attackability.h"
#include "moveability.h"

class HandCard;
class SkillBase;
class Equipment;
class AI;
class AttackAbility;
class MoveAbility;


class HeroItem : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

 public:
    explicit HeroItem(int lineLength);
	virtual ~HeroItem();

    // InnerInfo
    void setHeroProperty(Sexual s, int ar, int m, int h);
    void setHeroProperty(HeroInfo);
    inline HeroInfo getBaseInfo() {return baseInfo; }

    inline Camp camp() const { return theCamp;}
    inline void setCamp(Camp c) { theCamp = c; }
    inline Sexual sexual() const { return theSexual; }

    inline int health() const { return theHealth; }
    void addHealth(int n, DamageType st = DamageType::Physical);
    inline int maxHealth() const { return theMaxHealth; }
    void setHealth(int h) { theHealth = h; }
    void ambulance(bool get = true);
    inline void revive() { isAlive = DeathStatus::Alive; }
    inline DeathStatus heroAliveState() { return isAlive; }

    inline QString playerName() const { return thePlayerName; }
    inline QString heroName() const { return theHeroName; }
    inline void setHeroName(QString n) { theHeroName = n; }

    void addState(HeroState state, int lastTime);

    QList<int> skillCoolDown();
    void addSkill(SkillBase* s);
    void addHeroSkills(QList<SkillBase*> sl) { heroSkills = sl; }
    void removeSkill(SkillBase* s);
    QList<SkillBase*> hasSkillTriggerAt(TriggerTime);
    SkillBase* getHeroSkill(int n);
    QList<SkillBase*> getSkills();
    void setSkillAvailable(int sa) {skillAvailable = sa; }

    inline QPoint point() const { return thePoint;}
    inline void setPoint(QPoint p) { thePoint = p; }
    // InnerInfo

    // OuterInfo
    bool addEquipment(Equipment* eq);
    bool removeEquipment(Equipment* eq);
    inline QList<Equipment*> equipmentList() { return equipments; }

    inline QPixmap* avaterPic() const { return theAvaPic; }
    inline QPixmap* wholePic() const { return theWhoPic; }
    void setAvaterPic(QPixmap* p) { theAvaPic = p;}
    void setwholePic(QString path);

    void setSkillPics(QString path);
    QList<QPixmap> skillButtons();


    inline void setCards(QList<int> c) { theCards = c; }
    void addCards(QList<int> c);
    inline QList<int> cards() { return theCards; }
    int removeCard(int cardId);

    inline int money() { return theMoney; }
    inline QList<int> moneyLists() { return moneyList; }
    inline void addMoney(int mo) { theMoney += mo; moneyList.append(mo);}
    inline void cleanMoney() { theMoney = 0; moneyList.clear(); }
    void useMoney(QList<int> money);

    inline void setAI(AI* a) { ai = a; }
    inline AI* getAI() { return ai; }
    // OuterInfo

    void beginTurnSettle();
    void endRoundSettle();
    void reduceAllSkillCooldown();
    void reduceAllStatesCooldown();
    static int beginTurnGetCards() { return 2; }
    static int endTurnMaxCards() { return 3; }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    AttackAbility* aa;
    MoveAbility* ma;


 private:
    QString thePlayerName;
    QList<SkillBase*> skills;
    QList<SkillBase*> heroSkills;
    QList<int> theCards;
    QList<QPixmap> theSkillButtons;
    QList<int> moneyList;
    QList<Equipment*> equipments;
    QList<QPair<HeroState, int> > heroStates;
    QPixmap* theAvaPic;
    QPixmap* theWhoPic;
    int theHealth;
    int theMaxHealth;
    Camp theCamp;
    QPoint thePoint;
    Sexual theSexual;
    QString theHeroName;

    HeroInfo baseInfo;

    int lineLength;
    QColor color;
    int theMoney;
    AI* ai;
    DeathStatus isAlive;
    int skillAvailable;

 signals:
    void mouseClicked(QGraphicsSceneMouseEvent *event);
    void heroInvokeMenu(QPointF);
    void changeStatus(QString);

    friend class AI;
    friend class VvTestTest;
};

#endif  // GAME_ITEMS_HERO_HEROITEM_H_
