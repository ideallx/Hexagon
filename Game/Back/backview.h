#ifndef TESTVIEW2_H
#define TESTVIEW2_H

#include <QtWidgets>

class backview : public QGraphicsView
{
    Q_OBJECT
public:
    backview(QGraphicsScene *scene, QWidget *parent = 0);
    backview(QWidget *parent = 0);

protected:
    QSize sizeHint() const {return scene()->sceneRect().size().toSize();}

private:
    void initialSettrings();
};

#endif // TESTVIEW2_H
