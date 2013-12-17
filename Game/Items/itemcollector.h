#ifndef GAME_ITEMS_ITEMCOLLECTOR_H_
#define GAME_ITEMS_ITEMCOLLECTOR_H_

#include <QGraphicsScene>
#include <QList>
#include <QVector>
#include <QPoint>
#include <QPen>
#include <QPixmap>
#include <QQueue>
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
class EquipmentShop;
class Equipment;
struct externInfo;

enum class RangeMode {
    ModeMove,
    ModeAttack,
    ModeSkill,
    ModeElse
};

class ItemCollector {
 public:
    typedef bool (ItemCollector::*filter)(QPoint);

    ItemCollector(GameBackInfo*, GameCoordinate*);
    ~ItemCollector();

    void setMapElement(MapEngine *me);
    void setHeroFactory(HeroFactory* hf, QList<ExternInfo> info);
    void setCardEngine(CardEngine* ce);
    void setEquipmentShop(EquipmentShop* es);
    void setCampHealth();
    void addItemsToScene(QGraphicsScene* gs);
    void setPlaySeq(int i) { thePlayerSeq = i; }
    int playSeq() const { return thePlayerSeq; }
    QList<HandCard*> switchToBack(QList<HandCard*> in);
    QString rscPath();

    QList<QString> getHeroListAvaterPath(Camp c);

    bool isPointAvailable(QPoint);
    bool isPointMovable(QPoint);

    GameMapElement* getMapElementByPoint(QPoint in) {
        return elements[getPointNumber(in)]; }
    int getPointNumber(QPoint) const;

    QList<GameMapElement*> getRedTeamCamp();
    QList<GameMapElement*> getBlueTeamCamp();
    QList<GameMapElement*> getAllElementTypeOf(AreaHexagon);
    void setElementDefaultPen(QPoint);
    void setElementRestorePen(QPoint point);
    void setElementSpecialPen(QPoint, QPen);
    static void setElementSpecialPen(GameMapElement*, QPen pen);
    void setElementBoldPen(QPoint, double width);
    void restoreAllPen();

    HeroItem* getHeroByPoint(QPoint);
    inline void addLocalHero(HeroItem* h) { localHeros.append(h);}
    inline bool isLocalHero(HeroItem* h) { return localHeros.contains(h); }
    inline HeroItem* getLocalHero() { return localHeros[0]; }

    QList<HeroItem*> getActSequence();
    QList<HandCard*> getCard(int n);
    void returnCard(QList<HandCard*> l);
    inline QList<QGraphicsLineItem*> getLines() { return targetLines; }
    inline QList<QPoint> listRange(HeroItem* hero, RangeMode);
    inline QList<QPoint> listSpecialRange(QPoint o, MapRangeType t, int range);
    QList<QPoint> listAllMap();
    inline QList<HandCard*> getJunkCards() { return usedCards; }

    QPixmap getPixmap();
    QPoint getCooxWithPos(QPointF);

    QPointF getBeginPosOfHero(QPoint in);
    QPointF getCenterPosWithCoo(QPoint in);

    static QPoint outPoint() { return QPoint(-1, -1); }

    bool normalFilter(QPoint point);

    template <typename T>
    static void shuffle(QList<T> &l) {
        for (int i = 0; i < l.size(); i++) {
            l.swap(i, rand()%l.size());
        }
    }


    enum class PointState {
        NotChecked,
        Added,
        Checked
    };

    class RecursivePoint_t {
     public:
        QPoint parent;
        QPoint self;
        PointState state;
    };
    QList<QPoint> pathOnSearch (QPoint from, QPoint to);
    bool addPointToQueue(QPoint p, QPoint from, filter f);
    RecursivePoint_t* getStruct(QPoint in);

    void calcWholeMapDistance(QPoint from);
    QList<QPoint> pathAfterSearch (QPoint to);
    void clearPoints();

 private:
    void addHeroList(QList<ExternInfo> info);
    void addCardList();
    void addMapElementList();
    void addHeroSide();
    void addEquipment();

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
    EquipmentShop* es;

    int thePlayerSeq;
    int hei;
    int wid;
    HeroItem* tempHero;
    RangeMode type;

    QVector<HeroItem*> localHeros;

    QList<HeroItem*> redTeamHeros;
    QList<HeroItem*> blueTeamHeros;
    QList<GameMapElement*> elements;
    QList<CampHealth*> campLifes;
    QList<QGraphicsLineItem*> targetLines;

    QList<HandCard*> unusedCards;
    QList<HandCard*> backCards;
    QList<HandCard*> usedCards;

    QList<QList<Equipment*> > equips;

    QQueue<RecursivePoint_t*> queue;
    QList<QList<RecursivePoint_t*> > points;
};

#endif  // GAME_ITEMS_ITEMCOLLECTOR_H_
