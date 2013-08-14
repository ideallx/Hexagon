#ifndef ENUMS_H
#define ENUMS_H

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

#endif // ENUMS_H
