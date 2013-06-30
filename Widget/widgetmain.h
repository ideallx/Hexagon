#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QPainter>
#include "../Game/gamebackpic.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

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


    enum gameEnvironment_t
    {
        areaSpace,
        areaGrass   = '1',
        areaStone   = '2',
        areaShop    = '3',
        areaAlchemy = '4',
        areaSpring  = '5',
        areaCamp    = '6',
        areaSwamp   = '7',
        areaDesert  = '8',
        areaWater   = '9',


        areaFort    = 'J',
        areaRedHome = 'K',
        areaTree    = 'L',
        areaBlueHome= 'M',

        areaNouse = 'Z'
    };

private:
    void paintInitial(void);
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
    char getBlockEnviroment(QPoint);

    int lineLength;
    int printIndicator;
    QLabel *debugInfo;
    QPoint curMoveBlock;
    QPoint curChosenBlock;
    QList<QPushButton*> menuList;

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
    
public slots:
    void changeBlock(QPoint );
    
};

#endif // WIDGETMAIN_H
