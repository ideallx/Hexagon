#ifndef HEROITEM_H
#define HEROITEM_H

#include <QtWidgets>

class heroItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    Q_PROPERTY(QPoint point READ getPoint WRITE setPoint)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    heroItem(const QColor &colork, int lineLength);

    char getSexual() const;
    char getAttackSphere() const { return attackSphere; }
    char getMoveSphere() const;
    QString getPlayerName() const;
    QString getHeroName() const;
    QPoint getPoint() {return point;}
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
    char attackSphere;
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
