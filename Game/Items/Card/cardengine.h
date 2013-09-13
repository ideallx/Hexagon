#ifndef GAME_ITEMS_CARD_CARDENGINE_H_
#define GAME_ITEMS_CARD_CARDENGINE_H_

#include <QList>
#include <QString>
#include <QObject>
#include <QHash>

#include "enums.h"
#include "skillcenter.h"

class HandCard;
class GameBackInfo;


class AbstractCardPackage : public QObject {
 public:
    virtual int cardNumInPackage() = 0;
    virtual int cardTypeInPackage() = 0;
    virtual enum Card_Package_t cardPackageIdicator() = 0;
    virtual struct CardInfo getCardInfo(int n) = 0;
    virtual QList<struct CardInfo> getAllCards() const = 0;
    virtual SkillBase* getSkillByCardTypeId(int i) = 0;
};

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

class CardEngine : public QObject {
 public:
    explicit CardEngine(GameBackInfo *gbi);
    QList<HandCard*> generateHandCards();
    void addPackage(AbstractCardPackage* acp);
    void registerSkill(AbstractCardPackage* acp);

 private:
    HandCard* createCard(struct CardInfo ci);
    int cardAmount;
    int cardsId;
    QString path;
    int skillsNum;
    QList<AbstractCardPackage*> cpl;
    QHash<int, SkillBase*>skills;
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

#endif  // GAME_ITEMS_CARD_CARDENGINE_H_
