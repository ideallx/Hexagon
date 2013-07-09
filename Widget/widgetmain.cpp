#include "widgetmain.h"
#include "QtWidgets"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent)
{
    gbi = new gameBackInfo(QString(":/resource/SkinDefault/config.xml"));
    if(gbi->getPixmap().isNull())
        QMessageBox::warning(this, "Title", "No Picture");

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(gbi->getPixmap()));
    //palette.setBrush(QPalette::Background, QBrush(Qt::darkBlue));

    setFixedSize(gbi->getPixmap().size());
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
    if(!gbi->isLoadSuccess())
    {
        emit parentStatusChanged("Loading Map Infomation Failed");
        return;
    }
    lineLength = gbi->getLineLength();
    halfSqrt3 = sqrt(3)*lineLength/2;
}

QSize WidgetMain::getMaxSizeHint()
{
    return QSize(gbi->getPixmap().width()+20, gbi->getPixmap().height()+60);
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
    if(!gbi->isPointAvailable(block))
        return;
    QPointF current = gbi->getBeginPosWithCoo(block);

    QPainterPath path = drawSingleHexagon(current);
    painter->drawPath(path);
    //QBrush brush = map.at(block.x()+block.y()*widthCount)->getBrush();
    //painter->fillPath(path, brush);

    //painter->drawText(QPointF(current.x()+lineLength/2, current.y()+lineLength), QString::number(mapElement[i]));
}

void WidgetMain::drawMovingLines(QPainter* painter)
{
//    for(int i=0; i<moveList.size()-1; i++)
//    {
//        if((showSphere.indexOf(moveList.at(i)) != -1) && (showSphere.indexOf(moveList.at(i+1)) != -1))
//        {
//            QPointF display1 = gbi->getCenterPosWithCoo(moveList.at(i));
//            QPointF display2 = gbi->getCenterPosWithCoo(moveList.at(i+1));
//            painter->drawLine(display1, display2);
//        }
//    }
}


//地图块不太好一块块画 setBrush所有块统一被画出来， 还是做地图的时候，自己手动画吧
void WidgetMain::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    //paintInitial();
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
    if(gbi->isPointAvailable(curMoveBlock))
    {
        painter->setPen(QPen(Qt::black, 5));
        drawHexagonSeries(painter, curMoveBlock);
    }
    if(gbi->isPointAvailable(curChosenBlock))
    {
        painter->setPen(QPen(Qt::blue, 5));
        drawHexagonSeries(painter, curChosenBlock);
    }
//    if(mouseIndicator == MOUSE_MOVING)
//    {
//        painter->setPen(QPen(Qt::magenta, 10));
//        drawMovingLines(painter);

//        painter->setPen(QPen(Qt::yellow, 5));
//        qDebug("begin ff");
//        for (int i=0; i<showSphere.size(); i++)
//        {
//            drawHexagonSeries(painter, showSphere.at(i));
//        }
//    }
    delete painter;
}


void WidgetMain::mouseMoveEvent(QMouseEvent *e)
{
    //获取六角形横纵坐标
    QPoint newPoint = gbi->getCooxWithPos(e->pos());
    if(curMoveBlock != newPoint)
    {
        emit curMoveBlockChanged(newPoint);
    }
}

void WidgetMain::mousePressEvent(QMouseEvent *e)
{
    /*
    globol::menu->hideAllMenu();
//    moveList.clear();
//    showSphere.clear();
//    mouseIndicator = MOUSE_NORMAL;
    if(e->button() == Qt::LeftButton)
    {
        if(gbi->isPointAvailable(curMoveBlock))
        {
            //showAllQlist(menuList, e->pos());
        }
        curChosenBlock = curMoveBlock;
    }
    emit mousePressed();
    update();
    */
}

void WidgetMain::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

}

void WidgetMain::beginMoving()
{
//    mouseIndicator = MOUSE_MOVING;
//    moveList.append(curMoveBlock);
    //listAddAsSet(&moveList, curMoveBlock);
    qDebug("click pos %d, %d", curMoveBlock.x(), curMoveBlock.y());

    gbi->listMoveSphere(curChosenBlock, 3);
    //hideAllQlist(menuList);
    this->repaint();
}


void WidgetMain::changeBlock(QPoint p)
{
//    curMoveBlock = QPoint(p.x(), p.y());
//    printIndicator = BLOCK_CHOSEN;
//    if(gbi->isPointAvailable(curMoveBlock))
//    {
//        if(mouseIndicator == MOUSE_MOVING)
//        {
//            moveList.append(curMoveBlock);
//        }
//        qDebug("%d, %d", p.x(), p.y());
//        emit parentStatusChanged(map.at(gbi->getBlockNumber(p))->getElementName());
//    }
//    else
//    {
//        qDebug("%d, %d unavailable point", p.x(), p.y());
//        emit parentStatusChanged(QString::null);
//    }
//    update();
}

