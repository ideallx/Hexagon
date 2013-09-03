#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QGraphicsScene>

#include "enums.h"

class ItemCollector;
class GameBackInfo;
class GameCoordinate;
class HeroItem;
class HeroFactory;
class SkillBase;
struct externInfo;

class BackScene : public QGraphicsScene
{
    Q_OBJECT
public:
    BackScene(ItemCollector* ic, QObject *parent = 0);
    ~BackScene();

    ItemCollector* pIc() { return ic;}
    QList<QString> getHeroListAvaterPath(char in);

    void showMoveRange(HeroItem*);
    void showAttackRange(HeroItem* hero);
    void showSkillRange(HeroItem* hero, enum mapRangeType_t, int range);

    
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    ItemCollector *ic;

    QList<QPoint> rangeList;

    QPoint oldPoint;

    QPointF oldPointF;
    QSize oldViewSize;
    bool isPressing;

signals:
    void changeStatusBar(QStringList);
    void mapElementMovedIn(QPoint);
    void mapElementClicked(QPoint);
    void heroClicked(HeroItem*);
    void buildMenu(HeroItem*, QPoint);
    void viewSizeChanged(QSize);
    void rangeClicked(QPoint);
    
public slots:
    void clearRange();
    
};

#endif // BACKSCENE_H
