#include "widgetmain.h"
#include "QtWidgets"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent)
{
    gbp = new gameBackInfo(QPixmap(":/resource/SkinDefault/wallpaper.jpg"), QString(":/resources/SkinDefault/config.xml"));
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

}

void WidgetMain::variableInitial()
{
    beginX = gbp->getBeginPosition().x();
    beginY = gbp->getBeginPosition().y();
    lineLength = gbp->getLineLength();
    widthCount = gbp->getWidthCount()!=0?gbp->getWidthCount():(gbp->width()-beginX)/(sqrt(3.0)*lineLength);
    heightCount = gbp->getHeightCount()!=0?gbp->getHeightCount():(gbp->height()-beginY)/(1.5*lineLength);
    mapElement = gbp->getMapElement();

    printIndicator = BLANK_BACKGROUND;
    curChosenBlock = curMoveBlock = QPoint(-1, -1);

    qDebug("%d, %d, %d, %d, %d", beginX, beginY, widthCount, heightCount, lineLength);
}

QSize WidgetMain::getMaxSizeHint()
{
    return QSize(gbp->width()+20, gbp->height()+60);
}

//
//  p0  p2  q0  q2
//  p1      p3     q3
//
//  p6  r0  p4     q4
//      p5      q5
//
//      r6      r4
//          r5
//
// 根据P0的坐标 画出六角形
QPainterPath WidgetMain::drawSingleHexagon(QPointF begin)
{
    QPainterPath path;
    QPointF p1 = QPointF(begin.x(),                        begin.y() + lineLength/2);
    QPointF p2 = QPointF(begin.x()+sqrt(3.0)/2*lineLength, begin.y());
    QPointF p3 = QPointF(begin.x()+sqrt(3.0)*lineLength,   begin.y() + lineLength/2);
    QPointF p4 = QPointF(begin.x()+sqrt(3.0)*lineLength,   begin.y() + 1.5*lineLength);
    QPointF p5 = QPointF(begin.x()+sqrt(3.0)/2*lineLength, begin.y() + 2*lineLength);
    QPointF p6 = QPointF(begin.x(),                        begin.y() + 1.5*lineLength);

    path.moveTo(p1);
    path.lineTo(p2);
    path.lineTo(p3);
    path.lineTo(p4);
    path.lineTo(p5);
    path.lineTo(p6);
    path.lineTo(p1);\

    return path;
}

// 根据六角形的横纵坐标, 生成P0坐标, 画出六角形, 在图形中间填上横纵坐标
void WidgetMain::drawHexagonSeries(QPainter* painter, QPoint block)
{
    QPointF current = getBeginPosWithCoo(block);
    QPainterPath path = drawSingleHexagon(current);
    painter->drawPath(path);

    int i = block.x()*widthCount+block.y();
    painter->drawText(QPointF(current.x()+lineLength/2, current.y()+lineLength), QString::number(mapElement[i]));
}

//地图块不太好一块块画 setBrush所有块统一被画出来， 还是做地图的时候，自己手动画吧
void WidgetMain::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    /*
    switch(printIndicator)
    {
    case BLANK_BACKGROUND:
        paintInitial();
    case BLOCK_CHOSEN:
        paintFocus();
    }
    */
    paintInitial();

    printIndicator = BLANK_BACKGROUND;
}

void WidgetMain::paintInitial()
{
    QPainter *painter = new QPainter(this);
    //painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QColor("black"));
    painter->setBrush(QBrush(Qt::white));
    painter->setOpacity(0.5);

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
    if(block.y()%2)
        return QPointF(beginX + (block.x()+0.5)*sqrt(3.0)*lineLength, beginY + (block.y()/2+0.5)*3*lineLength);
    else
        return QPointF(beginX + block.x()*sqrt(3.0)*lineLength, beginY + block.y()/2*3*lineLength);

}

QPoint WidgetMain::goTopLeft(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 0)
        result.setX(coo.x()-1);
    result.setY(coo.y()-1);
    return result;
}

QPoint WidgetMain::goTopRight(QPoint coo)
{
    QPoint result(coo);
    if(coo.y()%2 == 1)
        result.setX(coo.x()+1);
    result.setY(coo.y()-1);
    return result;
}

//改好了。不需要第二次修正，double转int，负0.x会转成0，x--就可以了
QPoint WidgetMain::getCooxWithPos(QPointF point)
{
    double lineLenSqrt3 = sqrt(3.0)*lineLength;
    QPoint coo;

    //获取粗略坐标
    double newX = (point.x()-beginX)/lineLenSqrt3;
    double newX2 = (point.x()-beginX-(lineLenSqrt3/2))/lineLenSqrt3;
    coo.setY((point.y()-beginY)/(1.5*lineLength));
    double x = coo.y()%2?newX2:newX;
    if(x<0)
        x--;
    coo.setX((int)x);

    double offsetX = point.x() - beginX - coo.x()*lineLenSqrt3;
    offsetX -= coo.y()%2?(lineLenSqrt3/2):0;
    double offsetY = point.y() - beginY - coo.y()*1.5*lineLength;

    //第一次修正，上边沿
    if((offsetX<(sqrt(3.0)*lineLength/2)) && (offsetY<lineLength/2))
    {
        if(offsetY<(-1*offsetX/sqrt(3.0) + lineLength/2))
        {
            coo = goTopLeft(coo);
        }
    }
    else if(offsetY<lineLength/2)
    {
        if(offsetY<(offsetX/sqrt(3.0) - lineLength/2))
        {
            coo = goTopRight(coo);
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
    deleteAllQlist();
    if((e->button() == Qt::LeftButton))
    {
        if(isPointAvailable(curMoveBlock))
        {
            QPushButton *ddd = new QPushButton("ddd", this);
            QPushButton *eee = new QPushButton("eee", this);
            ddd->setGeometry(e->pos().x(), e->pos().y(), 80, 30);
            eee->setGeometry(e->pos().x(), e->pos().y()+30, 80, 30);
            menuList.append(ddd);
            menuList.append(eee);
            ddd->show();
            eee->show();
        }
        curChosenBlock = curMoveBlock;
        update();
    }
}

void WidgetMain::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

}

bool WidgetMain::isPointAvailable(QPoint in)
{
    if(in.x()<0 || in.y()<0 || in.x()>=widthCount || in.y()>=heightCount)
        return false;
    else
        return true;
}

void WidgetMain::changeBlock(QPoint p)
{
    curMoveBlock = QPoint(p.x(), p.y());
    if(isPointAvailable(curMoveBlock))
    {
        qDebug("%d, %d", p.x(), p.y());
    }
    else
    {
        qDebug("%d, %d out of range", p.x(), p.y());
    }
    printIndicator = BLOCK_CHOSEN;
    update();
}
