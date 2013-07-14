#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QGraphicsScene>

class backScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit backScene(QObject *parent = 0);
    
private:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    
public slots:
    
};

#endif // BACKSCENE_H
