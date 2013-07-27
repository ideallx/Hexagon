#ifndef CARDITEM_H
#define CARDITEM_H

#include <QtWidgets>

class cardBack : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit cardBack(QRectF, QString);

private:
    QRectF boundingRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString path;

signals:
    
public slots:
    
};

#endif // CARDITEM_H
