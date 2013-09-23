#include "eventcenter.h"
#include "mapelement.h"
#include "mapmark.h"
#include "normalpackage.h"
#include "heroitem.h"

CardPackageNormal::CardPackageNormal() {
    const struct CardInfo kb   = {KuangBao, CardPackage_Normal, 0,
                                  tr("KuangBao")};
    const struct CardInfo zy   = {ZheYue, CardPackage_Normal, 0,
                                  tr("ZheYue")};
    const struct CardInfo flrs = {FaLiRanShao, CardPackage_Normal, 0,
                                  tr("FaLiRanShao")};
    const struct CardInfo smlz = {ShengMingLiZan, CardPackage_Normal, 0,
                                  tr("ShengMingLiZan")};
    const struct CardInfo cs   = {ChuanSong, CardPackage_Normal, 0,
                                  tr("ChuanSong")};
    const struct CardInfo fyfw = {FangYuFuWen, CardPackage_Normal, 0,
                                  tr("FangYuFuWen")};
    const struct CardInfo ztjh = {ZhuangTaiJingHua, CardPackage_Normal, 0,
                                  tr("ZhuangTaiJingHua")};
    const struct CardInfo mfhd = {MoFaHuDun, CardPackage_Normal, 0,
                                  tr("MoFaHuDun")};
    const struct CardInfo mfzh = {MoFaZhiHeng, CardPackage_Normal, 0,
                                  tr("MoFaZhiHeng")};
    const struct CardInfo mjbd = {MoJingBaoDan, CardPackage_Normal, 0,
                                  tr("MoJingBaoDan")};
    const struct CardInfo nlxj = {NengLiangXianJing, CardPackage_Normal, 0,
                                  tr("NengLiangXianJing")};
    const struct CardInfo jb2  = {JinBi_2, CardPackage_Normal, 0,
                                  tr("JinBi_2")};
    const struct CardInfo jb3  = {JinBi_3, CardPackage_Normal, 0,
                                  tr("JinBi_3")};
    const struct CardInfo jb4  = {JinBi_4,  CardPackage_Normal, 0,
                                  tr("JinBi_4")};
    const struct CardInfo zjj  = {ZhengJingJi, CardPackage_Normal, 0,
                                  tr("ZhengJingJi")};
    const struct CardInfo jjy  = {JiJiuYao, CardPackage_Normal, 0,
                                  tr("JiJiuYao")};
    const struct CardInfo sb   = {ShanBi, CardPackage_Normal, 0,
                                  tr("ShanBi")};

    skillHash.insert(KuangBao, new CsKuangBao);
    skillHash.insert(ZheYue, new CsZheYue);
    skillHash.insert(ShengMingLiZan, new CsShengMingLiZan);
    skillHash.insert(ChuanSong, new CsChuanSong);
    skillHash.insert(JinBi_2, new CsMoney(2));
    skillHash.insert(JinBi_3, new CsMoney(3));
    skillHash.insert(JinBi_4, new CsMoney(4));
    // skillHash.insert(NengLiangXianJing, new CsNengLiangXianJing(path))

    int i = 0;

    for (i = 0; i < 2; i++) {
        cil.append(fyfw);
        cil.append(jjy);
        cil.append(zjj);
        cil.append(smlz);
        cil.append(mfzh);
        cil.append(flrs);
    }
    for (i = 0; i < 3; i++) {
        cil.append(sb);
        cil.append(jb2);
        cil.append(nlxj);
        cil.append(cs);
        cil.append(zy);
    }
    for (i = 0; i < 4; i++) {
        cil.append(mfhd);
    }
    for (i = 0; i < 5; i++) {
        cil.append(kb);
    }
    for (i = 0; i < 6; i++) {
        cil.append(jb3);
        cil.append(jb4);
        cil.append(ztjh);
        cil.append(mjbd);
    }
}

#define BUILDEQUIP const struct EquipmentInfo
EquipmentPackageNormal::EquipmentPackageNormal() {
    BUILDEQUIP ajlzx = {EquipShoe, EquipmentPackage_Normal,
                        AnJingLingZhiXue, 4, "AnJingLingZhiXue"};
    BUILDEQUIP andzd = {EquipArmor, EquipmentPackage_Normal,
                        ANuoDeZhiDun, 5, "ANuoDeZhiDun"};
    BUILDEQUIP blqzj = {EquipOmament, EquipmentPackage_Normal,
                        BuLanQiZhiJie, 4, "BuLanQiZhiJie"};
    BUILDEQUIP flksz = {EquipWeapon, EquipmentPackage_Normal,
                        FuLuoKenShenZhang, 8, "FuLuoKenShenZhang"};
    BUILDEQUIP jgb   = {EquipWeapon, EquipmentPackage_Normal,
                        JinGuBang, 7, "JinGuBang"};
    BUILDEQUIP lqddj = {EquipOmament, EquipmentPackage_Normal,
                        LaoQianDeDaoJu, 4, "LaoQianDeDaoJu"};
    BUILDEQUIP lrg   = {EquipWeapon, EquipmentPackage_Normal,
                        LieRiGong, 7, "LieRiGong"};
    BUILDEQUIP lwfz  = {EquipWeapon, EquipmentPackage_Normal,
                        LongWangFaZhang, 6, "LongWangFaZhang"};
    BUILDEQUIP msypf = {EquipArmor, EquipmentPackage_Normal,
                        MoShuYangDePiFeng, 6, "MoShuYangDePiFeng"};
    BUILDEQUIP rszf  = {EquipWeapon, EquipmentPackage_Normal,
                        RanShaoZhiFu, 6, "RanShaoZhiFu"};
    BUILDEQUIP xjlbs = {EquipWeapon, EquipmentPackage_Normal,
                        XueJingLingBiShou, 8, "XueJingLingBiShou"};
    BUILDEQUIP ysdzf = {EquipArmor, EquipmentPackage_Normal,
                        YuShenDeZhuFu, 5, "YuShenDeZhuFu"};
    eil.append(ajlzx);
    eil.append(andzd);
    eil.append(blqzj);
    eil.append(flksz);
    eil.append(jgb);
    eil.append(lqddj);
    eil.append(lrg);
    eil.append(lwfz);
    eil.append(msypf);
    eil.append(rszf);
    eil.append(xjlbs);
    eil.append(ysdzf);
}

CsKuangBao::CsKuangBao()
    : AttackBuffSkill(AttackBuffAddDamage, 1, 6) {
    setObjectName("KuangBao");
}

void CsKuangBao::skillAct(struct SkillPara sp) {
    Q_UNUSED(sp);
}

void CsKuangBao::skillPrepare(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->addNextAttackBouns(buffEffect());
}

CsZheYue::CsZheYue()
    : RangeSkill(RangeTypeRound, 2) {
    setObjectName("ZheYue");
}

void CsZheYue::skillAct(SkillPara sp) {
    sp.ec->setHeroPosition(static_cast<HeroItem*>(sp.from),
                           static_cast<GameMapElement*>(sp.to)->point());
}

CsShengMingLiZan::CsShengMingLiZan()
    : RangeSkill(RangeTypeRound, 1) {
    setObjectName("ShengMingLiZan");
}

void CsShengMingLiZan::skillAct(SkillPara sp) {
    QList<QPoint> lp = sp.ec->getPointInRange(
                static_cast<HeroItem*>(sp.from)->point(),
                RangeTypeRound, 1);
    foreach(QPoint p, lp) {
        HeroItem* hi = sp.ec->hasHeroOnPoint(p);
        if (hi)
            hi->addHealth(1);
    }
}

CsChuanSong::CsChuanSong()
    : RangeSkill(RangeTypeRound, 1) {
    setObjectName("ChuanSong");
}

void CsChuanSong::skillAct(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    sp.ec->setHeroPosition(hi, static_cast<GameMapElement*>(sp.to)->point());
}

void CsChuanSong::skillRange(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    QList<HeroItem*> friendHeros = sp.ec->getHerosOfCamp(hi->camp());
    QList<QPoint> lp;
    foreach(HeroItem* hi, friendHeros) {
        lp += sp.ec->getPointInRange(hi->point(), RangeTypeRound, 1);
    }
    sp.ec->showSkillRange(lp);
}

CsNengLiangXianJing::CsNengLiangXianJing(QString path, int width)
    : MapMarkSkill(new MapMark(path, width), -1) {
}










HsGuiShou::HsGuiShou()
    : AttackBuffSkill(AttackBuffAddDamage, 0, 6) {
    setObjectName("GuiShou");
}

void HsGuiShou::skillAct(SkillPara sp) {
    HeroItem* toHero = static_cast<HeroItem*>(sp.to);
    if (toHero->cards().size() == 0) {
        toHero->addHealth(-1);
    } else {
        QList<HandCard*> hcl = sp.ec->discardCard(toHero, 1);
        HeroItem* fromHero = static_cast<HeroItem*>(sp.from);
        fromHero->addCards(hcl);

    }
}

void HsGuiShou::skillPrepare(SkillPara sp) {
    Q_UNUSED(sp);
}
