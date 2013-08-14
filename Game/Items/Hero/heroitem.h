#ifndef HEROITEM_H
#define HEROITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "enums.h"


class handCard;
class skillBase;

enum triggerTime_t;

enum camp_t
{
    camp_red,
    camp_blue
};

enum sexual_t
{
    sex_male,
    sex_female
};

class heroItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    Q_PROPERTY(QPoint point READ point WRITE setPoint)

public:

    heroItem(int lineLength);
    void setHeroProperty(char s, char a, char m, int h);

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

    void setCards(QList<handCard*> c){ theCards = c; }
    void addCards(QList<handCard*> c);
    QList<handCard*> cards() { return theCards; }

    void addSkill(skillBase* s);
    void removeSkill(skillBase* s);
    QList<skillBase*> hasSkillTriggerAt(enum triggerTime_t);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);


private:
    QList<skillBase*> skills;
    QList<handCard*> theCards;
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
