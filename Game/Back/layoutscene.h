#ifndef LAYOUTSCENE_H
#define LAYOUTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QDebug>
#include <QVector>
#include <QGraphicsSceneMouseEvent>


struct panelInfo
{
    QString attackRange;
    QString moveRange;
    QString attack;
};

class essenialScene : public QGraphicsScene
{
public:
    essenialScene();
    ~essenialScene();

    void setContent(struct panelInfo);

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
    void clearChosenItems();
    void listCards();
    QGraphicsItemGroup* cardGroup;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QGraphicsItem* oldItem;
    QGraphicsItem* curItem;
    QVector<QGraphicsItem*> chosenItem;
    QTransform qtf;
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

class viewSendResize : public QGraphicsView
{
    Q_OBJECT
public:
    viewSendResize(QWidget *parent = 0);
    ~viewSendResize();
    void resizeEvent(QResizeEvent *e);

signals:
    void resized();
};

#endif // LAYOUTSCENE_H
