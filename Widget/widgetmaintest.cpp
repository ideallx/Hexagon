#include "widgetmaintest.h"

WidgetMainTest::WidgetMainTest(QWidget *parent) :
    QWidget(parent)
{
    lineLength = 200;
}

void WidgetMainTest::paintEvent(QPaintEvent *e)
{
    QPainterPath path = WidgetMainTest::drawSingleHexagon(NULL, QPointF(0, 0));
    QPainterPath path2 = WidgetMainTest::drawSingleHexagon(NULL, QPointF(300, 300));
    QPainter *painter = new QPainter(this);
    painter->setBrush(QBrush(QPixmap(":images/SkinDefault/iconTest.jpg")));
    painter->drawPath(path);
    painter->drawPath(path2);
    //painter->drawEllipse(0, 0, 200, 100);
    //drawSingleHexagon(painter, QPointF(50, 50));
}


QPainterPath WidgetMainTest::drawSingleHexagon(QPainter* painter, QPointF begin)
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


    /*
    painter->drawLine(p1, p2);
    painter->drawLine(p2, p3);
    painter->drawLine(p3, p4);
    painter->drawLine(p4, p5);
    painter->drawLine(p5, p6);
    painter->drawLine(p6, p1);
    */
}
