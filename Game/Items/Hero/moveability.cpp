#include "moveability.h"

MoveAbility::MoveAbility(int range)
    : theRange(range),
      ignoreHeroWhenMove(false),
      moveTime(1) {
}
