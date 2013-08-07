#ifndef TESTVIEW2_H
#define TESTVIEW2_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMatrix>
#include <QResizeEvent>

class backview : public QGraphicsView
{
    Q_OBJECT
public:
    backview(QGraphicsScene *scene, QWidget *parent = 0);
    backview(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);
    //QSize sizeHint() const {return scene()->sceneRect().size().toSize();}

private:
    void initialSettrings();
    QMatrix matrix;
};

#endif // TESTVIEW2_H
