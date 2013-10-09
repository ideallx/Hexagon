#ifndef GAME_BACK_COORDINATE_H_
#define GAME_BACK_COORDINATE_H_

#include <QPoint>
#include <QList>
#include <QQueue>
#include <QVector>
#include "enums.h"

// ALGORITHM

class GameBackInfo;

class GameCoordinate {
 public:

    explicit GameCoordinate(GameBackInfo* gbi);
    QList<QPoint> getMovePoint() const { return showRange; }
    static QPoint goUpLeft(QPoint);
    static QPoint goUpRight(QPoint);
    static QPoint goUp(QPoint);
    static QPoint goDownLeft(QPoint);
    static QPoint goDownRight(QPoint);
    static QPoint goDown(QPoint);

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
