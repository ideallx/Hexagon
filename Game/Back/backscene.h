#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QtWidgets>
#include "itemcollector.h"

class backScene : public QGraphicsScene
{
    Q_OBJECT
public:
    backScene(gameBackInfo*, gameCoordinate*, QList<heroFactory::ExternInfo> i, QObject *parent = 0);
    ~backScene();
    
private:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) { qDebug("sdfsf"); }

private:
    gameBackInfo* gbi;
    gameCoordinate* gc;
    itemCollector *ic;

    QList<QPoint> sphereList;

    QPoint oldPoint;
    QSize oldViewSize;

signals:
    void changeStatusBar(QStringList);
    void mapElementMovedIn(QPoint);
    void mapElementClicked(QPoint);
    void heroMovedIn(QPoint);
    void heroClicked(QPoint);
    void localHeroClicked(QPointF);
    void viewSizeChanged(QSize);
    
public slots:
    void clearSphere();
    void showMoveSphere();
    void showAttackSphere();
    
};

#endif // BACKSCENE_H
