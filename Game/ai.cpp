#include "ai.h"
#include "heroitem.h"
#include "carditem.h"

AI::AI(HeroItem *hi)
    : AiHero (hi),
      targetEnemyHero(NULL) {
}

HandCard* AI::useCard(CardNormalPackageType cnpt) {
    foreach(HandCard* hc, AiHero->cards()) {
        if (hc->cardType() == cnpt)
            return hc;
    }
    return NULL;
}

QList<HandCard*> AI::useCard(int n) {
    if (AiHero->cards().size() <= n) {
        return AiHero->cards();
    } else {
        QList<HandCard*> result;
        while (n != 0) {
            result.append(AiHero->cards()[n-1]);
            n--;
        }
        return result;
    }
}
