#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QGraphicsScene>
#include "itemcollector.h"

class backScene : public QGraphicsScene
{
    Q_OBJECT
public:
    backScene(gameBackInfo*, gameCoordinate*, QList<heroFactory::ExternInfo> i, QGraphicsScene* l, QGraphicsScene* r, QObject *parent = 0);
    
private:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    gameBackInfo* gbi;
    gameCoordinate* gc;
    itemCollector *ic;

    QList<QPoint> sphereList;

    QPoint oldPoint;

    QGraphicsScene* left;
    QGraphicsScene* right;

signals:
    void changeStatusBar(QStringList);
    void mapElementMovedIn(QPoint);
    void mapElementClicked(QPoint);
    void heroMovedIn(QPoint);
    void heroClicked(QPoint);
    void localHeroClicked(QPointF);
    
public slots:
    void clearSphere();
    void showMoveSphere();
    void showAttackSphere();
    
};

#endif // BACKSCENE_H
