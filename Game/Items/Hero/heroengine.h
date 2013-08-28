#ifndef HEROENGINE_H
#define HEROENGINE_H

#include <QMap>
#include <QString>
#include <QPoint>
#include <QGraphicsScene>
#include <QDebug>
#include <QMargins>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include "enums.h"


class gameBackInfo;
class heroItem;
enum camp_t;

class heroFactory : public QObject
{
public:
    heroFactory(gameBackInfo* gbi);

    heroItem* createHero(enum heroNum_t, QPoint, enum camp_t);
    QList<heroItem*> generateHeroes(QList<struct externInfo>);

    int getHeroAmount() { return heroInfoMap.size(); }
	QPixmap getHeroAvaterByNum(int n);
	void addPackage(enum hero_package_t);

private:

    QMap<enum heroNum_t, struct heroInfo> heroInfoMap;
    int lineLength;
    QGraphicsScene* scene;
    QString innerDir;
};

class AbstractHeroPacakage : public QObject
{
	virtual int heroNumInPackage() = 0;
	virtual enum hero_package_t heroPackageIndicator() = 0; 
};

class HeroPackageNormal : public AbstractHeroPacakage
{
	int heroNumInPackage() { return 20; }
	enum hero_package_t heroPackageIndicator() { return HeroPackage_Normal; }
	
    static const struct heroInfo msz;
    static const struct heroInfo ls;
    static const struct heroInfo bzsn;
    static const struct heroInfo hwz;
    static const struct heroInfo fxz;
    static const struct heroInfo hyzq;
    static const struct heroInfo lhyz;
    static const struct heroInfo dt;
    static const struct heroInfo yy;
    static const struct heroInfo shz;
    static const struct heroInfo ayzr;
    static const struct heroInfo rz;
    static const struct heroInfo xzlz;
    static const struct heroInfo qyz;
    static const struct heroInfo sqs;
    static const struct heroInfo zlzj;
    static const struct heroInfo zkzs;
    static const struct heroInfo ks;
    static const struct heroInfo ss;
    static const struct heroInfo bx;

};


#endif // HEROENGINE_H
