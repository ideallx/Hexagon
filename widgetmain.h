#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QPainter>
#include "gamebackpic.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class WidgetMain : public QWidget
{
    Q_OBJECT

public:
    WidgetMain(QWidget *parent = 0);
    void drawSingleHexagon(QPainter* painter, QPointF begin);
    ~WidgetMain();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    //void mouseDoubleClickEvent(QMouseEvent *);

private:
    void paintInitial(void);
    void paintFocus(void);
    void drawHexagonSeries(QPainter* painter, QPoint block);
    void variableInitial(void);
    QPointF getBeginPosWithCoo(QPoint);
    QPoint getCooxWithPos(QPointF);
    QPoint goTopLeft(QPoint);
    QPoint goTopRight(QPoint);
    bool isPointAvailable(QPoint);

    int lineLength;
    int printIndicator;
    QLabel *debugInfo;
    QPoint curBlock;
    QList<QPushButton*> menuList;

    int widthCount;
    int heightCount;
    int beginX;
    int beginY;

    gameBackPic *gbp;

    enum printIndicator_t
    {
        BLANK_BACKGROUND,
        BLOCK_CHOSEN
    };


signals:
    void curBlockChanged(QPoint );
    
public slots:
    void changeBlock(QPoint );
    
};

#endif // WIDGETMAIN_H
