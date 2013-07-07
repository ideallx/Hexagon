#ifndef ABSTRACTHERO_H
#define ABSTRACTHERO_H

#include <QtWidgets>

class abstractHero
{
public:
    abstractHero();

protected:
    virtual char getSexual() const = 0;
    virtual char getMoveSphere() const = 0;
    virtual QString getPlayerName() const = 0;
    virtual QString getHeroName() const = 0;

    QList<QPushButton*> menuList;
    void showHideAllList(QList<QPushButton*>, char, QPointF pos= QPointF());

private:
    void variableInitial();



};

#endif // ABSTRACTHERO_H
