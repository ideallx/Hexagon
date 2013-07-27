#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QGraphicsScene>
#include "itemcollector.h"

class backScene : public QGraphicsScene
{
    Q_OBJECT
public:
    backScene(gameBackInfo*, gameCoordinate*, QList<heroFactory::ExternInfo> i, QObject *parent = 0);
    
private:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    gameBackInfo* gbi;
    gameCoordinate* gc;
    itemCollector *ic;

signals:
    void mapElementMovedIn(QPoint);
    
public slots:
    
};

#endif // BACKSCENE_H
