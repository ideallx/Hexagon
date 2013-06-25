#include "widgetmain.h"
#include "QtWidgets"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent)
{
    gbp = new gameBackPic(QPixmap(":/images/wall2.jpg"));
    if(gbp->isNull())
        QMessageBox::warning(this, "Title", "No Picture");

    QPalette palette;
    //palette.setBrush(QPalette::Background, QBrush(*gbp));
    setFixedSize(gbp->width(), gbp->height());
    setPalette(palette);
    setAutoFillBackground(true);

    setMouseTracking(true);

    debugInfo = new QLabel(this);
    debugInfo->setText("Debug Info");

    variableInitial();
    connect(this, SIGNAL(curBlockChanged(QPoint)), this, SLOT(changeBlock(QPoint)));
}

void WidgetMain::variableInitial()
{
    beginX = gbp->getBeginPostion().x();
    beginY = gbp->getBeginPostion().y();
    lineLength = gbp->getLineLength();
    widthCount = gbp->getWidthCount()!=0?gbp->getWidthCount():(gbp->width()-beginX)/(sqrt(3.0)*lineLength);
    heightCount = gbp->getHeightCount()!=0?gbp->getHeightCount():(gbp->height()-beginY)/(1.5*lineLength);
    printIndicator = BLANK_BACKGROUND;

    qDebug("%d, %d, %d, %d, %d", beginX, beginY, widthCount, heightCount, lineLength);
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
void WidgetMain::drawSingleHexagon(QPainter* painter, QPointF begin)
{
    QPointF p1 = QPointF(begin.x(),                        begin.y() + lineLength/2);
    QPointF p2 = QPointF(begin.x()+sqrt(3.0)/2*lineLength, begin.y());
    QPointF p3 = QPointF(begin.x()+sqrt(3.0)*lineLength,   begin.y() + lineLength/2);
    QPointF p4 = QPointF(begin.x()+sqrt(3.0)*lineLength,   begin.y() + 1.5*lineLength);
    QPointF p5 = QPointF(begin.x()+sqrt(3.0)/2*lineLength, begin.y() + 2*lineLength);
    QPointF p6 = QPointF(begin.x(),                        begin.y() + 1.5*lineLength);

    painter->drawLine(p1, p2);
    painter->drawLine(p2, p3);
    painter->drawLine(p3, p4);
    painter->drawLine(p4, p5);
    painter->drawLine(p5, p6);
    painter->drawLine(p6, p1);
}

// 根据六角形的横纵坐标, 生成P0坐标, 画出六角形, 在图形中间填上横纵坐标
void WidgetMain::drawHexagonSeries(QPainter* painter, QPoint block)
{
    QPointF current = getBeginPosWithCoo(block);
    drawSingleHexagon(painter, current);
    painter->drawText(QPointF(current.x()+lineLength/2, current.y()+lineLength), QString::number(block.x()) + ',' + QString::number(block.y()));
}

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
/*
 *  0,0   1,0   2,0   3,0
 *     0,1   1,1   2,1
 *  0,2   1,2   2,2   3,2
 *     0,3   1,3   2,3
 */
// 根据六角形的横纵坐标, 生成P0坐标,
QPointF WidgetMain::getBeginPosWithCoo(QPoint block)
{
    int beginX = gbp->getBeginPostion().x();
    int beginY = gbp->getBeginPostion().y();

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

//略有问题 但影响不大
QPoint WidgetMain::getCooxWithPos(QPointF point)
{
    double lineLenSqrt3 = sqrt(3.0)*lineLength;
    QPoint coo;

    //获取粗略坐标
    double newX = (point.x()-beginX)/lineLenSqrt3;
    double newX2 = (point.x()-beginX-(lineLenSqrt3/2))/lineLenSqrt3;
    coo.setY((point.y()-beginY)/(1.5*lineLength));
    double x = coo.y()%2?newX2:newX;
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

    //第二次修正，左侧边沿
    //TODO
    return coo;
}

void WidgetMain::paintInitial()
{
    QPainter *painter = new QPainter(this);
    painter->setPen(QColor("red"));
    drawSingleHexagon(painter, QPointF(50, 50));

    for(int i=0; i<widthCount; i++)
    {
        for(int j=0; j<heightCount; j++)
        {
            if(i == curBlock.x() && j == curBlock.y())
                continue;
            drawHexagonSeries(painter, QPoint(i, j));
        }
    }
    painter->setPen(QPen(Qt::black, 5));
    drawHexagonSeries(painter, curBlock);
    delete painter;
}

WidgetMain::~WidgetMain()
{

}


void WidgetMain::mouseMoveEvent(QMouseEvent *e)
{
    //获取六角形横纵坐标
    QPoint newPoint = getCooxWithPos(e->pos());
    if(curBlock != newPoint)
    {
        emit curBlockChanged(newPoint);
    }
}

void WidgetMain::mousePressEvent(QMouseEvent *e)
{
    QPushButton *ddd = new QPushButton("ddd", this);
    QPushButton *eee = new QPushButton("eee", this);
    menuList.append(ddd);
    menuList.append(eee);
    ddd->show();
    eee->show();
    qDebug("fdsf");
}

void WidgetMain::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    for(int i=0; i<menuList.size(); i++)
    {
        delete menuList.at(i);
    }
    menuList.clear();

}

void WidgetMain::changeBlock(QPoint p)
{
    curBlock = QPoint(p.x(), p.y());
    if(curBlock.x()<0 || curBlock.y()<0 || curBlock.x()>=widthCount || curBlock.y()>=heightCount)
        return;
    qDebug("%d, %d", p.x(), p.y());
    printIndicator = BLOCK_CHOSEN;
    update();
}

void WidgetMain::paintFocus(void)
{
    QPainter *painter = new QPainter(this);
    painter->setPen(QColor("red"));

    drawHexagonSeries(painter, curBlock);
}
