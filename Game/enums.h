#ifndef ENUMS_H
#define ENUMS_H

/**
 *
 *for debug
 *
 */

#include <QString>
#include <QPoint>

enum gameEnvironment_t
{
    areaSpace,
    areaGrass   = '1',
    areaStone   = '2',
    areaShop    = '3',
    areaAlchemy = '4',
    areaSpring  = '5',
    areaCamp    = '6',
    areaSwamp   = '7',
    areaDesert  = '8',
    areaWater   = '9',


    areaFort    = 'J',
    areaRedHome = 'K',
    areaTree    = 'L',
    areaBlueHome= 'M',

    areaNouse = 'Z'
};

enum triggerTime_t
{
    TriggerGameBegin,
    TriggerRoundBegin,
    TriggerTurnBegin,
    TriggerMoveBegin,
    TriggerMoveEnd,
    TriggerAttackBegin,
    TriggerAttackEnd,
    TriggerOtherSkillBegin,
    TriggerOtherSkillEnd,
    TriggerTurnEnd,
    TriggerRoundEnd,
    TriggerGameEnd
};

enum mapRangeType_t
{
    RangeTypeStraight,
    RangeTypeDoubleLine,
    RangeTypeRound
};


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

enum camp_t
{
    camp_red,
    camp_blue
};

enum sexual_t
{
    sex_male,
    sex_female
};

enum hero_package_t
{
	HeroPackage_Normal,
	HeroPackage_Extend1,
	HeroPackage_Extend2
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

#endif // ENUMS_H
