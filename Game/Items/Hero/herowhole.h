#ifndef HEROWHOLE_H
#define HEROWHOLE_H

#include <QGraphicsRectItem>
#include <QtWidgets>

class HeroWhole : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    HeroWhole(int lineLength, QObject *parent = 0);
    
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

class heroThumbnail : public QObject, public QGraphicsRectItem
{
public:
    heroThumbnail(int lineLength, QObject *parent = 0);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // HEROWHOLE_H
