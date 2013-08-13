#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QGraphicsScene>

class itemCollector;
class gameBackInfo;
class gameCoordinate;
class heroItem;
class heroFactory;

enum mapRangeType_t
{
    RangeTypeStraight,
    RangeTypeDoubleLine,
    RangeTypeRound

};
struct externInfo;

class backScene : public QGraphicsScene
{
    Q_OBJECT
public:
    backScene(gameBackInfo*, gameCoordinate*, QList<struct externInfo> i, QObject *parent = 0);
    ~backScene();

    itemCollector* pIc() { return ic;}
    gameCoordinate* pGc() { return gc; }
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
    gameBackInfo* gbi;
    gameCoordinate* gc;
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
