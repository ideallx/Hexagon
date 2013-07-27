#ifndef HEROENGINE_H
#define HEROENGINE_H

#include <QtWidgets>

#include "backinfo.h"
#include "heroitem.h"
#include "herowhole.h"

struct heroInfo
{
    int moveSphere;
    int attackSphere;
    int healthMax;
    char sexual;
    QString heroName;

};

class heroFactory : public QObject
{
public:
    typedef enum heroNum_t
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
        HuoWuZhe,

        PackageII,

        UserDefined
    }heroNum;

    typedef struct externInfo
    {
        heroNum h;
        heroItem::heroCamp c;
        QPoint p;
    }ExternInfo;

    heroFactory(gameBackInfo* gbi, QGraphicsScene* scene);
    heroItem* createHero(heroNum, QPoint, heroItem::heroCamp);
    QList<heroItem*> generateHeroes(QList<ExternInfo>);

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

    QMap<heroNum, struct heroInfo> heroInfoMap;
    int lineLength;
    QGraphicsScene* scene;
    QString innerDir;
};

#endif // HEROENGINE_H
