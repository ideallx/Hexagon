#ifndef GAME_BACK_COORDINATE_H_
#define GAME_BACK_COORDINATE_H_

#include <QPoint>
#include <QList>
#include <QQueue>
#include <QVector>
#include "enums.h"

// ALGORITHM

class GameBackInfo;

//Transfer 2-dimension coordinate into 3-dimension coordinate
//To calculate the distance and so on
class TriPoint {
 public:
    int x;
    int y;
    int z;
};

class GameCoordinate {
 public:

    explicit GameCoordinate(GameBackInfo* gbi);
    inline QList<QPoint> getMovePoint() const { return showRange; }
    static QPoint goUpLeft(QPoint);
    static QPoint goUpRight(QPoint);
    static QPoint goUp(QPoint);
    static QPoint goDownLeft(QPoint);
    static QPoint goDownRight(QPoint);
    static QPoint goDown(QPoint);
    static int roughDistance(QPoint p1, QPoint p2);
    static TriPoint transToTriPoint(QPoint p);
    static QList<QPoint> aroundPoint(QPoint p);

    QPoint getCooxWithPos(QPointF);
    QPointF leftUpPosNoOffset(QPoint);
    QPointF getBeginPosWithCoo(QPoint);
    QPointF getBeginPosOfHero(QPoint);
    QPointF getCenterPosWithCoo(QPoint);

 private:
    int beginX;
    int beginY;
    int lineLength;
    double halfSqrt3;
    int widthCount;
    int heightCount;
    QVector<char> mapElement;
    QList<QPoint> showRange;
};


#endif  // GAME_BACK_COORDINATE_H_
