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



private:
    void paintInitial(void);
    void paintFocus(void);
    QPainterPath drawSingleHexagon(QPointF begin);
    void drawHexagonSeries(QPainter* painter, QPoint block);

    void variableInitial(void);
    void deleteAllQlist();
    QPointF getBeginPosWithCoo(QPoint);
    QPoint getCooxWithPos(QPointF);
    QPoint goUpLeft(QPoint);
    QPoint goUpRight(QPoint);
    QPoint goDownLeft(QPoint);
    QPoint goDownRight(QPoint);
    bool isPointAvailable(QPoint);

    int lineLength;
    int printIndicator;
    QLabel *debugInfo;
    QPoint curMoveBlock;
    QPoint curChosenBlock;
    QList<QPushButton*> menuList;

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


signals:
    void curMoveBlockChanged(QPoint );
    void parentStatusChanged(QString);
    
public slots:
    void changeBlock(QPoint );
    
};

#endif // WIDGETMAIN_H
