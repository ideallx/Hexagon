#ifndef GAME_BACK_LAYOUTSCENE_H_
#define GAME_BACK_LAYOUTSCENE_H_

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QDebug>
#include <QVector>
#include <QGraphicsSceneMouseEvent>

class HandCard;

struct panelInfo {
    QString attackRange;
    QString moveRange;
    QString attack;
    QString money;
};

class EssenialScene : public QGraphicsScene {
 public:
    EssenialScene();
    ~EssenialScene();

    void setContent(struct panelInfo);

 private:
    QString preMr;
    QString preAr;
    QString preA;
    QString preMo;
    QGraphicsTextItem *moveRange;
    QGraphicsTextItem *attackRange;
    QGraphicsTextItem *attack;
    QGraphicsTextItem *money;
};

class CardScene : public QGraphicsScene {
    Q_OBJECT

 public:
    CardScene();
    ~CardScene();
    void clearChosenItems();
    void listCards();
    QList<QGraphicsItem*> getChosenItems() { return chosenItem; }
    QGraphicsItemGroup* cardGroup;

 private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QGraphicsItem* oldItem;
    QGraphicsItem* curItem;
    QList<QGraphicsItem*> chosenItem;
    QTransform qtf;

 signals:
    void chosenNCard(int n);
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

class SkillScene : public QGraphicsScene {
 public:
    SkillScene();
    ~SkillScene();
    void setHeroSkillButton(QList<QPixmap>in);

 private:
    QGraphicsEllipseItem *skill1;
    QGraphicsEllipseItem *skill2;
    QGraphicsEllipseItem *skill3;
};

class ViewSendResize : public QGraphicsView {
    Q_OBJECT

 public:
    explicit ViewSendResize(QWidget *parent = 0);
    ~ViewSendResize();
    void resizeEvent(QResizeEvent *e);

 signals:
    void resized();
};

#endif  // GAME_BACK_LAYOUTSCENE_H_
