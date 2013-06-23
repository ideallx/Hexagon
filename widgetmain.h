#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QPainter>
#include "gamebackpic.h"
#include <QLabel>

class WidgetMain : public QWidget
{
    Q_OBJECT

public:
    WidgetMain(QWidget *parent = 0);
    void drawSingleShape(QPainter* painter, QPointF begin);
    ~WidgetMain();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void repaint();

private:
    void paintInitial(void);
    void paintFocus(void);

    static const int lineLength = 100;
    int printIndicator;
    QLabel *debugInfo;
    QPoint curBlock;

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
