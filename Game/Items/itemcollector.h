#ifndef ITEMCOLLECTOR_H
#define ITEMCOLLECTOR_H

#include "heroengine.h"
#include "cardengine.h"
#include "mapelement.h"
#include "coordinate.h"
#include "backinfo.h"
#include "buttomui.h"

class itemCollector
{
public:
    itemCollector(gameBackInfo*, gameCoordinate*, QGraphicsScene* c);
    ~itemCollector();

    void setMapElement();
    void setHeroFactory(heroFactory* hf, QList<heroFactory::ExternInfo> info);
    void setCardEngine(cardEngine* ce);
    void setButtomUi();
    QString rscPath() { return gbi->getConfigDir(); }

    QList<QString> getHeroListAvaterPath(char);


    bool isPointHasHero(QPoint);
    bool isPointAvailable(QPoint);
    bool isPointMovable(QPoint);

    gameMapElement* getMapElementByPoint(QPoint in){ return elements[getPointNumber(in)]; }
    int getPointNumber(QPoint);


    void setElementDefaultPen(QPoint);
    void setElementRestorePen(QPoint point);
    void setElementSpecialPen(QPoint, QPen);
    void setElementSpecialPen(gameMapElement*, QPen pen);
    void setElementBoldPen(QPoint, double width);
    void restoreAllPen();

    heroItem* getHeroByPoint(QPoint);
    void addLocalHero(heroItem* h){ localHeros.append(h);}
    bool isLocalHero(heroItem* h) { return localHeros.contains(h); }
    heroItem* getLocalHero() { return localHeros[0]; }

    QList<handCard*> getCard(int n);

    QList<QPoint> listSphere(QPoint point, int sphere, char type);

private:
    void addHeroList(QList<heroFactory::ExternInfo> info);
    void addCardList();
    void addMapElementList();
    void addHeroSide();

    bool listAddJudge(QList<QPoint>* set, QPoint point);
    QList<QPoint> recursionSeries(QList<QPoint>* set, QPoint point, int sphere);

    int wid;
    int hei;

    char type;

    QVector<heroItem*> localHeros;

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
