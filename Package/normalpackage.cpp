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


#define HeroInfoStructBuild(Abbr, AR, MR, HP, SEX, Name) \
    const struct heroInfo HeroPackageNormal::##Abbr = \
{ AR, MR, HP, SEX, Name }


HeroPackageNormal::HeroPackageNormal() {
    const struct HeroInfo msz  = {1, 4, 8,  sex_female,
                                  tr("MieShaZhe")};
    const struct HeroInfo ls   = {1, 2, 8,  sex_male,
                                  tr("LeiShen")};
    const struct HeroInfo bzsn = {1, 2, 8,  sex_female,
                                  tr("BingZhiShengNv")};
    const struct HeroInfo hwz  = {1, 2, 8,  sex_female,
                                  tr("HuoWuZhe")};
    const struct HeroInfo fxz  = {1, 3, 7,  sex_female,
                                  tr("FengXingZhe")};
    const struct HeroInfo hyzq = {1, 3, 8,  sex_female,
                                  tr("HuanYingZhiQiang")};
    const struct HeroInfo lhyz = {1, 3, 7,  sex_female,
                                  tr("LingHunYiZhe")};
    const struct HeroInfo dt   = {1, 4, 8,  sex_male,
                                  tr("DuTu")};
    const struct HeroInfo yy   = {1, 3, 8,  sex_male,
                                  tr("YingYan")};
    const struct HeroInfo shz  = {1, 4, 8,  sex_female,
                                  tr("ShiHunZhe")};
    const struct HeroInfo ayzr = {1, 4, 7,  sex_male,
                                  tr("AnYingZhiRen")};
    const struct HeroInfo rz   = {1, 4, 8,  sex_male,
                                  tr("RenZhe")};
    const struct HeroInfo xzlz = {1, 4, 8,  sex_male,
                                  tr("XueZhiLiZhua")};
    const struct HeroInfo qyz  = {1, 4, 8,  sex_male,
                                  tr("QiYueZhe")};
    const struct HeroInfo sqs  = {1, 3, 8,  sex_female,
                                  tr("ShengQiShi")};
    const struct HeroInfo zlzj = {1, 3, 9,  sex_male,
                                  tr("ZhanLanZhiJian")};
    const struct HeroInfo zkzs = {1, 3, 10, sex_male,
                                  tr("ZhongKaiZhanShi")};
    const struct HeroInfo ks   = {1, 3, 9,  sex_male,
                                  tr("KuangSha")};
    const struct HeroInfo ss   = {1, 3, 9,  sex_male,
                                  tr("SiShen")};
    const struct HeroInfo bx   = {1, 4, 8,  sex_male,
                                  tr("BaoXiong")};

    hil.append(msz);
    hil.append(rz);
    hil.append(ayzr);
    hil.append(ls);
    hil.append(sqs);
    hil.append(ks);
    hil.append(yy);
    hil.append(lhyz);
    hil.append(bzsn);
    hil.append(zkzs);
    hil.append(qyz);
    hil.append(bx);
    hil.append(shz);
    hil.append(fxz);
    hil.append(dt);
    hil.append(xzlz);
    hil.append(hyzq);
    hil.append(ss);
    hil.append(zlzj);
    hil.append(hwz);
}



CsKuangBao::CsKuangBao()
    : AttackBuffSkill(AttackBuffAddDamage, 1, 0x3F) {
    setObjectName("KuangBao");
}

void CsKuangBao::skillAct(struct SkillPara sp) {
    Q_UNUSED(sp);
}

void CsKuangBao::skillClicked(SkillPara sp) {
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
    : AttackBuffSkill(AttackBuffAddDamage, 0, 0x3F, 0, 0) {
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

void HsGuiShou::skillClicked(SkillPara sp) {
    Q_UNUSED(sp);
}


HsQianXing::HsQianXing()
    : AttackBuffSkill(AttackBuffAddDamage, 1, 0x3F, 2, 2) {
    setObjectName("QianXing");
}

void HsQianXing::skillAct(struct SkillPara sp) {
    // get physical immune
}

void HsQianXing::skillClicked(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->addNextAttackBouns(buffEffect());
    this->addCoolDown(this->cdMax());
}

HsLengXue::HsLengXue()
    : AttackBuffSkill(AttackBuffMustHit, 0, 0x3F, 2, 2) {
    setObjectName("LengXue");
}

void HsLengXue::skillAct(struct SkillPara sp) {
    HeroItem* fr = static_cast<HeroItem*>(sp.from);
    HeroItem* to = static_cast<HeroItem*>(sp.from);
    to->addHealth(- fr->attack());  // change to suffer magic
}

void HsLengXue::skillClicked(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->addNextAttackBouns(buffEffect());
    this->addCoolDown(this->cdMax());
}
