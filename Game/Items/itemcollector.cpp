#include <QStack>
#include "itemcollector.h"
#include "heroitem.h"
#include "heroengine.h"
#include "cardengine.h"
#include "mapelement.h"
#include "coordinate.h"
#include "backinfo.h"
#include "camphealth.h"
#include "carditem.h"
#include "equipment.h"

ItemCollector::ItemCollector(GameBackInfo* gbii, GameCoordinate* gci)
      : gbi(gbii),
        gc(gci),
        me(NULL),
        hf(NULL),
        ce(NULL),
        thePlayerSeq(0),
        hei(gbi->getHeightCount()),
        wid(gbi->getWidthCount()),
        tempHero(NULL),
        type(ModeMove) {
}

ItemCollector::~ItemCollector() {
    qDeleteAll(redTeamHeros);
    qDeleteAll(blueTeamHeros);
    qDeleteAll(unusedCards);
    qDeleteAll(usedCards);
    qDeleteAll(elements);

    redTeamHeros.clear();
    blueTeamHeros.clear();
    unusedCards.clear();
    usedCards.clear();
    elements.clear();
}

void ItemCollector::setMapElement(MapEngine *me) {
    this->me = me;
    addMapElementList();
}

void ItemCollector::setHeroFactory(HeroFactory* hf,
                                   QList<struct ExternInfo> info) {
    this->hf = hf;
    addHeroList(info);
}

void ItemCollector::setCardEngine(CardEngine* ce) {
    this->ce = ce;
    addCardList();
    shuffle(unusedCards);
}

void ItemCollector::setEquipmentShop(EquipmentShop *es) {
    this->es = es;
    addEquipment();
}

void ItemCollector::setCampHealth() {
    CampHealth* ch = new CampHealth(gbi->getConfigDir()+"health2.png");
    campLifes.append(ch);
    ch->setPos(200, 50);

    ch = new CampHealth(gbi->getConfigDir()+"health1.png");
    campLifes.append(ch);
    ch->setPos(200, gbi->getPixmap().height()-200);
}

void ItemCollector::addHeroList(QList<struct ExternInfo> info) {
    QList<HeroItem*> heros = hf->generateHeroes(info);
    for (int i = 0; i < heros.size(); i++) {
        heros.at(i)->setPos(gc->getBeginPosOfHero(heros.at(i)->point()));
        if (heros.at(i)->camp() == camp_red) {
            redTeamHeros.append(heros.at(i));
        }  else {
            blueTeamHeros.append(heros.at(i));
        }
    }

    for (int i = 0; i < heros.size(); i++) {
        QGraphicsLineItem *targetLine = new QGraphicsLineItem();
        targetLine->setPos(0, 0);
        targetLine->hide();
        targetLine->setPen(QPen(Qt::yellow, 5));
        targetLine->setZValue(2);
        targetLines.append(targetLine);
    }
    addLocalHero(heros.at(0));
}

void ItemCollector::addCardList() {
    unusedCards = ce->generateHandCards();
}

void ItemCollector::addMapElementList() {
    elements = me->generateMapElements(wid, hei);
    for (int j = 0; j < hei; j++) {
        for (int i = 0; i < wid; i++) {
            elements[j*wid+i]->setPos(gc->getBeginPosWithCoo(QPoint(i, j)));
        }
    }

    for (int i = 0; i < wid; i++) {
        QList<RecursivePoint_t*> list;
        for (int j = 0; j < hei; j++) {
            RecursivePoint_t* point = new RecursivePoint_t();
            point->parent = outPoint();
            point->self = QPoint(i, j);
            point->state = NotChecked;
            list.append(point);
        }
        points.append(list);
    }
}

void ItemCollector::addEquipment() {
    equips = es->generateEquipment();
    qDebug() << "Equipment:" << equips[0][0]->name();
}

bool ItemCollector::isPointAvailable(QPoint in) {
    if (in.x() < 0 || in.y() < 0 || in.x() >= wid || in.y() >= hei)
        return false;
    else if ((in.x() == wid-1) && (in.y()%2 == 1) && (wid%2 == 0))
        return false;
    else if (!elements[getPointNumber(in)]->isPointAvailable())
        return false;
    else
        return true;
}

bool ItemCollector::isPointMovable(QPoint in) {
    return elements[getPointNumber(in)]->isMoveAvailable();
}

void ItemCollector::restoreAllPen() {
    for (int i = 0; i < elements.size(); ++i) {
        elements[i]->getDefaultPen();
    }
}


int ItemCollector::getPointNumber(QPoint point) const {
    return point.x()+point.y()*wid;
}

HeroItem* ItemCollector::getHeroByPoint(QPoint point) {
    for (int i = 0; i < redTeamHeros.size(); i++) {
        if (point == redTeamHeros.at(i)->point()) {
            return redTeamHeros.at(i);
        }
    }
    for (int i = 0; i < blueTeamHeros.size(); i++) {
        if (point == blueTeamHeros.at(i)->point()) {
            return blueTeamHeros.at(i);
        }
    }
    return NULL;
}

bool ItemCollector::listAddJudge(QList<QPoint>* set, QPoint point) {
    if (type == ModeMove) {
        if (isPointAvailable(point) && isPointMovable(point)) {
            if (getHeroByPoint(point))
                return false;
            if (!set->contains(point))
                set->append(point);
            return true;
        }
    } else if (type == ModeAttack) {
        HeroItem* hi = getHeroByPoint(point);
        if (isPointAvailable(point) && hi) {
            if (hi->camp() == tempHero->camp())
                return false;
            if (!set->contains(point))
                set->append(point);
            return true;
        }
    }
    return false;
}

QList<QPoint> ItemCollector::recursionSeries(QList<QPoint>*set,
                                             QPoint point,
                                             int range) {
    if (range == 0)
        return *set;
    range--;
    QPoint pair;

    pair = gc->goUpLeft(point);
    if (listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goUpRight(point);
    if (listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goUp(point);
    if (listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goDownLeft(point);
    if (listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goDownRight(point);
    if (listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goDown(point);
    if (listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    return *set;
}

QList<QPoint> ItemCollector::listRange(HeroItem* hero, enum rangeMode_t t) {
    type = t;
    tempHero = hero;
    QList<QPoint> set;

    if (type == ModeMove)
        return recursionSeries(&set, hero->point(), hero->moveRange());
    else if (type == ModeAttack)
        return recursionSeries(&set, hero->point(), hero->attackRange());
    return set;
}

QList<QPoint> ItemCollector::listSpecialRange(QPoint o,
                                              enum MapRangeType_t t,
                                              int range) {
    QList<QPoint> set;
    if (t == RangeTypeRound) {
        return recursionSeries(&set, o, range);
    } else {   // TODO(ideallx)
        return set;
    }
}

QList<QPoint> ItemCollector::listAllMap() {  // TODO(ideallx) func point
    QList<QPoint> result;
    foreach(GameMapElement* gme, elements) {
        QPoint point = gme->point();
        if (!isPointMovable(point) ||
                !isPointAvailable(point) ||
                !getHeroByPoint(point)) {
            continue;
        }
        result.append(point);
    }
    return result;
}

/*
 *   0.8 not moveable
 *   0.7 current moved In bold
 *   0.65 in range
 *   0.6 moveable
 */

void ItemCollector::setElementDefaultPen(QPoint point) {
    if (!isPointAvailable(point))
        return;
    GameMapElement* gmeT = elements[getPointNumber(point)];
    gmeT->setDefaultZValue();
    gmeT->setDefaultPen();
}

void ItemCollector::setElementRestorePen(QPoint point) {
    if (!isPointAvailable(point))
        return;
    GameMapElement* gmeT = elements[getPointNumber(point)];
    gmeT->setZValue(0.65);
    gmeT->restorePen();
}

void ItemCollector::setElementSpecialPen(QPoint point, QPen pen) {
    if (!isPointAvailable(point))
        return;
    GameMapElement* gmeT = elements[getPointNumber(point)];
    gmeT->setZValue(0.65);
    setElementSpecialPen(gmeT, pen);
}

void ItemCollector::setElementBoldPen(QPoint point, double width) {
    if (!isPointAvailable(point))
        return;
    GameMapElement* gmeT = elements[getPointNumber(point)];
    gmeT->setZValue(0.7);
    gmeT->setPen(QPen(gmeT->getDefaultPen().color(), width));
}

void ItemCollector::setElementSpecialPen(GameMapElement* gmeT, QPen pen) {
    gmeT->setZValue(0.65);
    gmeT->setPen(pen);
}
/**
 * TODO(ideallx) change ui
 *
 */
QList<QString> ItemCollector::getHeroListAvaterPath(enum Camp_t in) {
    QList<QString> result;
    QList<HeroItem*> recv;

    if (in == camp_red) {
        recv = redTeamHeros;
    } else if (in == camp_blue) {
        recv = blueTeamHeros;
    } else {
        return result;
    }

    for (int i = 0; i < recv.size(); i++) {
        QString temp = gbi->getConfigDir() +
                "/heros/" + recv[i]->heroName() + "_Head.jpg";
        result.append(temp);
    }
    return result;
}

QList<HandCard*> ItemCollector::getCard(int n) {
    QList<HandCard*> result;
    if (unusedCards.size() < n)
        n = unusedCards.size();
    for (int i = 0; i < n; i++) {
        result.append(unusedCards[0]);
        unusedCards.removeAt(0);
    }
    return result;
}

void ItemCollector::returnCard(QList<HandCard*> l) {
    usedCards.append(l);
}

QString ItemCollector::rscPath() {
    return gbi->getConfigDir();
}

QList<HeroItem*> ItemCollector::getActSequence() {
    QList<HeroItem*> result;

    for (int i = 0; i < redTeamHeros.size(); i++) {
        result.append(blueTeamHeros[i]);
        result.append(redTeamHeros[i]);
    }
    return result;
}

QList<GameMapElement*> ItemCollector::getRedTeamCamp() {
    return getAllElementTypeOf(AreaRedHome);
}

QList<GameMapElement*> ItemCollector::getBlueTeamCamp() {
    return getAllElementTypeOf(AreaBlueHome);
}

QList<GameMapElement*> ItemCollector::getAllElementTypeOf(
        enum GameEnvironment_t type) {
    QList<GameMapElement*> result;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->getType() == type) {
            result.append(elements[i]);
        }
    }
    qDebug() << "result size:" << result.size();
    return result;
}


QPixmap ItemCollector::getPixmap() {
    return gbi->getPixmap();
}

QPoint ItemCollector::getCooxWithPos(QPointF qf) {
    return gc->getCooxWithPos(qf);
}

QPointF ItemCollector::getBeginPosOfHero(QPoint in) {
    return gc->getBeginPosOfHero(in);
}

QPointF ItemCollector::getCenterPosWithCoo(QPoint in) {
    return gc->getCenterPosWithCoo(in);
}

void ItemCollector::addItemsToScene(QGraphicsScene* s) {
    addListToScene(redTeamHeros, s);
    addListToScene(blueTeamHeros, s);
    addListToScene(elements, s);
    addListToScene(campLifes, s);
    addListToScene(targetLines, s);
}

QList<HandCard*> ItemCollector::switchToBack(QList<HandCard*> in) {
    int num = qMin(backCards.size(), in.size());
    QList<HandCard*> result;
    for (int i = 0; i < num; i++) {
        result.append(backCards[i]);
    }
    return result;
}

/**
 * @brief calc the path once it's called. Use breadth-first research
 * @param from
 * @param to
 * @return
 */
QList<QPoint> ItemCollector::pathOnSearch (QPoint from, QPoint to) {
    queue.clear();
    QQueue<RecursivePoint_t*> waitForChecks;
    QList<QPoint> result;
    filter f = &ItemCollector::normalFilter;
    if (!isPointAvailable(to))
        return result;

    clearPoints();
    if (!addPointToQueue(from, outPoint(), NULL))
        return result;
    queue.swap(waitForChecks);

    RecursivePoint_t *ss;
    while (!waitForChecks.isEmpty()) {
        while (!waitForChecks.isEmpty()) {
            ss = waitForChecks.dequeue();
            ss->state = Checked;
            from = ss->self;
            if (gc->roughDistance(from, to) == 1) {
                ss = getStruct(to);
                ss->parent = from;
                ss->state = Checked;
                return pathAfterSearch(to);
            }
            addPointToQueue(gc->goUp(from), from, f);
            addPointToQueue(gc->goUpLeft(from), from, f);
            addPointToQueue(gc->goUpRight(from), from, f);
            addPointToQueue(gc->goDown(from), from, f);
            addPointToQueue(gc->goDownLeft(from), from, f);
            addPointToQueue(gc->goDownRight(from), from, f);
        }
        queue.swap(waitForChecks);
    }
    return result;
}

bool ItemCollector::addPointToQueue(QPoint p, QPoint from, filter f) {
    if (isPointAvailable(p) && ((f == NULL) || (this->*f)(p))) {
        RecursivePoint_t *ss = getStruct(p);
        if (ss->state == NotChecked) {
            queue.append(ss);
            ss->parent = from;
            ss->state = Added;
            // qDebug() << "point added" << p;
            return true;
        }
        // qDebug() << "point already checked" <<p;
    }
    // qDebug() << "point unavailable" << p;
    return false;
}

void ItemCollector::clearPoints() {
    foreach(QList<RecursivePoint_t*> list, points) {
        foreach(RecursivePoint_t *point, list) {
            point->parent = outPoint();
            point->state = NotChecked;
        }
    }
}

ItemCollector::RecursivePoint_t* ItemCollector::getStruct(QPoint in) {
    return points[in.x()][in.y()];
}

bool ItemCollector::normalFilter(QPoint point) {
    return isPointMovable(point) && (!getHeroByPoint(point));
}

void ItemCollector::calcWholeMapDistance(QPoint from) {
    queue.clear();
    QQueue<RecursivePoint_t*> waitForChecks;
    filter f = &ItemCollector::normalFilter;

    clearPoints();
    if (!addPointToQueue(from, outPoint(), NULL))
        return;
    queue.swap(waitForChecks);

    RecursivePoint_t *ss;
    while (!waitForChecks.isEmpty()) {
        while (!waitForChecks.isEmpty()) {
            ss = waitForChecks.dequeue();
            from = ss->self;
            ss->state = Checked;
            addPointToQueue(gc->goUp(from), from, f);
            addPointToQueue(gc->goUpLeft(from), from, f);
            addPointToQueue(gc->goUpRight(from), from, f);
            addPointToQueue(gc->goDown(from), from, f);
            addPointToQueue(gc->goDownLeft(from), from, f);
            addPointToQueue(gc->goDownRight(from), from, f);
        }
        queue.swap(waitForChecks);
    }
}

QList<QPoint> ItemCollector::pathAfterSearch (QPoint to) {
    QList<QPoint> result;
    QStack<QPoint> stacks;
    RecursivePoint_t *ss;
    ss = getStruct(to);
    do {
        stacks.push(ss->self);
        ss = getStruct(ss->parent);
    } while (ss->parent != outPoint());

    while (!stacks.isEmpty()) {
        QPoint p = stacks.pop();
        qDebug() << p;
        result.append(p);
    }
    return result;
}
