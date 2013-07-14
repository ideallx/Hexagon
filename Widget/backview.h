#ifndef TESTVIEW2_H
#define TESTVIEW2_H

#include <QtWidgets>
#include <QtCore/qstate.h>
#include <QtCore/qobject.h>
#include "../Game/heroitem.h"
#include "../Game/gamemenu.h"
#include "../Game/gamebackinfo.h"
#include "../Game/gamemapelement.h"

class backview : public QGraphicsView
{
    Q_OBJECT
public:
    backview(QGraphicsScene *scene, int lineLength, gameBackInfo*);
    QSize sizeHint() const {return QSize(scene->width(), scene->height());}

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
    void mousePressEvent(QMouseEvent);

private:
    int lineLength;
    QGraphicsScene *scene;
    QList<heroItem*> items;
};

#endif // TESTVIEW2_H
