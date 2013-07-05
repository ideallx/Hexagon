#ifndef ABSTRACTHERO_H
#define ABSTRACTHERO_H

#include <QString>

class abstractHero
{
public:
    abstractHero();

protected:
    virtual char getSexual() const = 0;
    virtual char getMoveSphere() const = 0;
    virtual QString getPlayerName() const = 0;
    virtual QString getHeroName() const = 0;


};

#endif // ABSTRACTHERO_H
