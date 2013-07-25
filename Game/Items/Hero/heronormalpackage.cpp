#include "heronormalpackage.h"

void heroMieShaZhe::initial()
{
    setHeroProperty(heroItem::sex_female, 1, 4, 7);
    setToolTip(tr("Slay Assassin"));
    setHeroName(tr("Slay Assassin"));
}

void heroLeiShen::initial()
{
    setHeroProperty(heroItem::sex_male, 1, 2, 8);
    setToolTip(tr("Thunder King"));
    setHeroName(tr("Thunder King"));
}
