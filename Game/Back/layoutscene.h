#ifndef LAYOUTSCENE_H
#define LAYOUTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>

class QPainter;

struct essenialContent
{
    int mr;
    int ar;
    int a;
};

class essenialScene : public QGraphicsScene
{
public:
    essenialScene();
    ~essenialScene();

    void setContent(struct essenialContent);

private:
    QString preMr;
    QString preAr;
    QString preA;
    QGraphicsTextItem *moveRange;
    QGraphicsTextItem *attackRange;
    QGraphicsTextItem *attack;

};

class cardScene : public QGraphicsScene
{
public:
    cardScene();
    ~cardScene();
    QGraphicsItemGroup* cardGroup;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

/*
class skillButton : public QGraphicsEllipseItem
{
public :
    skillButton();
    ~skillButton();

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
};
*/

class skillScene : public QGraphicsScene
{
public:
    skillScene();
    ~skillScene();

    void setHeroSkillButton(QList<QPixmap>in);

private:
    QGraphicsEllipseItem *skill1;
    QGraphicsEllipseItem *skill2;
    QGraphicsEllipseItem *skill3;

};

#endif // LAYOUTSCENE_H
