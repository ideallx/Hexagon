#ifndef ITEMCOLLECTOR_H
#define ITEMCOLLECTOR_H


#include <QgraphicsScene>
#include <QList>
#include <QVector>
#include <QPoint>
#include <QPen>


class heroItem;
class gameBackInfo;
class gameCoordinate;
class heroFactory;
class cardEngine;
class gameMapElement;
class handCard;
class mapEngine;
class campHealth;


struct externInfo;


class itemCollector
{
public:
    itemCollector(gameBackInfo*, gameCoordinate*, QGraphicsScene* c);
    ~itemCollector();

    void setMapElement(mapEngine *me);
    void setHeroFactory(heroFactory* hf, QList<struct externInfo> info);
    void setCardEngine(cardEngine* ce);
    void setCampHealth();
    QString rscPath();

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
    QList<heroItem*> getActSequence();

    QList<handCard*> getCard(int n);

    QList<QPoint> listSphere(QPoint point, int sphere, char type);

private:
    void addHeroList(QList<struct externInfo> info);
    void addCardList();
    void addMapElementList();
    void addHeroSide();


    bool listAddJudge(QList<QPoint>* set, QPoint point);
    QList<QPoint> recursionSeries(QList<QPoint>* set, QPoint point, int sphere);

    char type;

    int hei;
    int wid;

    QVector<heroItem*> localHeros;

    mapEngine* me;
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
    QList<campHealth*> campLifes;

};

#endif // ITEMCOLLECTOR_H
