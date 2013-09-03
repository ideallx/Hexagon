#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsItem>
#include <QPainter>

class CardBack : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit CardBack(QRectF, QString);

private:
    QRectF boundingRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString path;

signals:
    
public slots:
    
};

#endif // CARDITEM_H
