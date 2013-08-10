#ifndef CAMPHEALTH_H
#define CAMPHEALTH_H

#include <QGraphicsRectItem>
#include <QPainter>

class campHealth : public QObject, public QGraphicsPixmapItem //pixmap later
{
    Q_OBJECT
public:
    explicit campHealth(const QPixmap &pixmap, QGraphicsItem *parent = 0);

private:
    QRectF boundingRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    
public slots:
    
};

#endif // CAMPHEALTH_H
