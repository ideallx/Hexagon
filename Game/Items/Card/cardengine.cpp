#include <QDebug>
#include "cardengine.h"
#include "carditem.h"
#include "backinfo.h"
#include "heroitem.h"

CardEngine::CardEngine(GameBackInfo *gbi)
    : cardAmount(0),
      cardsId(0),
      path(gbi->getConfigDir() + "cards/"),
      skillsNum(0) {
}

QList<HandCard*> CardEngine::generateHandCards() {
    QList<HandCard*> result;
    for (int i = 0; i < cpl.size(); i++) {
        QList<struct CardInfo> hcl = cpl[i]->getAllCards();
        for (int j = 0; j < hcl.size(); j++) {
            result.append(createCard(hcl[j]));
        }
    }
    return result;
}

HandCard* CardEngine::createCard(struct CardInfo ci) {
    return new HandCard(ci.cardType, cardsId++, path+ci.name+".jpg",
                        skills[ci.cardType]);
}

void CardEngine::addPackage(AbstractCardPackage* acp) {
    cpl.append(acp);
    cardAmount += acp->cardNumInPackage();
    registerSkill(acp);
}

void CardEngine::registerSkill(AbstractCardPackage* acp) {
    for (int i = 0; i < acp->cardTypeInPackage(); i++) {
        skills.insert(skillsNum+i, acp->getSkillByCardTypeId(i));
    }
}
