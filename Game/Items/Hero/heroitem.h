#ifndef HEROITEM_H
#define HEROITEM_H

#include <QGraphicsItem>
#include <QPainter>

class handCard;

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

    char camp() const { return theCamp;}
    void setCamp(enum camp_t c) { theCamp = c; }

    char sexual() const { return theSexual; }

    char attackSphere() const { return theAttackSphere; }
    char moveSphere() const { return theMoveSphere; }

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

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);


private:
    QList<handCard*> theCards;
    QList<QPixmap> theSkillButtons;
    int theAttack;
    QPixmap* theAvaPic;
    QPixmap* theWhoPic;
    int theMaxHealth;
    int theHealth;
    char theCamp;
    QPoint thePoint;
    char theSexual;
    char theMoveSphere;
    char theAttackSphere;
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
