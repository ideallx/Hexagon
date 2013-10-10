#include <QDebug>
#include <QStack>
#include "coordinate.h"
#include "backinfo.h"

GameCoordinate::GameCoordinate(GameBackInfo* gbi) {
    beginX = gbi->getBeginPosition().x();
    beginY = gbi->getBeginPosition().y();
    lineLength = gbi->getLineLength();
    widthCount = gbi->getWidthCount();
    heightCount = gbi->getHeightCount();
    mapElement = gbi->getMapElement();
    halfSqrt3 = 0.86;
}

/*
 *  0,0   1,0   2,0   3,0
 *     0,1   1,1   2,1
 *  0,2   1,2   2,2   3,2
 *     0,3   1,3   2,3
 */
QPointF GameCoordinate::getBeginPosWithCoo(QPoint point) {
    return QPointF(beginX, beginY) + leftUpPosNoOffset(point);
}

QPointF GameCoordinate::leftUpPosNoOffset(QPoint point) {
    if (point.y()%2 == 0)
        return QPointF(3*point.x()*lineLength,
                       point.y()*lineLength*halfSqrt3);
    else
        return QPointF((3*point.x()+1.5)*lineLength,
                       point.y()*lineLength*halfSqrt3);
}

QPointF GameCoordinate::getBeginPosOfHero(QPoint block) {
    return getBeginPosWithCoo(block)+QPointF(0.2*lineLength, 0.06*lineLength);
}

QPointF GameCoordinate::getCenterPosWithCoo(QPoint block) {
    if (block.y()%2 == 0)
        return QPointF(beginX + (3*block.x()+1)*lineLength,
                       beginY + (block.y()+halfSqrt3)*lineLength*halfSqrt3);
    else
        return QPointF(beginX + (3*block.x()+2.5)*lineLength,
                       beginY + (block.y()+halfSqrt3)*lineLength*halfSqrt3);
}

QPoint GameCoordinate::goUpLeft(QPoint coo) {
    QPoint result(coo);
    if (coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()-1);
    return result;
}

QPoint GameCoordinate::goUpRight(QPoint coo) {
    QPoint result(coo);
    if (coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()-1);
    return result;
}

QPoint GameCoordinate::goUp(QPoint coo) {
    QPoint result(coo);
    result.setY(coo.y()-2);
    return result;
}

QPoint GameCoordinate::goDown(QPoint coo) {
    QPoint result(coo);
    result.setY(coo.y()+2);
    return result;
}

QPoint GameCoordinate::goDownLeft(QPoint coo) {
    QPoint result(coo);
    if (coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()+1);
    return result;
}

QPoint GameCoordinate::goDownRight(QPoint coo) {
    QPoint result(coo);
    if (coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()+1);
    return result;
}

QPoint GameCoordinate::getCooxWithPos(QPointF point) {
    QPoint coo;
    // 获取粗略坐标
    double newX = (point.x()-beginX)/(3*lineLength);
    double newY = (point.y()-beginY)/(halfSqrt3*lineLength);
    if (newX < 0)
        newX--;
    if (newY < 0)
        newY--;
    int xInt = static_cast<int>(newX);
    int yInt = static_cast<int>(newY);

    // left part   y is even   right part  y is odd
    if (static_cast<int>(newX+0.5) <= xInt) {
        if (yInt%2 == 1)
            yInt--;
    } else {
        if (yInt%2 == 0)
            yInt--;
    }

    coo.setX(xInt);
    coo.setY(static_cast<int>(yInt));

    double offsetX = point.x() - beginX - coo.x()*3*lineLength;
    offsetX -= coo.y()%2?lineLength*1.5:0;
    double offsetY = point.y() - beginY - coo.y()*halfSqrt3*lineLength;

    // up left fix  down left fix
    if ((offsetX < (lineLength/2)) && (offsetY < lineLength*halfSqrt3)) {
        if (offsetY < (-2*halfSqrt3*offsetX + lineLength*halfSqrt3)) {
            coo = goUpLeft(coo);
        }
    } else if ((offsetX < (lineLength/2)) && (offsetY > lineLength*halfSqrt3)) {
        if (offsetY > (2*halfSqrt3*offsetX + lineLength*halfSqrt3)) {
            coo = goDownLeft(coo);
        }
    }

    return coo;
}

int GameCoordinate::roughDistance(QPoint p1, QPoint p2) {
    TriPoint tp1 = transToTriPoint(p1);
    TriPoint tp2 = transToTriPoint(p2);

    return (qAbs(tp1.x - tp2.x) + qAbs(tp1.y - tp2.y) + qAbs(tp1.z - tp2.z))/2;
}

TriPoint GameCoordinate::transToTriPoint(QPoint p) {
    TriPoint tp;
    tp.x = p.x() + (1+p.y())/2;
    tp.y = 2*p.x() + p.y()%2;
    tp.z = p.x() - p.y()/2;
    return tp;
}
