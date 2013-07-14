#ifndef CARDITEM_H
#define CARDITEM_H

#include <QtWidgets>

class cardItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit cardItem(QRectF);

private:
    QRectF boundingRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


signals:
    
public slots:
    
};

#endif // CARDITEM_H
