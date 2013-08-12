#ifndef GAMECOORDINATE_H
#define GAMECOORDINATE_H

#include <QPoint>
#include <QList>
#include <QVector>

class gameBackInfo;

class gameCoordinate
{
public:
    gameCoordinate(gameBackInfo* gbi);

    QList<QPoint> getMovePoint() const { return showRange; }

    QPoint goUpLeft(QPoint);
    QPoint goUpRight(QPoint);
    QPoint goUp(QPoint);
    QPoint goDownLeft(QPoint);
    QPoint goDownRight(QPoint);
    QPoint goDown(QPoint);

    QPoint getCooxWithPos(QPointF);

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


#endif // GAMECOORDINATE_H
