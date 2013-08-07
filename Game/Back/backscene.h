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
    QList<QString> getHeroListAvaterPath(char in);
    
private:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    gameBackInfo* gbi;
    gameCoordinate* gc;
    itemCollector *ic;

    QList<QPoint> sphereList;

    QPoint oldPoint;
    QSize oldViewSize;

signals:
    void changeStatusBar(QStringList);
    void mapElementMovedIn(QPoint);
    void mapElementClicked(QPoint);
    void heroMovedIn(QPoint);
    void heroClicked(heroItem*);
    void buildMenu(QPoint);
    void viewSizeChanged(QSize);
    void listSlideAvaters(QList<QString>, QList<QString>);
    
public slots:
    void clearSphere();
    void showMoveSphere();
    void showAttackSphere();
    
};

#endif // BACKSCENE_H
