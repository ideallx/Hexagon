#ifndef HEROITEM_H
#define HEROITEM_H

#include <QtWidgets>

class heroItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    heroItem(const QColor &colork, int lineLength);

    char getSexual() const;
    char getMoveSphere() const;
    QString getPlayerName() const;
    QString getHeroName() const;
    QPoint getCurPos() {return point;}
    void setPoint(QPoint p) { point = p; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    QPainterPath shape() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

private:
    QPoint point;
    char sexual;
    char moveSphere;
    QString playerName;
    QString heroName;

    int lineLength;
    QColor color;

signals:
    void mouseClicked(QGraphicsSceneMouseEvent *event);
    void heroInvokeMenu(QPointF);
    void changeStatus(QString);
};

#endif // HEROITEM_H
