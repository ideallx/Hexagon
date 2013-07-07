#ifndef TESTVIEW2_H
#define TESTVIEW2_H

#include <QtWidgets>
#include <QtCore/qstate.h>
#include <QtCore/qobject.h>
#include "../Game/heroitem.h"

class testView2 : public QGraphicsView
{
    Q_OBJECT
public:
    testView2(QGraphicsScene *scene, int lineLength);

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
    QSize sizeHint() const {return QSize(scene->width(), scene->height());}

private:
    int lineLength;
    QGraphicsScene *scene;
    QList<heroItem*> items;
};

#endif // TESTVIEW2_H
