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

    for (int i = 0; i < widthCount; i++) {
        QList<struct RecursivePoint_t> list;
        for (int j = 0; j < heightCount; j++) {
            struct RecursivePoint_t point;
            point.parent = outPoint();
            point.self = QPoint(i, j);
            point.state = NotChecked;
            list.append(point);
        }
        points.append(list);
    }
}

void GameCoordinate::clearPoints() {
    foreach(QList<struct RecursivePoint_t> list, points) {
        foreach(struct RecursivePoint_t point, list) {
            point.parent = outPoint();
            point.state = NotChecked;
        }
    }
}

GameCoordinate::RecursivePoint_t GameCoordinate::getStruct(QPoint in) {
    return points[in.x()][in.y()];
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

// breadth-first search
QList<QPoint> GameCoordinate::path (QPoint from, QPoint to) {
    queue.clear();
    QList<QPoint> result;

    if (!addPointToQueue(from, outPoint()))
        return result;

    clearPoints();
    while (!queue.isEmpty()) {
        struct RecursivePoint_t ss = queue.dequeue();
        ss.state = Checked;
        from = ss.self;
        if (to == goUp(from)) {
            break;
        }
        addPointToQueue(goUp(from), from);
        addPointToQueue(goUpLeft(from), from);
        addPointToQueue(goUpRight(from), from);
        addPointToQueue(goDown(from), from);
        addPointToQueue(goDownLeft(from), from);
        addPointToQueue(goDownRight(from), from);
    }

    // TODO return
}

bool GameCoordinate::addPointToQueue(QPoint p, QPoint from) {
    if (checkPointAvailable(p)) {
        struct RecursivePoint_t ss = getStruct(p);
        if (ss.state == NotChecked) {
            queue.append(ss);
            ss.parent = from;
            ss.state = Added;
            return true;
        }
    }
    return false;
}


bool GameCoordinate::checkPointAvailable(QPoint in) {
    if (in.x() < 0 || in.y() < 0 || in.x() >= widthCount || in.y() >= heightCount)
        return false;
    else if ((in.x() == widthCount-1) && (in.y()%2 == 1) && (widthCount%2 == 0))
        return false;
    else
        return true;
}
