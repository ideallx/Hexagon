#ifndef GAMECOORDINATE_H
#define GAMECOORDINATE_H

#include <QtWidgets>
#include "gamemapelement.h"
#include "heroitem.h"
#include "gamebackinfo.h"

class gameCoordinate
{
public:
    gameCoordinate(QPoint, gameBackInfo* gbi);

    QList<QPoint> getMoveSphere() { return showSphere; }
    void clearMoveSphere() { showSphere.clear(); }

    void restoreAllPen();

    QPointF getBeginPosWithCoo(QPoint);
    QPointF getBeginPosOfHero(QPoint);
    QPointF getCenterPosWithCoo(QPoint);
    QPoint getCooxWithPos(QPointF);
    void addmapElement(gameMapElement* gme){ mapList.append(gme); }
    void addHero(heroItem* hi){ heroList.append(hi); }

    QPoint getCurPoint() { return curPoint; }
    heroItem* getCurHero() { return curHero; }
    QGraphicsItemAnimation* getGia() { return gia; }
    QTimeLine* getGiaTimer() { return giaTimer; }
    QList<gameMapElement*> getMapList() { return mapList; }
    void setCurPoint(QPoint p){ curPoint = p; }
    void setCurHero(heroItem* h) { curHero = h; }

    heroItem* heroNum(int i);
    gameMapElement* at(QPoint pos);

    QPoint goUpLeft(QPoint);
    QPoint goUpRight(QPoint);
    QPoint goUp(QPoint);
    QPoint goDownLeft(QPoint);
    QPoint goDownRight(QPoint);
    QPoint goDown(QPoint);

    int getBlockNumber(QPoint);
    void listAddAsSet(QList<QPoint>*, QPoint);
    bool listAddSeies(QList<QPoint>*, QPoint);
    bool isPointAvailable(QPoint);
    bool isPointMovable(QPoint);
    void listMoveSphere(QPoint, int);

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
    QList<QPoint> moveList;

    QPoint curPoint;
    heroItem* curHero;
};

#endif // GAMECOORDINATE_H
