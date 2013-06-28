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

private:
    void paintInitial(void);
    QPainterPath drawSingleHexagon(QPointF begin);
    void drawHexagonSeries(QPainter* painter, QPoint block);
    void variableInitial(void);
    void deleteAllQlist();
    QPointF getBeginPosWithCoo(QPoint);
    QPoint getCooxWithPos(QPointF);
    QPoint goTopLeft(QPoint);
    QPoint goTopRight(QPoint);
    bool isPointAvailable(QPoint);

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
    QVector<int> mapElement;

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
