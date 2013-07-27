#ifndef ITEMCOLLECTOR_H
#define ITEMCOLLECTOR_H

#include "heroengine.h"
#include "cardengine.h"
#include "mapelement.h"
#include "coordinate.h"
#include "backinfo.h"

class itemCollector
{
public:
    itemCollector(gameBackInfo* gbi, gameCoordinate* gc, QGraphicsScene* scene);
    void setMapElement();
    void setHeroFactory(heroFactory* hf, QList<heroFactory::ExternInfo> info);
    void setCardEngine(cardEngine* ce);

    bool isPointHasHero(QPoint);
    bool isPointAvailable(QPoint);
    bool isPointMovable(QPoint);

    int getBlockNumber(QPoint);

    void restoreAllPen();

    QList<QPoint> listSphere(QPoint point, int sphere, char type);

private:
    void addHeroList(QList<heroFactory::ExternInfo> info);
    void addCardList();
    void addMapElementList();

    bool listAddJudge(QList<QPoint>set, QPoint point);
    QList<QPoint> recursionSeries(QList<QPoint>set, QPoint point, int sphere);

    int wid;
    int hei;

    char type;

    gameMapElement *gme;
    heroFactory* hf;
    cardEngine* ce;

    gameBackInfo* gbi;
    gameCoordinate* gc;
    QGraphicsScene* scene;

    QList<heroItem*> redTeamHeros;
    QList<heroItem*> blueTeamHeros;
    QList<handCard*> unusedCards;
    QList<handCard*> usedCards;
    QList<gameMapElement*> elements;

};

#endif // ITEMCOLLECTOR_H
