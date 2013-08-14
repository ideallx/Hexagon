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


class gameBackInfo;
class heroItem;
enum camp_t;


enum heroNum_t
{
    MieShaZhe,
    RenZhe,
    AnYingZhiRen,
    LeiShen,
    ShengQiShi,
    KuangSha,
    YingYan,
    LingHunYiZhe,
    BingZhiShengNv,
    ZhongKaiZhanShi,
    QiYueZhe,
    BaoXiong,
    ShiHunZhe,
    FengXingZhe,
    DuTu,
    XueZhiLiZhua,
    SiShen,
    HuanYingZhiQiang,
    ZhanLanZhiJian,
    HuoWuZhe
};

struct heroInfo
{
    int attackRange;
    int moveRange;
    int healthMax;
    char sexual;
    QString heroName;

};

struct externInfo
{
    enum heroNum_t h;
    enum camp_t c;
    QPoint p;
};


class heroFactory : public QObject
{
public:


    heroFactory(gameBackInfo* gbi);
    heroItem* createHero(enum heroNum_t, QPoint, enum camp_t);
    QList<heroItem*> generateHeroes(QList<struct externInfo>);
    int getHeroAmount() { return heroInfoMap.size(); }

private:
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

    QMap<enum heroNum_t, struct heroInfo> heroInfoMap;
    int lineLength;
    QGraphicsScene* scene;
    QString innerDir;
};

class heroPackage : QObject
{
    virtual int packageHeroBeginNum();
    virtual int packageHeroAmount();
};


#endif // HEROENGINE_H
