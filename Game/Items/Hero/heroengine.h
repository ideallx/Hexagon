#ifndef GAME_ITEMS_HERO_HEROENGINE_H_
#define GAME_ITEMS_HERO_HEROENGINE_H_

#include <QMap>
#include <QString>
#include <QPoint>
#include <QGraphicsScene>
#include <QDebug>
#include <QMargins>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include "enums.h"

class GameBackInfo;
class HeroItem;
class SkillBase;

class AbstractHeroPacakage : public QObject {
 public:
    virtual int heroNumInPackage() = 0;
    virtual HeroPackage heroPackageIndicator() = 0;
    virtual HeroInfo getHeroInfo(int n) = 0;
    virtual QList<SkillBase*> getSkillByHeroNum(int i) = 0;
};


class HeroFactory : public QObject {
 public:
    explicit HeroFactory(GameBackInfo* gbi);

    HeroItem* createHero(ExternInfo);
    QList<HeroItem*> generateHeroes(QList<ExternInfo>);

    int getHeroAmount() { return heroAmount; }
    void addPackage(AbstractHeroPacakage* ahp);
    HeroInfo getHeroInfoByNum(HeroNum hn);

 private:
    QGraphicsScene* scene;
    QList<AbstractHeroPacakage*> hpl;
    QString innerDir;
    int lineLength;
    int heroAmount;

 friend class VvTestTest;
};




#endif  // GAME_ITEMS_HERO_HEROENGINE_H_
