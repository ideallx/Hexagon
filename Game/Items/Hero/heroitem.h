#ifndef HEROITEM_H
#define HEROITEM_H

#include <QtWidgets>

class heroItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    Q_PROPERTY(QPoint point READ getPoint WRITE setPoint)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    typedef enum camp_t
    {
        camp_red,
        camp_blue
    }heroCamp;

    enum sexual_t
    {
        sex_male,
        sex_female
    };

    heroItem(int lineLength);
    virtual void initial() {}

    char getCamp() const { return camp;}
    void setCamp(heroCamp c) { camp = c; }
    char getSexual() const { return sexual; }
    char getAttackSphere() const { return attackSphere; }
    char getMoveSphere() const { return moveSphere; }
    int health() const { return innerHealth; }
    void setHealth(int h) { innerHealth = h; }

    void setHeroProperty(char s, char a, char m, int h){sexual = s; attackSphere = a; moveSphere = m; innerHealth = h;}

    QString getPlayerName() const { return playerName; }
    QString getHeroName() const { return heroName; }
    void setHeroName(QString n) { heroName = n; }

    QPoint getPoint() const { return point;}
    void setPoint(QPoint p) { point = p; }

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);

private:
    int innerHealth;
    char camp;
    QPoint point;
    char sexual;
    char moveSphere;
    char attackSphere;
    QString playerName;
    QString heroName;

    int lineLength;
    QColor color;


signals:
    void mouseClicked(QGraphicsSceneMouseEvent *event);
    void heroInvokeMenu(QPointF);
    void changeStatus(QString);
};

#endif // HEROITEM_H
