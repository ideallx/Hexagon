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
    virtual CardPackage cardPackageIdicator() = 0;
    virtual CardInfo getCardInfo(int n) = 0;
    virtual QList<CardInfo> getAllCards() const = 0;
    virtual SkillBase* getSkillByCardTypeId(int i) = 0;
};

class CardEngine : public QObject {
 public:
    explicit CardEngine(GameBackInfo *gbi);
    QList<HandCard*> generateHandCards();
    void addPackage(AbstractCardPackage* acp);
    void registerSkill(AbstractCardPackage* acp);

 private:
    HandCard* createCard(CardInfo ci);
    int cardAmount;
    int cardsId;
    QString path;
    int skillsNum;
    QList<AbstractCardPackage*> cpl;
    QHash<int, SkillBase*>skills;

 friend class VvTestTest;
};

#endif  // GAME_ITEMS_CARD_CARDENGINE_H_
