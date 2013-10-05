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
    int attackRange;
    int attackRangeBouns;
    int moveRange;
    int moveRangeBouns;
    int attack;
    int attackBouns;
    QList<int> moneyList;
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
    void setOneCardMode(bool s) { oneCardMode = s; }
    QList<QGraphicsItem*> getChosenItems() { return chosenItem; }
    QGraphicsItemGroup* cardGroup;

 private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QGraphicsItem* oldItem;
    QGraphicsItem* curItem;
    QList<QGraphicsItem*> chosenItem;
    QTransform qtf;
    bool oneCardMode;

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
    Q_OBJECT
 public:
    SkillScene();
    ~SkillScene();
    void setHeroSkillButton(QList<QPixmap>in);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QGraphicsEllipseItem* getSkill(int n);

 private:
    QGraphicsEllipseItem *skill1;
    QGraphicsEllipseItem *skill2;
    QGraphicsEllipseItem *skill3;

 signals:
    void heroSkillUsed(int n);
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
