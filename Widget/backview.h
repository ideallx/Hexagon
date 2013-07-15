#ifndef TESTVIEW2_H
#define TESTVIEW2_H

#include <QtWidgets>

class backview : public QGraphicsView
{
    Q_OBJECT
public:
    backview(QGraphicsScene *scene, int lineLength);
    QSize sizeHint() const {return QSize(scene()->width(), scene()->height());}

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
    void mousePressEvent(QMouseEvent);

private:
    int lineLength;
};

#endif // TESTVIEW2_H
