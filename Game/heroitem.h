#ifndef HEROITEM_H
#define HEROITEM_H

#include <QtWidgets>
#include "abstracthero.h"
#include "../Game/gamemenu.h"
#include "../commonvariable.h"


class heroItem : public abstractHero, public QObject, public QGraphicsEllipseItem
{

public:
    heroItem(const QColor &colork, int lineLength);

    char getSexual() const;
    char getMoveSphere() const;
    QString getPlayerName() const;
    QString getHeroName() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    QPainterPath shape() const;

    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent *);

private:
    char sexual;
    char moveSphere;
    QString playerName;
    QString heroName;

    int lineLength;
    QColor color;

signals:
    void heroInvokeMenu(QPointF);
};

#endif // HEROITEM_H
