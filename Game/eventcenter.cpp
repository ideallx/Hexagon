#include "eventcenter.h"

eventCenter::eventCenter(backScene* scene, gameMenu* menu):
    scene(scene),
    menu(menu),
    ic(scene->pIc())
{
    connect(scene, SIGNAL(heroClicked(heroItem*)), this, SLOT(heroChosen(heroItem*)));
    connect(scene, SIGNAL(buildMenu(QPoint)), menu, SLOT(showMenu(QPoint)));
    connect(scene, SIGNAL(mapElementClicked(QPoint)), menu, SLOT(hideAllMenu()));
    connect(scene, SIGNAL(mapElementClicked(QPoint)), scene, SLOT(clearSphere()));
    connect(scene, SIGNAL(viewSizeChanged(QSize)), menu, SLOT(reSetInterface(QSize)));
    connect(scene, SIGNAL(listSlideAvaters(QList<QString>,QList<QString>)), menu, SLOT(listSlideHeroHead(QList<QString>,QList<QString>)));

    connect(menu, SIGNAL(moveClicked()), scene, SLOT(clearSphere()));
    connect(menu, SIGNAL(moveClicked()), scene, SLOT(showMoveSphere()));
    connect(menu, SIGNAL(attackClicked()), scene, SLOT(clearSphere()));
    connect(menu, SIGNAL(attackClicked()), scene, SLOT(showAttackSphere()));

    qDebug()<<"event center initialized";
}

void eventCenter::heroChosen(heroItem* hero)
{
    struct essenialContent ec;
    ec.mr = hero->moveSphere();
    ec.a  = hero->attack();
    ec.ar = hero->attackSphere();

    menu->setHeroHp(hero->health(), hero->maxHealth());
    menu->setHeroAvaters(hero->wholePic());
    menu->setEssenial(ec);
    menu->setHeroSkillButton(hero->skillButtons());

    hero->addCards(ic->getCard(5));
    menu->setDisplayCards(hero->cards());
}
