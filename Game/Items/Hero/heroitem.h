#ifndef GAME_ITEMS_HERO_HEROITEM_H_
#define GAME_ITEMS_HERO_HEROITEM_H_

#include <QGraphicsItem>
#include <QPainter>
#include "enums.h"

class HandCard;
class SkillBase;
enum triggerTime_t;

class HeroItem : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(QPoint point READ point WRITE setPoint)

 public:
    explicit HeroItem(int lineLength);
    void setHeroProperty(char s, char a, char m, int h);
    void setHeroProperty(struct heroInfo);
    enum camp_t camp() const { return theCamp;}
    void setCamp(enum camp_t c) { theCamp = c; }
    char sexual() const { return theSexual; }

    char attackRange() const { return theAttackRange; }
    char moveRange() const { return theMoveRange; }

    int health() const { return theHealth; }
    int maxHealth() const { return theMaxHealth; }
    void setHealth(int h) { theHealth = h; }

    QPixmap* avaterPic() const { return theAvaPic; }
    QPixmap* wholePic() const { return theWhoPic; }
    void setAvaterPic(QPixmap* p) { theAvaPic = p;}
    void setwholePic(QPixmap*p);
    QList<QPixmap> skillButtons() { return theSkillButtons; }

    int attack() const { return theAttack; }
    void setAttack(int i) { theAttack = i; }

    QString playerName() const { return thePlayerName; }
    QString heroName() const { return theHeroName; }
    void setHeroName(QString n) { theHeroName = n; }

    QPoint point() const { return thePoint;}
    void setPoint(QPoint p) { thePoint = p; }

    void setCards(QList<HandCard*> c) { theCards = c; }
    void addCards(QList<HandCard*> c);
    QList<HandCard*> cards() { return theCards; }
    bool removeCard(HandCard* hc) { return theCards.removeOne(hc); }

    void addSkill(SkillBase* s);
    void removeSkill(SkillBase* s);
    QList<SkillBase*> hasSkillTriggerAt(enum triggerTime_t);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    static int beginTurnGetCards() { return 2; }
    static int endTurnMaxCards() { return 3; }

 private:
    QString thePlayerName;
    QList<SkillBase*> skills;
    QList<HandCard*> theCards;
    QList<QPixmap> theSkillButtons;
    int theAttack;
    QPixmap* theAvaPic;
    QPixmap* theWhoPic;
    int theHealth;
    int theMaxHealth;
    enum camp_t theCamp;
    QPoint thePoint;
    char theSexual;
    char theMoveRange;
    char theAttackRange;
    QString theHeroName;

    int lineLength;
    QColor color;

 signals:
    void mouseClicked(QGraphicsSceneMouseEvent *event);
    void heroInvokeMenu(QPointF);
    void changeStatus(QString);
};

#endif  // GAME_ITEMS_HERO_HEROITEM_H_
