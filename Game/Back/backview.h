#ifndef GAME_BACK_BACKVIEW_H_
#define GAME_BACK_BACKVIEW_H_

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMatrix>
#include <QResizeEvent>

class BackView : public QGraphicsView {
    Q_OBJECT

 public:
    BackView(QGraphicsScene *scene, QWidget *parent = 0);
    explicit BackView(QWidget *parent = 0);

 protected:
    void resizeEvent(QResizeEvent *event);

 private:
    void initialSettrings();
    QMatrix matrix;
};

#endif  // GAME_BACK_BACKVIEW_H_
