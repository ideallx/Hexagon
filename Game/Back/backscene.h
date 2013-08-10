#ifndef BACKSCENE_H
#define BACKSCENE_H

#include <QGraphicsScene>

class itemCollector;
class gameBackInfo;
class gameCoordinate;
class heroItem;
class heroFactory;
struct externInfo;

class backScene : public QGraphicsScene
{
    Q_OBJECT
public:
    backScene(gameBackInfo*, gameCoordinate*, QList<struct externInfo> i, QObject *parent = 0);
    ~backScene();

    itemCollector* pIc() { return ic;}
    gameCoordinate* pGc() { return gc; }
    QList<QString> getHeroListAvaterPath(char in);

    
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    gameBackInfo* gbi;
    gameCoordinate* gc;
    itemCollector *ic;

    QList<QPoint> sphereList;

    QPoint oldPoint;

    QPointF oldPointF;
    QSize oldViewSize;
    bool isPressing;

signals:
    void changeStatusBar(QStringList);
    void mapElementMovedIn(QPoint);
    void mapElementClicked(QPoint);
    void heroClicked(heroItem*);
    void buildMenu(heroItem*, QPoint);
    void viewSizeChanged(QSize);
    void listSlideAvaters(QList<QString>, QList<QString>);
    void sphereClicked(QPoint);
    
public slots:
    void clearSphere();
    void showMoveSphere(heroItem*);
    void showAttackSphere(heroItem* hero);
    
};

#endif // BACKSCENE_H
