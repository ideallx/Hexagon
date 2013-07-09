#include "gamebackinfo.h"

gameBackInfo::gameBackInfo(QString configFilePath)
{
    variableInitial(configFilePath);
}

void gameBackInfo::variableInitial(QString configFilePath)
{
    QFile file(configFilePath);
    isLoadingCorrectly = true;
    halfSqrt3 = sqrt(3.0)/2;
    beginX = beginPosition.x();
    beginY = beginPosition.y();

    for(int i=0; i<widthCount*heightCount; i++)
    {
        //gameMapElement *gme = new gameMapElement(mapElement[i]);
        //map.append(gme);
    }

    try
    {
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            throw QString("cant open file %1").arg(configFilePath);
        }

        QXmlStreamReader xml(file.readAll());
        if(xml.readNextStartElement())
        {
            if(xml.name() == "skin")
            {
                widthCount = xml.attributes().value("widthCount").toString().toInt();
                heightCount = xml.attributes().value("heightCount").toString().toInt();
                lineLength = xml.attributes().value("lineLength").toString().toInt();

                QStringList temp = xml.attributes().value("beginPosition").toString().split(", ");
                beginPosition = QPointF(temp[0].toDouble(), temp[1].toDouble());
                backgroundPicture = QPixmap(xml.attributes().value("backpic").toString());
                if(backgroundPicture.isNull())
                    throw QString("no pic");

                temp = xml.attributes().value("mapElement").toString().simplified().split(", ");
                for(int i=0; i<heightCount; i++)
                {
                    if(temp[i].length() != widthCount)
                    {
                        throw QString("wrong map element");
                    }
                    for(int j=0; j<widthCount; j++)
                    {
                        mapElement.append(temp[i][j].toLatin1());
                    }
                }
            }
        }
    }catch(QString e)
    {
        qDebug(qPrintable(e));
        isLoadingCorrectly = false;
    }
}

/*
 *  0,0   1,0   2,0   3,0
 *     0,1   1,1   2,1
 *  0,2   1,2   2,2   3,2
 *     0,3   1,3   2,3
 */
// 根据六角形的横纵坐标, 生成P0坐标,
QPointF gameBackInfo::getBeginPosWithCoo(QPoint block)
{
    if(block.y()%2 == 0)
        return QPointF(beginX + 3*block.x()*lineLength, beginY + block.y()*lineLength*halfSqrt3);
    else
        return QPointF(beginX + (3*block.x()+1.5)*lineLength, beginY + block.y()*lineLength*halfSqrt3);
}

QPointF gameBackInfo::getCenterPosWithCoo(QPoint block)
{
    if(block.y()%2 == 0)
        return QPointF(beginX + (3*block.x()+1)*lineLength, beginY + (block.y()+halfSqrt3)*lineLength*halfSqrt3);
    else
        return QPointF(beginX + (3*block.x()+2.5)*lineLength, beginY + (block.y()+halfSqrt3)*lineLength*halfSqrt3);
}

QPoint gameBackInfo::goUpLeft(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()-1);
    return result;
}

QPoint gameBackInfo::goUpRight(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()-1);
    return result;
}

QPoint gameBackInfo::goUp(QPoint coo)
{
    QPoint result(coo);
    result.setY(coo.y()-2);
    return result;
}

QPoint gameBackInfo::goDown(QPoint coo)
{
    QPoint result(coo);
    result.setY(coo.y()+2);
    return result;
}

QPoint gameBackInfo::goDownLeft(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()+1);
    return result;
}

QPoint gameBackInfo::goDownRight(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()+1);
    return result;
}

QPoint gameBackInfo::getCooxWithPos(QPointF point)
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


int gameBackInfo::getBlockNumber(QPoint block)
{
    return block.x()+block.y()*widthCount;
}


void gameBackInfo::listAddAsSet(QList<QPoint> *list, QPoint point)
{
    if(list->indexOf(point) == -1)
    {
        list->append(point);
    }
}

bool gameBackInfo::listAddSeies(QList<QPoint> *list, QPoint point)
{
    if(isPointAvailable(point))
    {
        if(map.at(getBlockNumber(point))->isMoveAvailable())
        {
            listAddAsSet(list, point);
            return true;
        }
    }
    return false;
}

void gameBackInfo::listMoveSphere(QPoint block, int sphere)
{
    if(!listAddSeies(&showSphere, block))
        return;
    if(sphere == 0)
        return;
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

bool gameBackInfo::isPointAvailable(QPoint in)
{
    if(in.x()<0 || in.y()<0 || in.x()>=widthCount || in.y()>=heightCount)
        return false;
    else if((in.x() == widthCount-1) && (in.y()%2 == 1))
        return false;
    else if(!map.at(getBlockNumber(in))->isPointAvailable())
        return false;
    else
        return true;
}
