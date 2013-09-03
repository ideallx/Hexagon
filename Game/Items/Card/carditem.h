#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class HandCard : public QGraphicsRectItem
{
public:
    HandCard(int t, QString pixmapPath);
    QPixmap pixmap() { return pixmapPath; }
    void setPixmap(QString s) { pixmapPath = s; }

    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

private:
    QPixmap pixmapPath;
    int type;
};
#endif // CARDITEM_H
