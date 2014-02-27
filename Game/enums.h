#ifndef GAME_ENUMS_H_
#define GAME_ENUMS_H_

#include <QString>
#include <QPoint>

enum class AreaHexagon {
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

enum class TriggerTime {
    TriggerNever,
    TriggerGameBegin,
    TriggerRoundBegin,
    TriggerTurnBegin,
    TriggerMoveBegin,
    TriggerMoveEnd,
    TriggerAttackBegin,
    TriggerAttackHit,
    TriggerAttackEnd,
    TriggerOtherSkillBegin,
    TriggerOtherSkillEnd,
    TriggerTurnEnd,
    TriggerRoundEnd,
    TriggerGameEnd,
    TriggerInAction
};

enum class MapRangeType {
    RangeTypeStraight,
    RangeTypeDoubleLine,
    RangeTypeRound
};


enum class HeroNum {
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

enum class Camp {
    CampRed,
    CampBlue
};

enum class Sexual {
    SexMale,
    SexFemale
};

enum class HeroPackage {
    HeroPackage_Normal,
    HeroPackage_Extend1,
    HeroPackage_Extend2
};

enum class CardPackage {
    CardPackage_Normal,
    CardPackage_Extend1,
    CardPackage_Extend2
};

enum class EquipmentPackage {
    EquipmentPackage_Normal,
    EquipmentPackage_Extend1,
    EquipmentPackage_Extend2
};

class HeroInfo {
 public:
    int attackRange;
    int moveRange;
    int healthMax;
    Sexual sexual;
    QString heroName;
};

class ExternInfo {
 public:
    HeroNum h;
    Camp c;
    QPoint p;
};

enum class AttackBuffEffect {
    AttackBuffAddDamage,
    AttackBuffAddStat,
    AttackBuffMustHit,
    AttackBuffMoreAttack
};

class AttackBuff {
 public:
    AttackBuffEffect abe;
    union {
    int stateType;
    int damage;
    };
    int probability;
};

enum class CardNormalPackageType {
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

class CardInfo {
 public:
    CardNormalPackageType cardType;
    CardPackage cardPackage;
    QString name;
};


enum class EquipNormalPackageId {
    AnJingLingZhiXue,
    ANuoDeZhiDun,
    BuLanQiZhiJie,
    FuLuoKenShenZhang,
    JinGuBang,
    LaoQianDeDaoJu,
    LieRiGong,
    LongWangFaZhang,
    MoShuYangDePiFeng,
    RanShaoZhiFu,
    XueJingLingBiShou,
    YuShenDeZhuFu
};

enum class HeroState {
    HeroStatePhysicalImmune,
    HeroStateSilence,
    HeroStateStunned,
    HeroStateUnmoveable
};

enum class SkillType {
    SkillActive,
    SkillPositive,
    SkillPositiveTrigger
};

enum class EquipmentType {
    EquipWeapon,
    EquipArmor,
    EquipOmament,
    EquipShoe
};

enum class SufferType {
    SufferPhysical,
    SufferMagic
};

enum class GameMenuType {
    Move,
    Attack,
    Skill,
    Cancel,
    EndTurn,
    SkillTest
};

class EquipmentInfo {
 public:
    EquipmentType type;
    EquipmentPackage eqPackage;
    EquipNormalPackageId equipmentId;
    int price;
    QString name;
};

#endif  // GAME_ENUMS_H_
