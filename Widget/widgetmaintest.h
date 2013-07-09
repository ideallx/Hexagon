#ifndef WIDGETMAINTEST_H
#define WIDGETMAINTEST_H

#include <QWidget>
#include <QtWidgets>
#include "backview.h"
#include "../Game/gamemenu.h"

class WidgetMainTest : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetMainTest(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

private:
    QPainterPath drawSingleHexagon(QPainter* painter, QPointF begin);
    int lineLength;

    
signals:
    
public slots:
    
};

#endif // WIDGETMAINTEST_H
