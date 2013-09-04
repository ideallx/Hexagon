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
struct externInfo;

class BackScene : public QGraphicsScene {
    Q_OBJECT

 public:
    BackScene(ItemCollector* ic, QObject *parent = 0);
    ~BackScene();

    ItemCollector* pIc() { return ic;}
    QList<QString> getHeroListAvaterPath(enum camp_t c);
    void showMoveRange(HeroItem* hero);
    void showAttackRange(HeroItem* hero);
    void showSkillRange(HeroItem* hero, enum mapRangeType_t, int range);
    void showBirthSquare(enum camp_t camp);

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
    enum mode_t {
        ModeChooseBirth,
        ModeNormal
    };
    enum mode_t mode;

 signals:
    void changeStatusBar(QStringList sl);
    void mapElementMovedIn(QPoint p);
    void mapElementClicked(QPoint p);
    void heroClicked(HeroItem* h);
    void buildMenu(HeroItem* h, QPoint p);
    void viewSizeChanged(QSize s);
    void rangeClicked(QPoint p);

 public slots:
    void clearRange();
};

#endif  // GAME_BACK_BACKSCENE_H_
