#ifndef PACKAGE_NORMALPACKAGE_H_
#define PACKAGE_NORMALPACKAGE_H_

#include <QObject>
#include "skillcenter.h"
#include "enums.h"
#include "cardengine.h"
#include "heroengine.h"
#include "equipment.h"

class AbstractPackage {
 public:
    AbstractPackage(AbstractCardPackage *acp,
                    AbstractEquipmentPackage *aep,
                    AbstractHeroPacakage* ahp)
        : acp(acp),
          aep(aep),
          ahp(ahp) {;}
    AbstractCardPackage* getAcp() { return acp; }
    AbstractEquipmentPackage * getAep() { return aep;}
    AbstractHeroPacakage* getAhp() { return ahp; }
 private:
    AbstractCardPackage* acp;
    AbstractEquipmentPackage *aep;
    AbstractHeroPacakage* ahp;
    // TODO(ideallx) abstractMapmarkPackage* amp;
};

class CardPackageNormal : public AbstractCardPackage {
 public:
    CardPackageNormal();
    int cardNumInPackage() { return 60; }
    int cardTypeInPackage() { return 17;}
    CardPackage cardPackageIdicator() {
        return CardPackage::CardPackage_Normal;
    }
    CardInfo getCardInfo(int n) {
        return cil[n];
    }
    QList<CardInfo> getAllCards() const {
        return cil;
    }

    SkillBase* getSkillByCardTypeId(int i) { return skillHash[i]; }

 private:
    QHash<int, SkillBase*>skillHash;
    QString path;
    QList<CardInfo> cil;
};

class EquipmentPackageNormal : public AbstractEquipmentPackage {
 public:
    EquipmentPackageNormal();
    int equipmentNumInPackage() { return 12; }
    EquipmentPackage equipmentPackageIdicator() {
        return EquipmentPackage::EquipmentPackage_Normal;
    }
    EquipmentInfo getEquipmentInfo(int n) { return eil[n];}
    QList<EquipmentInfo> getAllEquipments() const { return eil; }

 private:
    QList<EquipmentInfo> eil;
};

class NoSkill : public SkillBase {
    void skillFlow(struct SkillPara sp) { Q_UNUSED(sp);}
    TriggerTime triggerTime() { return TriggerTime::TriggerNever; }
    bool isWorkNow() { return false; }
};


class HeroPackageNormal : public AbstractHeroPacakage {
 public:
    HeroPackageNormal();
    int heroNumInPackage() { return 20; }
    HeroPackage heroPackageIndicator() { return HeroPackage::HeroPackage_Normal; }
    HeroInfo getHeroInfo(int n) { return hil[n]; }

 private:
    QList<HeroInfo> hil;
};




class CsKuangBao : public AttackBuffSkill {
 public:
    CsKuangBao();
    void skillAct(struct SkillPara sp);
    void skillClicked(SkillPara sp);
};

class CsZheYue : public RangeSkill {
 public:
    CsZheYue();
    void skillAct(struct SkillPara sp);
};

class CsShengMingLiZan : public RangeSkill {
 public:
    CsShengMingLiZan();
    void skillAct(SkillPara sp);
};

class CsChuanSong : public RangeSkill {
 public:
    CsChuanSong();
    void skillRange(SkillPara sp);
    void skillAct(SkillPara sp);
};

class CsNengLiangXianJing : public MapMarkSkill {
 public:
    CsNengLiangXianJing(QString path, int width);
};

class HsGuiShou : public AttackBuffSkill {
 public:
    HsGuiShou();
    void skillAct(struct SkillPara sp);
    void skillClicked(SkillPara sp);
    virtual SkillType type() { return SkillType::SkillPositive; }
};

class HsQianXing : public AttackBuffSkill {
 public:
    HsQianXing();
    void skillAct(struct SkillPara sp);
    void skillClicked(SkillPara sp);
};

class HsLengXue : public AttackBuffSkill {
 public:
    HsLengXue();
    void skillAct(struct SkillPara sp);
    void skillClicked(SkillPara sp);
};

class HsBaoNu : public AttackBuffSkill {
 public:
    HsBaoNu();
    void skillAct(struct SkillPara sp);
    void skillClicked(SkillPara sp);
};

#endif  // PACKAGE_NORMALPACKAGE_H_
