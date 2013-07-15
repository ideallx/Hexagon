#ifndef HEROITEM_H
#define HEROITEM_H

#include <QtWidgets>

class heroItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    Q_PROPERTY(QPoint point READ getPoint WRITE setPoint)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    heroItem(int lineLength, QString);

    char getSexual() const { return sexual; }
    char getAttackSphere() const { return attackSphere; }
    char getMoveSphere() const { return moveSphere; }
    QString getPlayerName() const { return playerName; }
    QString getHeroName() const { return heroName; }
    QPoint getPoint() const { return point;}
    void setPoint(QPoint p) { point = p; }

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);

    enum sexual_t
    {
        sex_male,
        sex_female
    };

private:
    QString path;
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
