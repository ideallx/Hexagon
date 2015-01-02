#include "eventcenter.h"
#include "mapelement.h"
#include "mapmark.h"
#include "normalpackage.h"
#include "heroitem.h"

CardPackageNormal::CardPackageNormal() {
    const CardInfo kb   = {CardNormalPackageType::KuangBao,
                           CardPackage::CardPackage_Normal, tr("KuangBao")};
    const CardInfo zy   = {CardNormalPackageType::ZheYue,
                           CardPackage::CardPackage_Normal, tr("ZheYue")};
    const CardInfo flrs = {CardNormalPackageType::FaLiRanShao,
                           CardPackage::CardPackage_Normal, tr("FaLiRanShao")};
    const CardInfo smlz = {CardNormalPackageType::ShengMingLiZan,
                           CardPackage::CardPackage_Normal, tr("ShengMingLiZan")};
    const CardInfo cs   = {CardNormalPackageType::ChuanSong,
                           CardPackage::CardPackage_Normal, tr("ChuanSong")};
    const CardInfo fyfw = {CardNormalPackageType::FangYuFuWen,
                           CardPackage::CardPackage_Normal, tr("FangYuFuWen")};
    const CardInfo ztjh = {CardNormalPackageType::ZhuangTaiJingHua,
                           CardPackage::CardPackage_Normal, tr("ZhuangTaiJingHua")};
    const CardInfo mfhd = {CardNormalPackageType::MoFaHuDun,
                           CardPackage::CardPackage_Normal, tr("MoFaHuDun")};
    const CardInfo mfzh = {CardNormalPackageType::MoFaZhiHeng,
                           CardPackage::CardPackage_Normal, tr("MoFaZhiHeng")};
    const CardInfo mjbd = {CardNormalPackageType::MoJingBaoDan,
                           CardPackage::CardPackage_Normal, tr("MoJingBaoDan")};
    const CardInfo nlxj = {CardNormalPackageType::NengLiangXianJing,
                           CardPackage::CardPackage_Normal, tr("NengLiangXianJing")};
    const CardInfo jb2  = {CardNormalPackageType::JinBi_2,
                           CardPackage::CardPackage_Normal, tr("JinBi_2")};
    const CardInfo jb3  = {CardNormalPackageType::JinBi_3,
                           CardPackage::CardPackage_Normal, tr("JinBi_3")};
    const CardInfo jb4  = {CardNormalPackageType::JinBi_4,
                           CardPackage::CardPackage_Normal, tr("JinBi_4")};
    const CardInfo zjj  = {CardNormalPackageType::ZhengJingJi,
                           CardPackage::CardPackage_Normal, tr("ZhengJingJi")};
    const CardInfo jjy  = {CardNormalPackageType::JiJiuYao,
                           CardPackage::CardPackage_Normal, tr("JiJiuYao")};
    const CardInfo sb   = {CardNormalPackageType::ShanBi,
                           CardPackage::CardPackage_Normal, tr("ShanBi")};

    skillHash.insert(static_cast<int>(CardNormalPackageType::KuangBao), new CsKuangBao);
    skillHash.insert(static_cast<int>(CardNormalPackageType::ZheYue), new CsZheYue);
    skillHash.insert(static_cast<int>(CardNormalPackageType::ShengMingLiZan), new CsShengMingLiZan);
    skillHash.insert(static_cast<int>(CardNormalPackageType::ChuanSong), new CsChuanSong);
    skillHash.insert(static_cast<int>(CardNormalPackageType::JinBi_2), new CsMoney(2));
    skillHash.insert(static_cast<int>(CardNormalPackageType::JinBi_3), new CsMoney(3));
    skillHash.insert(static_cast<int>(CardNormalPackageType::JinBi_4), new CsMoney(4));
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

#define BUILDEQUIP const EquipmentInfo
EquipmentPackageNormal::EquipmentPackageNormal() {
    BUILDEQUIP ajlzx = {EquipmentType::Shoe,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::AnJingLingZhiXue,
                        4, "AnJingLingZhiXue"};
    BUILDEQUIP andzd = {EquipmentType::Armor,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::ANuoDeZhiDun,
                        5, "ANuoDeZhiDun"};
    BUILDEQUIP blqzj = {EquipmentType::Omament,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::BuLanQiZhiJie,
                        4, "BuLanQiZhiJie"};
    BUILDEQUIP flksz = {EquipmentType::Weapon,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::FuLuoKenShenZhang,
                        8, "FuLuoKenShenZhang"};
    BUILDEQUIP jgb   = {EquipmentType::Weapon,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::JinGuBang,
                        7, "JinGuBang"};
    BUILDEQUIP lqddj = {EquipmentType::Omament,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::LaoQianDeDaoJu,
                        4, "LaoQianDeDaoJu"};
    BUILDEQUIP lrg   = {EquipmentType::Weapon,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::LieRiGong,
                        7, "LieRiGong"};
    BUILDEQUIP lwfz  = {EquipmentType::Weapon,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::LongWangFaZhang,
                        6, "LongWangFaZhang"};
    BUILDEQUIP msypf = {EquipmentType::Armor,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::MoShuYangDePiFeng,
                        6, "MoShuYangDePiFeng"};
    BUILDEQUIP rszf  = {EquipmentType::Weapon,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::RanShaoZhiFu,
                        6, "RanShaoZhiFu"};
    BUILDEQUIP xjlbs = {EquipmentType::Weapon,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::XueJingLingBiShou,
                        8, "XueJingLingBiShou"};
    BUILDEQUIP ysdzf = {EquipmentType::Armor,
                        EquipmentPackage::EquipmentPackage_Normal,
                        EquipNormalPackageId::YuShenDeZhuFu,
                        5, "YuShenDeZhuFu"};
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
    const heroInfo HeroPackageNormal::##Abbr = \
{ AR, MR, HP, SEX, Name }


HeroPackageNormal::HeroPackageNormal() {
    const HeroInfo msz  = {1, 4, 8,  Sexual::SexFemale,
                                  tr("MieShaZhe")};
    const HeroInfo ls   = {1, 2, 8,  Sexual::SexMale,
                                  tr("LeiShen")};
    const HeroInfo bzsn = {1, 2, 8,  Sexual::SexFemale,
                                  tr("BingZhiShengNv")};
    const HeroInfo hwz  = {1, 2, 8,  Sexual::SexFemale,
                                  tr("HuoWuZhe")};
    const HeroInfo fxz  = {1, 3, 7,  Sexual::SexFemale,
                                  tr("FengXingZhe")};
    const HeroInfo hyzq = {1, 3, 8,  Sexual::SexFemale,
                                  tr("HuanYingZhiQiang")};
    const HeroInfo lhyz = {1, 3, 7,  Sexual::SexFemale,
                                  tr("LingHunYiZhe")};
    const HeroInfo dt   = {1, 4, 8,  Sexual::SexMale,
                                  tr("DuTu")};
    const HeroInfo yy   = {1, 3, 8,  Sexual::SexMale,
                                  tr("YingYan")};
    const HeroInfo shz  = {1, 4, 8,  Sexual::SexFemale,
                                  tr("ShiHunZhe")};
    const HeroInfo ayzr = {1, 4, 7,  Sexual::SexMale,
                                  tr("AnYingZhiRen")};
    const HeroInfo rz   = {1, 4, 8,  Sexual::SexMale,
                                  tr("RenZhe")};
    const HeroInfo xzlz = {1, 4, 8,  Sexual::SexMale,
                                  tr("XueZhiLiZhua")};
    const HeroInfo qyz  = {1, 4, 8,  Sexual::SexMale,
                                  tr("QiYueZhe")};
    const HeroInfo sqs  = {1, 3, 8,  Sexual::SexFemale,
                                  tr("ShengQiShi")};
    const HeroInfo zlzj = {1, 3, 9,  Sexual::SexMale,
                                  tr("ZhanLanZhiJian")};
    const HeroInfo zkzs = {1, 3, 10, Sexual::SexMale,
                                  tr("ZhongKaiZhanShi")};
    const HeroInfo ks   = {1, 3, 9,  Sexual::SexMale,
                                  tr("KuangSha")};
    const HeroInfo ss   = {1, 3, 9,  Sexual::SexMale,
                                  tr("SiShen")};
    const HeroInfo bx   = {1, 4, 8,  Sexual::SexMale,
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

    addSkills(HeroNum::AnYingZhiRen,
              new HsGuiShou,
              new HsQianXing,
              new HsLengXue);
}

void HeroPackageNormal::addSkills(HeroNum hn, SkillBase* s1, SkillBase* s2, SkillBase* s3) {
    skillHash.insert(static_cast<int>(hn) * 3, s1);
    skillHash.insert(static_cast<int>(hn) * 3 + 1, s2);
    skillHash.insert(static_cast<int>(hn) * 3 + 2, s3);
}

QList<SkillBase*> HeroPackageNormal::getSkillByHeroNum(int i) {
    QList<SkillBase*> result;
    result.append(skillHash[3 * i]);
    result.append(skillHash[3 * i + 1]);
    result.append(skillHash[3 * i + 2]);
    return result;
}


CsKuangBao::CsKuangBao()
    : AttackBuffSkill(AttackBuffEffect::AttackBuffAddDamage, 1, 0x3F) {
    setObjectName("KuangBao");
}

void CsKuangBao::skillAct(SkillPara sp) {
    Q_UNUSED(sp);
}

void CsKuangBao::skillClicked(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->aa->addBouns(buffEffect());
}

CsZheYue::CsZheYue()
    : RangeSkill(MapRangeType::Round, 2) {
    setObjectName("ZheYue");
}

void CsZheYue::skillRange(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    QList<QPoint> lp = sp.ec->getPointInRange(hi->point(),
                                              MapRangeType::Round, 2);
    sp.ec->showSkillRange(lp);
    to = sp.ec->gmeOnPoint(sp.ec->askForSelectPoint());
}

void CsZheYue::skillAct(SkillPara sp) {
    sp.ec->setHeroPosition(static_cast<HeroItem*>(sp.from),
                           static_cast<GameMapElement*>(to)->point());
}

CsChuanSong::CsChuanSong()
    : RangeSkill(MapRangeType::Round, 1) {
    setObjectName("ChuanSong");
}

void CsChuanSong::skillAct(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    sp.ec->setHeroPosition(hi, static_cast<GameMapElement*>(to)->point());
    // hi->removeCard()
}

void CsChuanSong::skillRange(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    QList<HeroItem*> friendHeros = sp.ec->getHerosOfCamp(hi->camp());
    QList<QPoint> lp;
    foreach(HeroItem* hi, friendHeros) {
        lp += sp.ec->getPointInRange(hi->point(), MapRangeType::Round, 1);
    }
    sp.ec->showSkillRange(lp);
    QPoint qp = sp.ec->askForSelectPoint();
    if (sp.ec->hasHeroOnPoint(qp)) {
        return;     // cannot chuansong to point which has a hero on it
    }
    to = sp.ec->gmeOnPoint(qp);
}

CsNengLiangXianJing::CsNengLiangXianJing(QString path, int width)
    : MapMarkSkill(new MapMark(path, width), -1) {
}


CsShengMingLiZan::CsShengMingLiZan()
    : RangeSkill(MapRangeType::Round, 1) {
    setObjectName("ShengMingLiZan");
}

void CsShengMingLiZan::skillAct(SkillPara sp) {
    QList<QPoint> lp = sp.ec->getPointInRange(
                static_cast<HeroItem*>(sp.from)->point(),
                MapRangeType::Round, 1);
    foreach(QPoint p, lp) {
        HeroItem* hi = sp.ec->hasHeroOnPoint(p);
        if (hi)
            hi->addHealth(1);
    }
}



HsGuiShou::HsGuiShou()
    : AttackBuffSkill(AttackBuffEffect::AttackBuffAddDamage, 0, 0x3F, 0, 0) {
    setObjectName("GuiShou");
}

void HsGuiShou::skillAct(SkillPara sp) {
    Q_UNUSED(sp);
}

void HsGuiShou::skillClicked(SkillPara sp) {
    HeroItem* from = static_cast<HeroItem*>(sp.from);
    from->aa->addBouns(buffEffect());
}


HsQianXing::HsQianXing()
    : AttackBuffSkill(AttackBuffEffect::AttackBuffAddDamage, 1, 0x3F, 0, 2) {
    setObjectName("QianXing");
}

void HsQianXing::skillAct(SkillPara sp) {
    Q_UNUSED(sp);
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->addState(HeroState::PhysicalImmune, 1);
    // get physical immune
}

void HsQianXing::skillClicked(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->aa->addBouns(buffEffect());
    this->addCoolDown(this->cdMax());
}

HsLengXue::HsLengXue()
    : AttackBuffSkill(AttackBuffEffect::AttackBuffMustHit, 0, 0x3F, 0, 2) {
    setObjectName("LengXue");
}

void HsLengXue::skillAct(SkillPara sp) {
    HeroItem* fr = static_cast<HeroItem*>(sp.from);
    HeroItem* to = static_cast<HeroItem*>(sp.from);
    to->addHealth(- fr->aa->attack(),
                  DamageType::Magical);  // change to suffer magic
}

void HsLengXue::skillClicked(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*>(sp.from);
    hi->aa->addBouns(buffEffect());
    this->addCoolDown(this->cdMax());
}

HsBaoNu::HsBaoNu()
    : AttackBuffSkill(AttackBuffEffect::AttackBuffMoreAttack, 2, 0x3F, 0, 2) {
    setObjectName("BaoNu");
}

void HsBaoNu::skillAct(SkillPara sp) {
    Q_UNUSED(sp);
}

void HsBaoNu::skillClicked(SkillPara sp) {
    HeroItem* hi = static_cast<HeroItem*> (sp.from);
    hi->aa->addBouns(buffEffect());
    this->addCoolDown(this->cdMax());
}
