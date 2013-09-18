#ifndef GAME_ENUMS_H_
#define GAME_ENUMS_H_

#include <QString>
#include <QPoint>

enum GameEnvironment_t {
    AreaSpace,
    AreaGrass   = '1',
    AreaStone   = '2',
    AreaShop    = '3',
    AreaAlchemy = '4',
    AreaSpring  = '5',
    AreaCamp    = '6',
    AreaSwamp   = '7',
    AreaDesert  = '8',
    AreaWater   = '9',

    AreaFort    = 'J',
    AreaRedHome = 'K',
    AreaTree    = 'L',
    AreaBlueHome= 'M',

    AreaNouse = 'Z'
};

enum TriggerTime_t {
    TriggerNever,
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
    TriggerGameEnd,
    TriggerInAction
};

enum MapRangeType_t {
    RangeTypeStraight,
    RangeTypeDoubleLine,
    RangeTypeRound
};


enum HeroNum_t {
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

enum Camp_t {
    camp_red,
    camp_blue
};

enum Sexual_t {
    sex_male,
    sex_female
};

enum Hero_package_t {
    HeroPackage_Normal,
    HeroPackage_Extend1,
    HeroPackage_Extend2
};

enum Card_Package_t {
    CardPackage_Normal,
    CardPackage_Extend1,
    CardPackage_Extend2
};

enum EquipmentPackage_t {
    EquipmentPackage_Normal,
    EquipmentPackage_Extend1,
    EquipmentPackage_Extend2
};

struct HeroInfo {
    int attackRange;
    int moveRange;
    int healthMax;
    enum Sexual_t sexual;
    QString heroName;
};

struct ExternInfo {
    int h;
    enum Camp_t c;
    QPoint p;
};

enum AttackBuffEffect {
    AttackBuffAddDamage,
    AttackBuffAddStat
};

struct AttackBuff {
    enum AttackBuffEffect abe;
    union {
    int stateType;
    int damage;
    };
    int probability;
};

struct CardInfo {
    int cardType;
    enum Card_Package_t cardPackage;
    int cardId;
    QString name;
};


enum Card_Normal_Package_Type_t {
    KuangBao,
    ZheYue,
    FaLiRanShao,
    ShengMingLiZan,
    ChuanSong,
    FangYuFuWen,
    ZhuangTaiJingHua,
    MoFaHuDun,
    MoFaZhiHeng,
    MoJingBaoDan,
    NengLiangXianJing,
    JinBi_2,
    JinBi_3,
    JinBi_4,
    ZhengJingJi,
    JiJiuYao,
    ShanBi
};

enum SkillType_t {
    SkillActive,
    SkillPositive,
    SkillPositiveTrigger
};

enum EquipmentType_t {
    EquipWeapon,
    EquipArmor,
    EquipOmament,
    EquipShoe
};

struct EquipmentInfo {
    enum EquipmentType_t type;
    enum EquipmentPackage_t eqPackage;
    int equipmentId;
    int price;
    QString path;
    QString name;
};

#endif  // GAME_ENUMS_H_
