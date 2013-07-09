#ifndef TESTVIEW2_H
#define TESTVIEW2_H

#include <QtWidgets>
#include <QtCore/qstate.h>
#include <QtCore/qobject.h>
#include "../Game/heroitem.h"
#include "../Game/gamemenu.h"

class backview : public QGraphicsView
{
    Q_OBJECT
public:
    backview(QGraphicsScene *scene, int lineLength);

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
    QSize sizeHint() const {return QSize(scene->width(), scene->height());}
    void mousePressEvent(QMouseEvent);
    void setHeroPos(heroItem* item, QPointF pos){
        item->setPos(pos);
    }

private:
    gameMenu* menu;
    int lineLength;
    QGraphicsScene *scene;
    QList<heroItem*> items;
};

#endif // TESTVIEW2_H
