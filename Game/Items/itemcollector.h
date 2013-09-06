#ifndef GAME_ITEMS_ITEMCOLLECTOR_H_
#define GAME_ITEMS_ITEMCOLLECTOR_H_

#include <QGraphicsScene>
#include <QList>
#include <QVector>
#include <QPoint>
#include <QPen>
#include <QPixmap>
#include "enums.h"

class HeroItem;
class GameBackInfo;
class GameCoordinate;
class HeroFactory;
class CardEngine;
class GameMapElement;
class HandCard;
class MapEngine;
class CampHealth;
struct externInfo;

enum rangeMode_t {
    ModeMove,
    ModeAttack,
    ModeSkill,
    ModeElse
};

class ItemCollector {
 public:
    ItemCollector(GameBackInfo*, GameCoordinate*);
    ~ItemCollector();

    void setMapElement(MapEngine *me);
    void setHeroFactory(HeroFactory* hf, QList<struct externInfo> info);
    void setCardEngine(CardEngine* ce);
    void setCampHealth();
    void addItemsToScene(QGraphicsScene* gs);
    void setPlaySeq(int i) { thePlayerSeq = i; }
    int playSeq() const { return thePlayerSeq; }
    QList<HandCard*> switchToBack(QList<HandCard*> in);
    QString rscPath();

    QList<QString> getHeroListAvaterPath(enum camp_t c);

    bool isPointAvailable(QPoint);
    bool isPointMovable(QPoint);

    GameMapElement* getMapElementByPoint(QPoint in) {
        return elements[getPointNumber(in)]; }
    int getPointNumber(QPoint) const;

    QList<GameMapElement*> getRedTeamCamp();
    QList<GameMapElement*> getBlueTeamCamp();
    QList<GameMapElement*> getAllElementTypeOf(enum gameEnvironment_t);
    void setElementDefaultPen(QPoint);
    void setElementRestorePen(QPoint point);
    void setElementSpecialPen(QPoint, QPen);
    static void setElementSpecialPen(GameMapElement*, QPen pen);
    void setElementBoldPen(QPoint, double width);
    void restoreAllPen();

    HeroItem* getHeroByPoint(QPoint);
    void addLocalHero(HeroItem* h) { localHeros.append(h);}
    bool isLocalHero(HeroItem* h) { return localHeros.contains(h); }
    HeroItem* getLocalHero() { return localHeros[0]; }

    QList<HeroItem*> getActSequence();
    QList<HandCard*> getCard(int n);
    QList<QGraphicsLineItem*> getLines() { return targetLines; }
    QList<QPoint> listRange(HeroItem* hero, enum rangeMode_t);

    QPixmap getPixmap();
    QPoint getCooxWithPos(QPointF);

    QPointF getBeginPosOfHero(QPoint in);
    QPointF getCenterPosWithCoo(QPoint in);

 private:
    void addHeroList(QList<struct externInfo> info);
    void addCardList();
    void addMapElementList();
    void addHeroSide();

    template <typename T>
    static void addListToScene(QList<T> l, QGraphicsScene* s) {
        for (int i = 0; i < l.size(); i++) {
            s->addItem(l[i]);
        }
    }

    bool listAddJudge(QList<QPoint>* set, QPoint point);
    QList<QPoint> recursionSeries(QList<QPoint>* set, QPoint point, int range);

    GameBackInfo* gbi;
    GameCoordinate* gc;
    MapEngine* me;
    HeroFactory* hf;
    CardEngine* ce;

    int thePlayerSeq;
    int hei;
    int wid;
    HeroItem* tempHero;
    enum rangeMode_t type;

    QVector<HeroItem*> localHeros;

    QList<HeroItem*> redTeamHeros;
    QList<HeroItem*> blueTeamHeros;
    QList<GameMapElement*> elements;
    QList<CampHealth*> campLifes;
    QList<QGraphicsLineItem*> targetLines;

    QList<HandCard*> unusedCards;
    QList<HandCard*> backCards;
    QList<HandCard*> usedCards;
};

#endif  // GAME_ITEMS_ITEMCOLLECTOR_H_
