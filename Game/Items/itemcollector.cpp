#include "itemcollector.h"
#include "heroitem.h"
#include "heroengine.h"
#include "cardengine.h"
#include "mapelement.h"
#include "coordinate.h"
#include "backinfo.h"
#include "camphealth.h"

itemCollector::itemCollector(gameBackInfo* gbii, gameCoordinate* gci, QGraphicsScene* scenei):
      gbi(gbii),
      gc(gci),
      scene(scenei)
{
    hei = gbi->getHeightCount();
    wid = gbi->getWidthCount();
}

itemCollector::~itemCollector()
{
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

void itemCollector::setMapElement(mapEngine *me)
{
    this->me = me;
    addMapElementList();
}

void itemCollector::setHeroFactory(heroFactory* hf, QList<struct externInfo> info)
{
    this->hf = hf;
    addHeroList(info);
}

void itemCollector::setCardEngine(cardEngine* ce)
{
    this->ce = ce;
    addCardList();
}

void itemCollector::setCampHealth()
{
    campHealth* ch = new campHealth(gbi->getConfigDir()+"health2.png");
    scene->addItem(ch);
    campLifes.append(ch);
    ch->setPos(200, 50);

    ch = new campHealth(gbi->getConfigDir()+"health1.png");
    scene->addItem(ch);
    campLifes.append(ch);
    ch->setPos(200, gbi->getPixmap().height()-200);

}

void itemCollector::addHeroList(QList<struct externInfo> info)
{
    QList<heroItem*> heros = hf->generateHeroes(info);
    for(int i=0; i<heros.size(); i++)
    {
        scene->addItem(heros.at(i));
        heros.at(i)->setPos(gc->getBeginPosOfHero(heros.at(i)->point()));
        if(heros.at(i)->camp() == camp_red)
        {
            redTeamHeros.append(heros.at(i));
        }
        else
        {
            blueTeamHeros.append(heros.at(i));
        }
    }

    for(int i=0; i<heros.size(); i++)
    {
        QGraphicsLineItem *targetLine = new QGraphicsLineItem();
        scene->addItem(targetLine);
        targetLine->hide();
        targetLines.append(targetLine);
    }
    addLocalHero(heros.at(0));
}

void itemCollector::addCardList()
{
    unusedCards = ce->generateHandCards();
}

void itemCollector::addMapElementList()
{
    elements = me->generateMapElements(wid, hei);
    for(int j=0; j<hei; j++)
    {
        for(int i=0; i<wid; i++)
        {
            elements[j*wid+i]->setPos(gc->getBeginPosWithCoo(QPoint(i, j)));
            scene->addItem(elements[j*wid+i]);
        }
    }
}

bool itemCollector::isPointAvailable(QPoint in)
{
    if(in.x()<0 || in.y()<0 || in.x()>=wid || in.y()>=hei)
        return false;
    else if((in.x() == wid-1) && (in.y()%2 == 1))
        return false;
    else if(!elements[getPointNumber(in)]->isPointAvailable())
        return false;
    else
        return true;
}

bool itemCollector::isPointMovable(QPoint in)
{
    return elements[getPointNumber(in)]->isMoveAvailable();
}

void itemCollector::restoreAllPen()
{
    for(int i=0; i<elements.size(); ++i)
    {
        elements.at(i)->setPen(QPen(Qt::black, 1));
    }
}


int itemCollector::getPointNumber(QPoint point)
{
    return point.x()+point.y()*wid;
}

heroItem* itemCollector::isPointHasHero(QPoint point)  //TODO change return type
{
    for(int i=0; i<redTeamHeros.size(); i++)
    {
        if(point == redTeamHeros.at(i)->point())
        {
            return redTeamHeros.at(i);
        }
    }
    for(int i=0; i<blueTeamHeros.size(); i++)
    {
        if(point == blueTeamHeros.at(i)->point())
        {
            return blueTeamHeros.at(i);
        }
    }
    return NULL;
}

bool itemCollector::listAddJudge(QList<QPoint>* set, QPoint point)
{
    if(type == ModeMove)
    {
        if(isPointAvailable(point) && isPointMovable(point))
        {
            if(isPointHasHero(point))
                return false;
            if(!set->contains(point))
                set->append(point);
            return true;
        }
    }
    else if(type == ModeAttack)
    {
        heroItem* hi = isPointHasHero(point);
        if(isPointAvailable(point) && hi)
        {
            if(hi->camp() == tempHero->camp())
                return false;
            if(!set->contains(point))
                set->append(point);
            return true;
        }
    }
    return false;
}

QList<QPoint> itemCollector::recursionSeries(QList<QPoint>*set, QPoint point, int range)
{
    if(range == 0)
        return *set;
    range--;
    QPoint pair;

    pair = gc->goUpLeft(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goUpRight(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goUp(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goDownLeft(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goDownRight(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    pair = gc->goDown(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, range);

    return *set;
}

QList<QPoint> itemCollector::listRange(heroItem* hero, enum rangeMode_t t)
{
    type = t;
    tempHero = hero;
    QList<QPoint> set;

    if(type == ModeMove)
        return recursionSeries(&set, hero->point(), hero->moveRange());
    else if(type == ModeAttack)
        return recursionSeries(&set, hero->point(), hero->attackRange());
}


heroItem* itemCollector::getHeroByPoint(QPoint point)
{
    for(int i=0; i<redTeamHeros.size(); i++)
    {
        if(point == redTeamHeros.at(i)->point())
        {
            return redTeamHeros.at(i);
        }
    }
    for(int i=0; i<blueTeamHeros.size(); i++)
    {
        if(point == blueTeamHeros.at(i)->point())
        {
            return blueTeamHeros.at(i);
        }
    }
    return NULL;
}

void itemCollector::setElementDefaultPen(QPoint point)
{
    if(!isPointAvailable(point))
        return;
    gameMapElement* gmeT = elements[getPointNumber(point)];
    gmeT->setDefaultZValue();
    gmeT->setDefaultPen();
}
void itemCollector::setElementRestorePen(QPoint point)
{
    if(!isPointAvailable(point))
        return;
    gameMapElement* gmeT = elements[getPointNumber(point)];
    gmeT->setZValue(0.7);
    gmeT->restorePen();
}

void itemCollector::setElementSpecialPen(QPoint point, QPen pen)
{
    if(!isPointAvailable(point))
        return;
    gameMapElement* gmeT = elements[getPointNumber(point)];
    setElementSpecialPen(gmeT, pen);
}

void itemCollector::setElementBoldPen(QPoint point, double width)
{
    if(!isPointAvailable(point))
        return;
    gameMapElement* gmeT = elements[getPointNumber(point)];
    gmeT->setZValue(0.7);
    gmeT->setPen(QPen(gmeT->getDefaultPen().color(), width));
}

void itemCollector::setElementSpecialPen(gameMapElement* gmeT, QPen pen)
{
    gmeT->setZValue(0.65); //TODO
    gmeT->setPen(pen);
}

QList<QString> itemCollector::getHeroListAvaterPath(char in)  //TODO change ui
{
    QList<QString> result;
    QList<heroItem*> recv;

    if(in == 'r')
    {
        recv = redTeamHeros;
    }
    else
    {
        recv = blueTeamHeros;
    }

    for(int i=0; i<recv.size(); i++)
    {
        QString temp = gbi->getConfigDir() + "/heros/" + recv[i]->heroName() + "_Head.png";
        result.append(temp);
    }
    return result;
}

QList<handCard*> itemCollector::getCard(int n)
{
    QList<handCard*> result;
    if(unusedCards.size()<n)
        n = unusedCards.size();
    for(int i=0; i<n; i++)
    {
        result.append(unusedCards[0]);
        unusedCards.removeAt(0);
    }
    qDebug()<<"unused cards:"<<unusedCards.size()<<"used:"<<n;
    return result;
}

QString itemCollector::rscPath()
{
    return gbi->getConfigDir();
}

QList<heroItem*> itemCollector::getActSequence()
{
    QList<heroItem*> result;

    for(int i=0; i<redTeamHeros.size(); i++)
    {
        result.append(blueTeamHeros[i]);
        result.append(redTeamHeros[i]);
    }
    return result;
}
