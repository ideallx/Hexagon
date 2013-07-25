#include "heroengine.h"

heroItem* createHero(enum heroNum_t hero)
{
    switch(hero)
    {
    case heroFactory::MieShaZhe:
        return new heroMieShaZhe();

    case heroFactory::LeiShen:
        return new heroLeiShen();
    }
    return NULL;
}
