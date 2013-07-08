#ifndef ABSTRACTHERO_H
#define ABSTRACTHERO_H

#include <QtWidgets>

class midClass : public QObject
{

};

class abstractHero
{
public:
    abstractHero();

protected:
    virtual char getSexual() const = 0;
    virtual char getMoveSphere() const = 0;
    virtual QString getPlayerName() const = 0;
    virtual QString getHeroName() const = 0;

private:
    void variableInitial();



};

#endif // ABSTRACTHERO_H
