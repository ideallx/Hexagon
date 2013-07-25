#ifndef GAMECOORDINATE_H
#define GAMECOORDINATE_H

#include <QtWidgets>
#include "mapelement.h"
#include "heroitem.h"
#include "backinfo.h"

class gameCoordinate
{
public:
    gameCoordinate(QPoint, gameBackInfo* gbi);

    QList<QPoint> getMovePoint() const { return showSphere; }
    QPoint getCurPoint() const { return curPoint; }
    heroItem* getCurHero() const { return curHero; }
    QGraphicsItemAnimation* getGia() const { return gia; }
    QTimeLine* getGiaTimer() const { return giaTimer; }
    QList<gameMapElement*> getMapList() const { return mapList; }


    void setCurPoint(QPoint p){ curPoint = p; }
    void setCurHero(heroItem* h) { curHero = h; }

    heroItem* heroAtNum(int i);
    gameMapElement* mapAtPos(QPoint);
    void addmapElement(gameMapElement* gme){ mapList.append(gme); }
    void addHero(heroItem* hi){ heroList.append(hi); }

    QPoint goUpLeft(QPoint);
    QPoint goUpRight(QPoint);
    QPoint goUp(QPoint);
    QPoint goDownLeft(QPoint);
    QPoint goDownRight(QPoint);
    QPoint goDown(QPoint);
    QPointF getBeginPosWithCoo(QPoint);
    QPointF getBeginPosOfHero(QPoint);
    QPointF getCenterPosWithCoo(QPoint);
    QPoint getCooxWithPos(QPointF);
    int getBlockNumber(QPoint);


    bool isPointAvailable(QPoint);
    bool isPointMovable(QPoint);

    bool listAddSeies(QPoint);
    QList<QPoint> listMoveSphere(QPoint, int);
    void restoreAllPen();
    void clearMoveSphere() { showSphere.clear();}


private:
    int beginX;
    int beginY;
    int lineLength;
    double halfSqrt3;
    int widthCount;
    int heightCount;
    QGraphicsItemAnimation *gia;
    QTimeLine *giaTimer;

    QVector<char> mapElement;
    QList<gameMapElement*> mapList;
    QList<heroItem*> heroList;

    QList<QPoint> showSphere;


    QPoint curPoint;
    heroItem* curHero;

};

#endif // GAMECOORDINATE_H
