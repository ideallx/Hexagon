#ifndef NORMALPACKAGE_H
#define NORMALPACKAGE_H

#include <QObject>
#include "skillcenter.h"
#include "enums.h"
#include "cardengine.h"
#include "heroengine.h"

class CardPackageNormal : public AbstractCardPackage {
 public:
    CardPackageNormal();
    int cardNumInPackage() { return 60; }
    int cardTypeInPackage() { return 17;}
    enum Card_Package_t cardPackageIdicator() {
        return CardPackage_Normal;
    }
    struct CardInfo getCardInfo(int n) {
        return cil[n];
    }
    QList<struct CardInfo> getAllCards() const {
        return cil;
    }

    SkillBase* getSkillByCardTypeId(int i) { return skillHash[i]; }

 private:
    QHash<int, SkillBase*>skillHash;
    QString path;
    QList<struct CardInfo> cil;
};

class NoSkill : public SkillBase {
    void skillFlow(struct SkillPara sp) { Q_UNUSED(sp);}
    enum TriggerTime_t triggerTime() { return TriggerNever; }
    bool isWorkNow() { return false; }
};


class CsKuangBao : public AttackBuffSkill {
 public:
    CsKuangBao();
    void skillAct(struct SkillPara sp);
    void skillPrepare(SkillPara sp);
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
    void skillPrepare(SkillPara sp);
    virtual enum SkillType_t type() { return SkillPositive; }
};


#endif // NORMALPACKAGE_H
