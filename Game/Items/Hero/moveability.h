#ifndef MOVEABILITY_H
#define MOVEABILITY_H

class MoveAbility
{
 public:
    MoveAbility(int range = 3);
    inline void setRange(int n) { theRange = n; }
    inline int moveRange() { return theRange; }

 private:
    int theRange;
    bool ignoreHeroWhenMove;
};

#endif // MOVEABILITY_H
