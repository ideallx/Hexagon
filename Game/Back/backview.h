#ifndef TESTVIEW2_H
#define TESTVIEW2_H

#include <QtWidgets>

class backview : public QGraphicsView
{
    Q_OBJECT
public:
    backview(QGraphicsScene *scene, QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
    QSize sizeHint() const {return QSize(scene()->width(), scene()->height());}

private:
    backview(QWidget *parent = 0);
    void initialSettrings();
};

#endif // TESTVIEW2_H
