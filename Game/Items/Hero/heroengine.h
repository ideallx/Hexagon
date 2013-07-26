#ifndef HEROENGINE_H
#define HEROENGINE_H

#include <QtWidgets>

#include "coordinate.h"
#include "heroitem.h"
#include "heronormalpackage.h"
#include "herowhole.h"
#include "backscene.h"


struct heroInfo
{
    QString heroName;
    int moveSphere;
    int attackSphere;
    int healthMax;
    char sexual;

};

class heroFactory
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

    heroFactory(QString dir, int lineLength, gameCoordinate* gc, backScene* scene);
    heroItem* createHero(heroNum, QPoint, heroItem::heroCamp);

private:
    static const struct heroInfo msz;
    static const struct heroInfo ls;

    gameCoordinate* gc;
    QMap<heroNum, struct heroInfo> heroInfoMap;
    int lineLength;
    backScene* scene;
    QString innerDir;
};

#endif // HEROENGINE_H
