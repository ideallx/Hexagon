#include "gamecoordinate.h"

gameCoordinate::gameCoordinate(QPoint pos, gameBackInfo* gbi)
{
    gia = new QGraphicsItemAnimation;
    giaTimer = new QTimeLine(500);
    curPoint = pos;
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
QPointF gameCoordinate::getBeginPosWithCoo(QPoint block)
{
    if(block.y()%2 == 0)
        return QPointF(beginX + 3*block.x()*lineLength, beginY + block.y()*lineLength*halfSqrt3);
    else
        return QPointF(beginX + (3*block.x()+1.5)*lineLength, beginY + block.y()*lineLength*halfSqrt3);
}

QPointF gameCoordinate::getBeginPosOfHero(QPoint block)
{
    return getBeginPosWithCoo(block)+QPointF(0.2*lineLength, 0.06*lineLength);
}

QPointF gameCoordinate::getCenterPosWithCoo(QPoint block)
{
    if(block.y()%2 == 0)
        return QPointF(beginX + (3*block.x()+1)*lineLength, beginY + (block.y()+halfSqrt3)*lineLength*halfSqrt3);
    else
        return QPointF(beginX + (3*block.x()+2.5)*lineLength, beginY + (block.y()+halfSqrt3)*lineLength*halfSqrt3);
}

QPoint gameCoordinate::goUpLeft(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()-1);
    return result;
}

QPoint gameCoordinate::goUpRight(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()-1);
    return result;
}

QPoint gameCoordinate::goUp(QPoint coo)
{
    QPoint result(coo);
    result.setY(coo.y()-2);
    return result;
}

QPoint gameCoordinate::goDown(QPoint coo)
{
    QPoint result(coo);
    result.setY(coo.y()+2);
    return result;
}

QPoint gameCoordinate::goDownLeft(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()+1);
    return result;
}

QPoint gameCoordinate::goDownRight(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()+1);
    return result;
}

QPoint gameCoordinate::getCooxWithPos(QPointF point)
{
    QPoint coo;
    //获取粗略坐标
    double newX = (point.x()-beginX)/(3*lineLength);
    double newY = (point.y()-beginY)/(halfSqrt3*lineLength);
    if(newX<0)
        newX--;
    if(newY<0)
        newY--;
    int xInt = (int)newX;
    int yInt = (int)newY;

    if((int)(newX+0.5) <= xInt) //left part   y is even
    {
        if(yInt%2 == 1)
            yInt--;
    }
    else                        //right part  y is odd
    {
        if(yInt%2 == 0)
            yInt--;
    }

    coo.setX(xInt);
    coo.setY((int)yInt);

    double offsetX = point.x() - beginX - coo.x()*3*lineLength;
    offsetX -= coo.y()%2?lineLength*1.5:0;
    double offsetY = point.y() - beginY - coo.y()*halfSqrt3*lineLength;

    //up left fix
    if((offsetX<(lineLength/2)) && (offsetY<lineLength*halfSqrt3))
    {
        if(offsetY<(-2*halfSqrt3*offsetX + lineLength*halfSqrt3))
        {
            coo = goUpLeft(coo);
        }
    }
    //down left fix
    else if((offsetX<(lineLength/2)) && (offsetY>lineLength*halfSqrt3))
    {
        if(offsetY>(2*halfSqrt3*offsetX + lineLength*halfSqrt3))
        {
            coo = goDownLeft(coo);
        }
    }

    return coo;
}


int gameCoordinate::getBlockNumber(QPoint block)
{
    return block.x()+block.y()*widthCount;
}


void gameCoordinate::listAddAsSet(QList<QPoint> *list, QPoint point)
{
    if(list->indexOf(point) == -1)
    {
        list->append(point);
    }
}

bool gameCoordinate::listAddSeies(QList<QPoint> *list, QPoint point)
{
    if(isPointAvailable(point) && isPointMovable(point))
    {
        listAddAsSet(list, point);
        return true;
    }
    return false;
}

void gameCoordinate::listMoveSphere(QPoint block, int sphere)
{
    if(!listAddSeies(&showSphere, block))
        return;
    if(sphere == 0)
        return;
    qDebug("%d, %d", block.x(), block.y());
    sphere--;

    listMoveSphere(goUpLeft(block), sphere);
    listMoveSphere(goUpRight(block), sphere);
    listMoveSphere(goUp(block), sphere);
    listMoveSphere(goDownLeft(block), sphere);
    listMoveSphere(goDownRight(block), sphere);
    listMoveSphere(goDown(block), sphere);

    listAddSeies(&showSphere, goUpLeft(block));
    listAddSeies(&showSphere, goUpRight(block));
    listAddSeies(&showSphere, goUp(block));
    listAddSeies(&showSphere, goDownLeft(block));
    listAddSeies(&showSphere, goDownRight(block));
    listAddSeies(&showSphere, goDown(block));

    return;
}

bool gameCoordinate::isPointAvailable(QPoint in)
{
    if(in.x()<0 || in.y()<0 || in.x()>=widthCount || in.y()>=heightCount)
        return false;
    else if((in.x() == widthCount-1) && (in.y()%2 == 1))
        return false;
    else if(mapElement[getBlockNumber(in)] == 'Z')
        return false;
    else
        return true;
}

bool gameCoordinate::isPointMovable(QPoint in)
{
    return mapList[getBlockNumber(in)]->isMoveAvailable();
}

gameMapElement* gameCoordinate::at(QPoint pos)
{
    int i = getBlockNumber(pos);
    if(i>=mapList.size())
        return 0;
    return mapList.at(i);
}

heroItem* gameCoordinate::heroNum(int i)
{
    if(i>=heroList.size())
        return 0;
    return heroList.at(i);
}

void gameCoordinate::restoreAllPen()
{
    for(int i=0; i<mapList.size(); ++i)
    {
        mapList.at(i)->setPen(QPen(Qt::black, 1));
    }
}
