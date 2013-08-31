#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QGraphicsScene>

#include "enums.h"

class itemCollector;
class gameBackInfo;
class gameCoordinate;
class heroItem;
class heroFactory;
class skillBase;
struct externInfo;

class backScene : public QGraphicsScene
{
    Q_OBJECT
public:
    backScene(itemCollector* ic, QObject *parent = 0);
    ~backScene();

    itemCollector* pIc() { return ic;}
    QList<QString> getHeroListAvaterPath(char in);

    void showMoveRange(heroItem*);
    void showAttackRange(heroItem* hero);
    void showSkillRange(heroItem* hero, enum mapRangeType_t, int range);

    
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    itemCollector *ic;

    QList<QPoint> rangeList;

    QPoint oldPoint;

    QPointF oldPointF;
    QSize oldViewSize;
    bool isPressing;

signals:
    void changeStatusBar(QStringList);
    void mapElementMovedIn(QPoint);
    void mapElementClicked(QPoint);
    void heroClicked(heroItem*);
    void buildMenu(heroItem*, QPoint);
    void viewSizeChanged(QSize);
    void rangeClicked(QPoint);
    
public slots:
    void clearRange();
    
};

#endif // BACKSCENE_H
