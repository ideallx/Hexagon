#ifndef HEROWHOLE_H
#define HEROWHOLE_H

#include <QGraphicsRectItem>
#include <QtWidgets>

class heroWhole : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit heroWhole(int lineLength, QObject *parent = 0);
    
signals:

private:
    QRectF heroWhole::boundingRect() const;
    void heroWhole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    int lineLength;
    
public slots:
    
};

#endif // HEROWHOLE_H
