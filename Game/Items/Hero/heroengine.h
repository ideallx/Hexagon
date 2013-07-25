#ifndef HEROENGINE_H
#define HEROENGINE_H

#include "heroitem.h"
#include "heronormalpackage.h"
#include "herowhole.h"

class heroFactory
{
public:
    heroItem* createHero(enum heroNum_t hero);

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
        HuoWuZhe,

        PackageII,

        UserDefined


    };
};

#endif // HEROENGINE_H
