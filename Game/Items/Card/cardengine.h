#ifndef GAME_ITEMS_CARD_CARDENGINE_H_
#define GAME_ITEMS_CARD_CARDENGINE_H_

#include <QList>
#include <QString>
#include <QObject>
#include "enums.h"

class HandCard;
class GameBackInfo;

struct CardInfo {
    int cartType;
    QString name;
};

class AbstractCardPackage : public QObject {
 public:
    virtual int cardNumInPackage() = 0;
    virtual enum Card_Package_t cardPackageIdicator() = 0;
    virtual struct CardInfo getCardInfo(int n) = 0;
    virtual QList<struct CardInfo> getAllCards() const = 0;
};

class CardPackageNormal : public AbstractCardPackage {
 public:
    CardPackageNormal();
    int cardNumInPackage() { return 60; }
    enum Card_Package_t cardPackageIdicator() {
        return CardPackage_Normal;
    }
    struct CardInfo getCardInfo(int n) {
        return cil[n];
    }
    QList<struct CardInfo> getAllCards() const {
        return cil;
    }

 private:
    QString path;
    QList<struct CardInfo> cil;
};

class CardEngine : public QObject {
 public:
    explicit CardEngine(GameBackInfo *gbi);
    QList<HandCard*> generateHandCards();
    QList<HandCard*> backCard(int num);
    void addPackage(AbstractCardPackage* acp);

 private:
    HandCard* createCard(struct CardInfo ci);
    int cardAmount;
    QString path;
    QList<AbstractCardPackage*> cpl;
};

#endif  // GAME_ITEMS_CARD_CARDENGINE_H_
