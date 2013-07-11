#ifndef COMMONVARIABLE_H
#define COMMONVARIABLE_H

#include "game/gamemenu.h"
#include "game/gamebackinfo.h"

class globol
{
public:
    static gameMenu* menu;
    static int i;
    static gameBackInfo *gbi;
    static QLabel *statusLabel;
};

#endif // COMMONVARIABLE_H
