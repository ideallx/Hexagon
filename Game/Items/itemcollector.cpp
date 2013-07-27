#include "itemcollector.h"

itemCollector::itemCollector(gameBackInfo* gbii, gameCoordinate* gci, QGraphicsScene* scenei):
      gbi(gbii),
      gc(gci),
      scene(scenei)
{
    hei = gbi->getHeightCount();
    wid = gbi->getWidthCount();
}

void itemCollector::setMapElement()
{
    addMapElementList();
}

void itemCollector::setHeroFactory(heroFactory* hf, QList<heroFactory::ExternInfo> info)
{
    this->hf = hf;
    addHeroList(info);
}

void itemCollector::setCardEngine(cardEngine* ce)
{
    this->ce = ce;
    addCardList();
}

void itemCollector::addHeroList(QList<heroFactory::ExternInfo> info)
{
    QList<heroItem*> heros = hf->generateHeroes(info);
    for(int i=0; i<heros.size(); i++)
    {
        scene->addItem(heros.at(i));
        heros.at(i)->setPos(gc->getBeginPosOfHero(heros.at(i)->getPoint()));
        if(heros.at(i)->getCamp() == heroItem::camp_red)
        {
            redTeamHeros.append(heros.at(i));
        }
        else
        {
            blueTeamHeros.append(heros.at(i));
        }
    }
}

void itemCollector::addCardList()
{
    unusedCards = ce->generateHandCards();
}

void itemCollector::addMapElementList()
{
    QVector<char> map = gbi->getMapElement();
    for(int j=0; j<hei; j++)
    {
        for(int i=0; i<wid; i++)
        {
            gameMapElement *mapItem = new gameMapElement(gbi->getLineLength(), map[i+j*wid], QPoint(i, j), gbi->getConfigDir());
            elements.append(mapItem);
            mapItem->hide();
            if(mapItem->isPointAvailable())
            {
                mapItem->setPos(gc->getBeginPosWithCoo(QPoint(i, j)));
                mapItem->show();
                scene->addItem(mapItem);
            }
        }
    }
}

bool itemCollector::isPointAvailable(QPoint in)
{
    if(in.x()<0 || in.y()<0 || in.x()>=wid || in.y()>=hei)
        return false;
    else if((in.x() == wid-1) && (in.y()%2 == 1))
        return false;
    else if(elements[getBlockNumber(in)]->isPointAvailable())
        return false;
    else
        return true;
}

bool itemCollector::isPointMovable(QPoint in)
{
    return elements[getBlockNumber(in)]->isMoveAvailable();
}

void itemCollector::restoreAllPen()
{
    for(int i=0; i<elements.size(); ++i)
    {
        elements.at(i)->setPen(QPen(Qt::black, 1));
    }
}


int itemCollector::getBlockNumber(QPoint point)
{
    return point.x()+point.y()*wid;
}

bool itemCollector::isPointHasHero(QPoint point)
{
    for(int i=0; i<redTeamHeros.size(); i++)
    {
        if(point == redTeamHeros.at(i)->getPoint())
        {
            return true;
        }
    }
    for(int i=0; i<blueTeamHeros.size(); i++)
    {
        if(point == blueTeamHeros.at(i)->getPoint())
        {
            return true;
        }
    }
    return false;
}

bool itemCollector::listAddJudge(QList<QPoint>set, QPoint point)
{
    if(type == 'm')
    {
        if(isPointAvailable(point) && isPointMovable(point))
        {
            if(isPointHasHero(point))
                return true;
            if(!set.contains(point))
                set.append(point);
            return true;
        }
    }
    else if(type == 'a')
    {
        if(isPointAvailable(point) && isPointHasHero(point))
        {
            if(!set.contains(point))
                set.append(point);
            return true;
        }
    }
    return false;
}

QList<QPoint> itemCollector::recursionSeries(QList<QPoint>set, QPoint point, int sphere)
{
    if(!listAddJudge(set, point))
        return set;
    if(sphere == 0)
        return set;
    sphere--;
    QPoint pair;

    pair = gc->goUpLeft(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, sphere);

    pair = gc->goUpRight(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, sphere);

    pair = gc->goUp(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, sphere);

    pair = gc->goDownLeft(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, sphere);

    pair = gc->goDownRight(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, sphere);

    pair = gc->goDown(point);
    if(listAddJudge(set, pair))
        recursionSeries(set, pair, sphere);

    return set;
}

QList<QPoint> itemCollector::listSphere(QPoint point, int sphere, char t)
{
    QList<QPoint> set;
    type = t;
    return recursionSeries(set, point, sphere);
}

