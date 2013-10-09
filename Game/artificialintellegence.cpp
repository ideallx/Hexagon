#include "artificialintellegence.h"
#include "heroitem.h"
#include "carditem.h"

ArtificialIntellegence::ArtificialIntellegence(HeroItem *hi)
    : AiHero (hi) {
}

HandCard* ArtificialIntellegence::useCard(enum Card_Normal_Package_Type_t cnpt) {
    foreach(HandCard* hc, AiHero->cards()) {
        if (hc->cardType() == cnpt)
            return hc;
    }
    return NULL;
}

QList<HandCard*> ArtificialIntellegence::useCard(int n) {
    if (AiHero->cards().size() <= n) {
        return AiHero->cards();
    } else {
        QList<HandCard*> result;
        while (n != 0) {
            result.append(AiHero->cards()[n-1]);
        }
        return result;
    }
}
