#ifndef MOVEABILITY_H
#define MOVEABILITY_H

class MoveAbility
{
 public:
    MoveAbility(int range = 3);
    inline void setRange(int n) { theRange = n; }
    inline int moveRange() { return theRange; }
    inline int remainingTimes() { return moveTime; }
    inline void restore() { moveTime = 1; }

 private:
    int theRange;
    bool ignoreHeroWhenMove;
    int moveTime;
};

#endif // MOVEABILITY_H
