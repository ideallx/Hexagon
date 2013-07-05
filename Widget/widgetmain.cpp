#include "widgetmain.h"
#include "QtWidgets"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent)
{
    gbp = new gameBackInfo(QPixmap(":/resource/SkinDefault/wallpaper.jpg"), QString(":/resource/SkinDefault/config.xml"));
    if(gbp->isNull())
        QMessageBox::warning(this, "Title", "No Picture");

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(*gbp));

    setFixedSize(gbp->size());
    setPalette(palette);
    setAutoFillBackground(true);
    setMouseTracking(true);

    debugInfo = new QLabel(this);
    debugInfo->setText("Debug Info");

    variableInitial();
    connect(this, SIGNAL(curMoveBlockChanged(QPoint)), this, SLOT(changeBlock(QPoint)));

}

WidgetMain::~WidgetMain()
{
    deleteAllQlist();
    qDeleteAll(map);
    map.clear();

}

void WidgetMain::variableInitial()
{
    if(!gbp->isLoadSuccess())
    {
        emit parentStatusChanged("Loading Map Infomation Failed");
        return;
    }
    beginX = gbp->getBeginPosition().x();
    beginY = gbp->getBeginPosition().y();
    lineLength = gbp->getLineLength();
    widthCount = gbp->getWidthCount()!=0?gbp->getWidthCount():(gbp->width()-beginX)/(sqrt(3.0)*lineLength);
    heightCount = gbp->getHeightCount()!=0?gbp->getHeightCount():(gbp->height()-beginY)/(1.5*lineLength);
    mapElement = gbp->getMapElement();

    printIndicator = BLANK_BACKGROUND;
    curChosenBlock = curMoveBlock = QPoint(-1, -1);


    for(int i=0; i<widthCount*heightCount; i++)
    {
        gameMapElement *gme = new gameMapElement(mapElement[i]);
        map.append(gme);
    }

    QPushButton *moveButton = new QPushButton("Move", this);
    QPushButton *attackButton = new QPushButton("Attack", this);
    moveButton->setGeometry(0, 0, 80, 30);
    attackButton->setGeometry(0, 30, 80, 30);
    menuList.append(moveButton);
    menuList.append(attackButton);
    hideAllQlist(menuList);

    mouseIndicator = MOUSE_NORMAL;

    halfSqrt3 = sqrt(3.0)/2;
    connect(menuList.at(0), SIGNAL(clicked()), this, SLOT(beginMoving()));

    qDebug("%d, %d, %d, %d, %d", beginX, beginY, widthCount, heightCount, lineLength);
}

QSize WidgetMain::getMaxSizeHint()
{
    return QSize(gbp->width()+20, gbp->height()+60);
}

QPainterPath WidgetMain::drawSingleHexagon(QPointF begin)
{
    QPainterPath path;

    QPointF p1 = QPointF(begin.x(),                begin.y() + halfSqrt3*lineLength);
    QPointF p2 = QPointF(begin.x()+0.5*lineLength, begin.y());
    QPointF p3 = QPointF(begin.x()+1.5*lineLength, begin.y());
    QPointF p4 = QPointF(begin.x()+2.0*lineLength, begin.y() + halfSqrt3*lineLength);
    QPointF p5 = QPointF(begin.x()+1.5*lineLength, begin.y() + 2*halfSqrt3*lineLength);
    QPointF p6 = QPointF(begin.x()+0.5*lineLength, begin.y() + 2*halfSqrt3*lineLength);

    path.moveTo(p1);
    path.lineTo(p2);
    path.lineTo(p3);
    path.lineTo(p4);
    path.lineTo(p5);
    path.lineTo(p6);
    path.lineTo(p1);

    return path;
}

// 根据六角形的横纵坐标, 生成P0坐标, 画出六角形, 在图形中间填上横纵坐标
void WidgetMain::drawHexagonSeries(QPainter* painter, QPoint block)
{
    if(!isPointAvailable(block))
        return;
    QPointF current = getBeginPosWithCoo(block);

    QPainterPath path = drawSingleHexagon(current);
    painter->drawPath(path);
    QBrush brush = map.at(block.x()+block.y()*widthCount)->getBrush();
    painter->fillPath(path, brush);

    //painter->drawText(QPointF(current.x()+lineLength/2, current.y()+lineLength), QString::number(mapElement[i]));
}

void WidgetMain::drawMovingLines(QPainter* painter)
{
    for(int i=0; i<moveList.size()-1; i++)
    {
        if((showSphere.indexOf(moveList.at(i)) != -1) && (showSphere.indexOf(moveList.at(i+1)) != -1))
        {
            QPointF display1 = getCenterPosWithCoo(moveList.at(i));
            QPointF display2 = getCenterPosWithCoo(moveList.at(i+1));
            painter->drawLine(display1, display2);
        }
    }
}

int WidgetMain::getBlockEnviroment(QPoint block)
{
    return block.x()+block.y()*widthCount;
}

//地图块不太好一块块画 setBrush所有块统一被画出来， 还是做地图的时候，自己手动画吧
void WidgetMain::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    paintInitial();
    /*
    switch(printIndicator)
    {
    case BLANK_BACKGROUND:
        paintInitial();
    case BLOCK_CHOSEN:
        paintFocus();
    }

    printIndicator = BLOCK_CHOSEN;
    */
}

void WidgetMain::paintInitial()
{
    QPainter *painter = new QPainter(this);
    painter->setPen(QColor("black"));
    painter->setBrush(QBrush(Qt::white));
    painter->setOpacity(0.3);

    for(int i=0; i<widthCount; i++)
    {
        for(int j=0; j<heightCount; j++)
        {
            if(i == curMoveBlock.x() && j == curMoveBlock.y())
                continue;
            drawHexagonSeries(painter, QPoint(i, j));
        }
    }
    if(isPointAvailable(curMoveBlock))
    {
        painter->setPen(QPen(Qt::black, 5));
        drawHexagonSeries(painter, curMoveBlock);
    }
    if(isPointAvailable(curChosenBlock))
    {
        painter->setPen(QPen(Qt::blue, 5));
        drawHexagonSeries(painter, curChosenBlock);
    }
    if(mouseIndicator == MOUSE_MOVING)
    {
        painter->setPen(QPen(Qt::magenta, 10));
        drawMovingLines(painter);

        painter->setPen(QPen(Qt::yellow, 5));
        for (int i=0; i<showSphere.size(); i++)
        {
            drawHexagonSeries(painter, showSphere.at(i));
        }
    }
    delete painter;
}

/*
 *  0,0   1,0   2,0   3,0
 *     0,1   1,1   2,1
 *  0,2   1,2   2,2   3,2
 *     0,3   1,3   2,3
 */
// 根据六角形的横纵坐标, 生成P0坐标,
QPointF WidgetMain::getBeginPosWithCoo(QPoint block)
{
    if(block.y()%2 == 0)
        return QPointF(beginX + 3*block.x()*lineLength, beginY + block.y()*lineLength*halfSqrt3);
    else
        return QPointF(beginX + (3*block.x()+1.5)*lineLength, beginY + block.y()*lineLength*halfSqrt3);
}

QPointF WidgetMain::getCenterPosWithCoo(QPoint block)
{
    if(block.y()%2 == 0)
        return QPointF(beginX + (3*block.x()+1)*lineLength, beginY + (block.y()+halfSqrt3)*lineLength*halfSqrt3);
    else
        return QPointF(beginX + (3*block.x()+2.5)*lineLength, beginY + (block.y()+halfSqrt3)*lineLength*halfSqrt3);
}

QPoint WidgetMain::goUpLeft(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()-1);
    return result;
}

QPoint WidgetMain::goUpRight(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()-1);
    return result;
}

QPoint WidgetMain::goUp(QPoint coo)
{
    QPoint result(coo);
    result.setY(coo.y()-2);
    return result;
}

QPoint WidgetMain::goDown(QPoint coo)
{
    QPoint result(coo);
    result.setY(coo.y()+2);
    return result;
}

QPoint WidgetMain::goDownLeft(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()+1);
    return result;
}

QPoint WidgetMain::goDownRight(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()+1);
    return result;
}

QPoint WidgetMain::getCooxWithPos(QPointF point)
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

void WidgetMain::deleteAllQlist()
{
    for(int i=0; i<menuList.size(); i++)
    {
        delete menuList.at(i);
    }
    menuList.clear();
}

void WidgetMain::showAllQlist(QList<QPushButton*> list, QPoint begin)
{
    for(int i=0; i<list.size(); i++)
    {
        list.at(i)->setGeometry(begin.x(), begin.y()+30*i, 80, 30);
        list.at(i)->show();
    }
}

void WidgetMain::hideAllQlist(QList<QPushButton*> list)
{
    for(int i=0; i<menuList.size(); i++)
    {
        list.at(i)->hide();
    }
}

void WidgetMain::mouseMoveEvent(QMouseEvent *e)
{
    //获取六角形横纵坐标
    QPoint newPoint = getCooxWithPos(e->pos());
    if(curMoveBlock != newPoint)
    {
        emit curMoveBlockChanged(newPoint);
    }
}

void WidgetMain::mousePressEvent(QMouseEvent *e)
{
    hideAllQlist(menuList);
    moveList.clear();
    showSphere.clear();
    mouseIndicator = MOUSE_NORMAL;
    if(e->button() == Qt::LeftButton)
    {
        if(isPointAvailable(curMoveBlock))
        {
            showAllQlist(menuList, e->pos());
        }
        curChosenBlock = curMoveBlock;
    }
    update();
}

void WidgetMain::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

}

void WidgetMain::beginMoving()
{
    mouseIndicator = MOUSE_MOVING;
    moveList.append(curMoveBlock);
    //listAddAsSet(&moveList, curMoveBlock);
    qDebug("click pos %d, %d", curMoveBlock.x(), curMoveBlock.y());

    listMoveSphere(curChosenBlock, 3);
    hideAllQlist(menuList);
    update();
}

bool WidgetMain::isPointAvailable(QPoint in)
{
    if(in.x()<0 || in.y()<0 || in.x()>=widthCount || in.y()>=heightCount)
        return false;
    else if((in.x() == widthCount-1) && (in.y()%2 == 1))
        return false;
    else if(!map.at(getBlockEnviroment(in))->isPointAvailable())
        return false;
    else
        return true;
}

void WidgetMain::changeBlock(QPoint p)
{
    curMoveBlock = QPoint(p.x(), p.y());
    printIndicator = BLOCK_CHOSEN;
    if(isPointAvailable(curMoveBlock))
    {
        if(mouseIndicator == MOUSE_MOVING)
        {
            //listAddAsSet(&moveList, curMoveBlock);
            moveList.append(curMoveBlock);
        }
        qDebug("%d, %d", p.x(), p.y());
        emit parentStatusChanged(map.at(getBlockEnviroment(p))->getElementName());
    }
    else
    {
        qDebug("%d, %d unavailable point", p.x(), p.y());
        emit parentStatusChanged(QString::null);
    }
    update();
}

void WidgetMain::listAddAsSet(QList<QPoint> *list, QPoint point)
{
    if(list->indexOf(point) == -1)
    {
        list->append(point);
    }
}

bool WidgetMain::listAddSeies(QList<QPoint> *list, int sphere, QPoint point)
{
    if(isPointAvailable(point))
    {
        if(map.at(getBlockEnviroment(point))->isMoveAvailable())
        {
            listAddAsSet(list, point);
            return true;
        }
    }
    return false;
}

void WidgetMain::listMoveSphere(QPoint block, int sphere)
{
    if(!listAddSeies(&showSphere, sphere, block))
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

    listAddSeies(&showSphere, sphere, goUpLeft(block));
    listAddSeies(&showSphere, sphere, goUpRight(block));
    listAddSeies(&showSphere, sphere, goUp(block));
    listAddSeies(&showSphere, sphere, goDownLeft(block));
    listAddSeies(&showSphere, sphere, goDownRight(block));
    listAddSeies(&showSphere, sphere, goDown(block));


    return;
}
