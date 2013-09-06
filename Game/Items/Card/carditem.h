#ifndef GAME_ITEMS_CARD_CARDITEM_H_
#define GAME_ITEMS_CARD_CARDITEM_H_

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class HandCard : public QGraphicsRectItem {
 public:
    HandCard(int t, QString pixmapPath);
    QPixmap pixmap() { return pixmapPath; }
    void setPixmap(QString s) { pixmapPath = s; }

    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

 private:
    int type;
    QPixmap pixmapPath;
};
#endif  // GAME_ITEMS_CARD_CARDITEM_H_
