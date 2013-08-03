#ifndef BUTTONUI_H
#define BUTTONUI_H

#include <QGraphicsPixmapItem>
#include <QtWidgets>

class buttomUi : public QGraphicsPixmapItem
{
public:
    explicit buttomUi(QString path);

private:
    QRectF boundingRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    
public slots:
    
};

#endif // BUTTONUI_H
