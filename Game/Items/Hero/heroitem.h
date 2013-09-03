#ifndef HEROITEM_H
#define HEROITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "enums.h"


class HandCard;
class SkillBase;

enum triggerTime_t;

class HeroItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    Q_PROPERTY(QPoint point READ point WRITE setPoint)

public:

    HeroItem(int lineLength);
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

    void setCards(QList<HandCard*> c){ theCards = c; }
    void addCards(QList<HandCard*> c);
    QList<HandCard*> cards() { return theCards; }

    void addSkill(SkillBase* s);
    void removeSkill(SkillBase* s);
    QList<SkillBase*> hasSkillTriggerAt(enum triggerTime_t);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);


private:
    QList<SkillBase*> skills;
    QList<HandCard*> theCards;
    QList<QPixmap> theSkillButtons;
    int theAttack;
    QPixmap* theAvaPic;
    QPixmap* theWhoPic;
    int theMaxHealth;
    int theHealth;
    enum camp_t theCamp;
    QPoint thePoint;
    char theSexual;
    char theMoveRange;
    char theAttackRange;
    QString thePlayerName;
    QString theHeroName;

    int lineLength;
    QColor color;


signals:
    void mouseClicked(QGraphicsSceneMouseEvent *event);
    void heroInvokeMenu(QPointF);
    void changeStatus(QString);
};

#endif // HEROITEM_H
