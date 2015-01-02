#include <QDebug>
#include "cardengine.h"
#include "carditem.h"
#include "backinfo.h"
#include "heroitem.h"

CardEngine::CardEngine(GameBackInfo *gbi)
    : cardAmount(0)
	, cardsId(0)
	, path(gbi->getConfigDir() + "cards/")
	, skillsNum(0) {
}

bool CardEngine::generateHandCards(QList<HandCard*>& result) {
    for (int i = 0; i < cpl.size(); i++) {
        QList<CardInfo> hcl = cpl[i]->getAllCards();
        for (int j = 0; j < hcl.size(); j++) {
            result.append(createCard(hcl[j]));
        }
    }
	return true;
}

HandCard* CardEngine::createCard(CardInfo ci) {
    return new HandCard(ci.cardType, cardsId++,
                        QString("%1%2.jpg").arg(path).arg(ci.name),
                        skills[static_cast<int> (ci.cardType)]);
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
