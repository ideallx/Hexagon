#ifndef SIDESCENE_H
#define SIDESCENE_H

#include <QtWidgets>

class sideScene : public QGraphicsScene
{
    Q_OBJECT
public:
    sideScene(QObject *parent = 0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    
signals:
    
public slots:
    
};

#endif // SIDESCENE_H
