#ifndef GAME_ITEMS_CARD_CARDBACK_H_
#define GAME_ITEMS_CARD_CARDBACK_H_

#include <QGraphicsItem>
#include <QPainter>

class CardBack : public QObject, public QGraphicsRectItem {
    Q_OBJECT

 public:
    explicit CardBack(QRectF, QString);

 private:
    QRectF boundingRect();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QString path;
};

#endif  // GAME_ITEMS_CARD_CARDBACK_H_
