#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QGraphicsScene>
#include "coordinate.h"
#include "backinfo.h"
#include "heroengine.h"

class backScene : public QGraphicsScene
{
    Q_OBJECT
public:
    backScene(gameBackInfo*, gameCoordinate*, QObject *parent = 0);
    
private:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    gameBackInfo* gbi;
    gameCoordinate* gc;

signals:
    
public slots:
    
};

#endif // BACKSCENE_H
