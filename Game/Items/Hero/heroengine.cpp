#include "heroengine.h"

const struct heroInfo heroFactory::msz  = {"mieShaZhe", 1, 3, 7, heroItem::sex_female};
const struct heroInfo heroFactory::ls   = {"leiShen",   1, 2, 8, heroItem::sex_male};

heroFactory::heroFactory(QString dir, int l, gameCoordinate* g, backScene* scene):
    innerDir(dir),
    lineLength(l),
    gc(g),
    scene(scene)
{
    heroInfoMap[MieShaZhe] = msz;
    heroInfoMap[LeiShen] = ls;
}

heroItem* heroFactory::createHero(heroNum hero, QPoint pt, heroItem::heroCamp c)
{
    heroItem * item = new heroItem(lineLength);
    item->setBrush(QPixmap(innerDir + heroInfoMap[hero].heroName + "_Head.png").scaledToWidth(lineLength*1.6));
    item->setHeroProperty(heroInfoMap[hero].sexual, heroInfoMap[hero].attackSphere, heroInfoMap[hero].moveSphere, heroInfoMap[hero].healthMax);
    item->setPoint(pt);
    item->setCamp(c);
    item->setPos(gc->getBeginPosOfHero(pt));

    return item;
}
