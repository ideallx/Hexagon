#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QPainter>
#include "../Game/gamebackpic.h"
#include "../Game/gamemapelement.h"
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
    //void mouseDoubleClickEvent(QMouseEvent *);
    int getBlockEnviroment(QPoint);

    void listMoveSphere(QPoint, int);
    int getLineLength(){ return lineLength;}



private:
    void paintInitial(void);
    void paintFocus(void);
    QPainterPath drawSingleHexagon(QPointF begin);

    void drawHexagonSeries(QPainter* painter, QPoint block);
    void drawMovingLines(QPainter* painter);

    void variableInitial(void);

    void deleteAllQlist();
    void listAddAsSet(QList<QPoint>*, QPoint);
    bool listAddSeies(QList<QPoint>*, QPoint);

    QPointF getBeginPosWithCoo(QPoint);
    QPointF getCenterPosWithCoo(QPoint);
    QPoint getCooxWithPos(QPointF);

    QPoint goUpLeft(QPoint);
    QPoint goUpRight(QPoint);
    QPoint goUp(QPoint);
    QPoint goDownLeft(QPoint);
    QPoint goDownRight(QPoint);
    QPoint goDown(QPoint);

    bool isPointAvailable(QPoint);

    void showAllQlist(QList<QPushButton*>, QPoint);
    void hideAllQlist(QList<QPushButton*>);

    int lineLength;
    int printIndicator;
    int mouseIndicator;

    QLabel *debugInfo;
    QPoint curMoveBlock;
    QPoint curChosenBlock;
    QList<QPushButton*> menuList;
    QList<QPoint> showSphere;
    QList<QPoint> moveList;
    QList<gameMapElement*> map;

    int widthCount;
    int heightCount;
    int beginX;
    int beginY;
    QVector<char> mapElement;

    double halfSqrt3;

    gameBackInfo *gbp;

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
    
public slots:
    void changeBlock(QPoint);
    void beginMoving(void);
    
};

#endif // WIDGETMAIN_H
