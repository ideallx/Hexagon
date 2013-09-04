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

class AbstractHeroPacakage : public QObject {
 public:
    virtual int heroNumInPackage() = 0;
    virtual enum hero_package_t heroPackageIndicator() = 0;
    virtual struct heroInfo getHeroInfo(int n) = 0;
};

class HeroPackageNormal : public AbstractHeroPacakage {
 public:
    HeroPackageNormal();
    int heroNumInPackage() { return 20; }
    enum hero_package_t heroPackageIndicator() { return HeroPackage_Normal; }
    struct heroInfo getHeroInfo(int n) { return hil[n]; }

 private:
    QList<struct heroInfo> hil;
};

class HeroFactory : public QObject {
 public:
    explicit HeroFactory(GameBackInfo* gbi);

    HeroItem* createHero(struct externInfo);
    QList<HeroItem*> generateHeroes(QList<struct externInfo>);

    int getHeroAmount() { return heroAmount; }
    void addPackage(AbstractHeroPacakage* ahp);
    struct heroInfo getHeroInfoByNum(int n);

 private:
    QList<AbstractHeroPacakage*> hpl;
    QGraphicsScene* scene;
    QString innerDir;
    int lineLength;
    int heroAmount;
};
#endif  // GAME_ITEMS_HERO_HEROENGINE_H_
