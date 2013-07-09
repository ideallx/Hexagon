#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

// should be deleted

#include <QWidget>
#include <QPainter>
#include "../Game/gamebackinfo.h"
#include "../Game/gamemapelement.h"
#include "../commonvariable.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtCore>

class WidgetMain : public QWidget
{
    Q_OBJECT

public:
    WidgetMain(QWidget *parent = 0);
    ~WidgetMain();
    QSize getMaxSizeHint();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    QSize sizeHint() const { return QSize(1024, 1536);}
    int getLineLength(){ return lineLength;}

private:
    void paintInitial(void);
    void paintFocus(void);
    QPainterPath drawSingleHexagon(QPointF begin);

    void drawHexagonSeries(QPainter* painter, QPoint block);
    void drawMovingLines(QPainter* painter);

    void variableInitial(void);

    QLabel *debugInfo;
    QPoint curMoveBlock;
    QPoint curChosenBlock;

    int widthCount;
    int heightCount;
    int beginX;
    int beginY;
    int lineLength;
    double halfSqrt3;

    QVector<char> mapElement;

    gameBackInfo *gbi;

    enum printIndicator_t
    {
        BLANK_BACKGROUND,
        BLOCK_CHOSEN
    };

    enum mouseIndicator_t
    {
        MOUSE_NORMAL,
        MOUSE_MOVING
    };


signals:
    void curMoveBlockChanged(QPoint );
    void parentStatusChanged(QString);
    void mousePressed();
    
public slots:
    void changeBlock(QPoint);
    void beginMoving(void);
    
};

#endif // WIDGETMAIN_H
