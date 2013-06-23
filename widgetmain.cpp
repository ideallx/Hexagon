#include "widgetmain.h"
#include "QtWidgets"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent)
{
    gbp = new gameBackPic(QPixmap(":/images/wall2.jpg"));
    if(gbp->isNull())
        QMessageBox::warning(this, "fff", "no pic");

    QPalette palette;
    //palette.setBrush(QPalette::Background, QBrush(*gbp));
    setFixedSize(gbp->width(), gbp->height());
    setPalette(palette);
    setAutoFillBackground(true);

    printIndicator = BLANK_BACKGROUND;
    setMouseTracking(true);

    debugInfo = new QLabel(this);
    debugInfo->setText("Debug Info");

    connect(this, SIGNAL(curBlockChanged(QPoint)), this, SLOT(changeBlock(QPoint)));
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
void WidgetMain::drawSingleShape(QPainter* painter, QPointF begin)
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

/*
 *  0   6
 *    1   7
 *  2   8
 *    3   9
 *  4  10
 *    5  11
 */
void WidgetMain::paintEvent(QPaintEvent *e)
{
    switch(printIndicator)
    {
    case BLANK_BACKGROUND:
        paintInitial();
    case BLOCK_CHOSEN:
        paintFocus();
    }

    printIndicator = BLANK_BACKGROUND;
}

void WidgetMain::repaint()
{
}

void WidgetMain::paintInitial()
{
    QPainter *painter = new QPainter(this);

    int beginX = gbp->getBeginPostion().x();
    int beginY = gbp->getBeginPostion().y();
    qDebug("fff");

    painter->setPen(QColor("red"));
    drawSingleShape(painter, QPointF(50, 50));
    int widthCount = (gbp->width()-beginX)/(sqrt(3.0)*lineLength);
    int heightCount = (gbp->height()-beginY)/(1.5*lineLength);
    QPointF current;
    QPointF display;
    for(int i=0; i<widthCount; i++)
    {
        for(int j=0; j<heightCount; j++)
        {
            if(j%2)
            {
                current = QPointF(beginX + (i+0.5)*sqrt(3.0)*lineLength, beginY + (j/2+0.5)*3*lineLength);
                drawSingleShape(painter, current);
                display = QPointF(current.x()+lineLength/2, current.y()+lineLength);
                painter->drawText(display, QString::number(i) + ',' + QString::number(j));
            }
            else
            {
                current = QPointF(beginX + i*sqrt(3.0)*lineLength, beginY + j/2*3*lineLength);
                drawSingleShape(painter, current);
                display = QPointF(current.x()+lineLength/2, current.y()+lineLength);
                painter->drawText(display, QString::number(i) + ',' + QString::number(j));
            }
        }
    }
    delete painter;
}

WidgetMain::~WidgetMain()
{

}


void WidgetMain::mouseMoveEvent(QMouseEvent *e)
{
    //debugInfo->setText(QString::number(e->pos().x()) + ', ' + QString::number(e->pos().y()));
    int beginX = gbp->getBeginPostion().x();
    int beginY = gbp->getBeginPostion().y();
    double lineLenSqrt3 = sqrt(3.0)*lineLength;

    double newX = (e->pos().x()-beginX)/lineLenSqrt3;
    double newX2 = (e->pos().x()-beginX-(lineLenSqrt3/2))/lineLenSqrt3;
    int cooy = (e->pos().y()-beginY)/(1.5*lineLength);
    double x = cooy%2?newX2:newX;
    int coox = (int)x;

    double offsetX = e->pos().x() - beginX - coox*lineLenSqrt3;
    offsetX -= cooy%2?(lineLenSqrt3/2):0;
    double offsetY = e->pos().y() - beginY - cooy*1.5*lineLength;

    if((offsetX<(sqrt(3.0)*lineLength/2)) && (offsetY<lineLength/2))
    {
        if(offsetY<(-1*offsetX/sqrt(3.0) + lineLength/2))
        {
            if(cooy%2 == 0)
                coox--;
            cooy--;
        }
    }
    else if(offsetY<lineLength/2)
    {
        if(offsetY<(offsetX/sqrt(3.0) - lineLength/2))
        {
            if(cooy%2)
                coox++;
            cooy--;
        }
    }
    update();
    if((curBlock.x() != coox) || (curBlock.y() != cooy))
    {
        emit curBlockChanged(QPoint(coox, cooy));
    }
}

void WidgetMain::changeBlock(QPoint p)
{
    curBlock = QPoint(p.x(), p.y());
    //qDebug("%d, %d", p.x(), p.y());
    debugInfo->setText(QString::number(p.x()) + ", " + QString::number(p.y()));
    printIndicator = BLOCK_CHOSEN;
    update();
}

void WidgetMain::paintFocus(void)
{
    QPainter *painter = new QPainter(this);
    int beginX = gbp->getBeginPostion().x();
    int beginY = gbp->getBeginPostion().y();
    int i = curBlock.x();
    int j = curBlock.y();
    QPointF current;
    QPointF display;
    qDebug("%d, %d", i, j);

    if(i<0 || j<0)
        return;

    if(curBlock.y()%2)
    {
        current = QPointF(beginX + (i+0.5)*sqrt(3.0)*lineLength, beginY + (j/2+0.5)*3*lineLength);
        drawSingleShape(painter, current);
        display = QPointF(current.x()+lineLength/2, current.y()+lineLength);
        painter->drawText(display, QString::number(i) + ',' + QString::number(j) + '!');
    }
    else
    {
        current = QPointF(beginX + i*sqrt(3.0)*lineLength, beginY + j/2*3*lineLength);
        drawSingleShape(painter, current);
        display = QPointF(current.x()+lineLength/2, current.y()+lineLength);
        painter->drawText(display, QString::number(i) + ',' + QString::number(j) + '!');
    }
}
