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
class MapMark;


class AbstractCardPackage : public QObject {
 public:
    virtual int cardNumInPackage() = 0;
    virtual int cardTypeInPackage() = 0;
    virtual enum Card_Package_t cardPackageIdicator() = 0;
    virtual struct CardInfo getCardInfo(int n) = 0;
    virtual QList<struct CardInfo> getAllCards() const = 0;
    virtual SkillBase* getSkillByCardTypeId(int i) = 0;
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

#endif  // GAME_ITEMS_CARD_CARDENGINE_H_
