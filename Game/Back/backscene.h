#ifndef GAME_BACK_BACKSCENE_H_
#define GAME_BACK_BACKSCENE_H_

#include <QGraphicsScene>

#include "enums.h"

class ItemCollector;
class GameBackInfo;
class GameCoordinate;
class HeroItem;
class HeroFactory;
class SkillBase;
class externInfo;

class BackScene : public QGraphicsScene {
    Q_OBJECT

 public:
    BackScene(ItemCollector* ic, QObject *parent = 0);
    ~BackScene();

    inline ItemCollector* pIc() { return ic;}
    QList<QString> getHeroListAvaterPath(Camp c);
    void showMoveRange(HeroItem* hero);
    void showAttackRange(HeroItem* hero);
    void showSkillRange(HeroItem* hero, MapRangeType, int range);
    void showBirthSquare(Camp camp, QList<QPoint> unshow);
    void showRangePoints(QList<QPoint> lp);
    QList<QPoint> getSkillRange(QPoint o, MapRangeType, int range);
    QPoint getLastPoint() { return oldPoint; }
    bool isPointInRange(QPoint in) { return rangeList.contains(in); }

 private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void restoreOldPoint(QPoint old);

 private:
    ItemCollector *ic;
    QList<QPoint> rangeList;
    QPoint oldPoint;
    QPointF oldPointF;
    QSize oldViewSize;
    bool isPressing;

 signals:
    void changeStatusBar(QStringList sl);
    void mapElementMovedIn(QPoint p);
    void mapElementClicked(QPoint p);
    void heroClicked(HeroItem* h);
    void heroMovedIn(HeroItem *h);
    void buildMenu(HeroItem* h, QPoint p);
    void viewSizeChanged(QSize s);
    void rangeClicked(QPoint p);

 public slots:
    void clearRange();
};

#endif  // GAME_BACK_BACKSCENE_H_
