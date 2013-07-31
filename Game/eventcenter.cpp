#include "eventcenter.h"

eventCenter::eventCenter(backScene* scene, gameMenu* menu, backview* view)
{
    connect(scene, SIGNAL(localHeroClicked(QPointF)), menu, SLOT(showMenu(QPointF)));
    connect(scene, SIGNAL(heroClicked(QPoint)), menu, SLOT(hideAllMenu()));
    connect(scene, SIGNAL(mapElementClicked(QPoint)), menu, SLOT(hideAllMenu()));
    connect(scene, SIGNAL(mapElementClicked(QPoint)), scene, SLOT(clearSphere()));
    connect(scene, SIGNAL(viewSizeChanged(QSize)), menu, SLOT(reSetInterface(QSize)));

    connect(menu, SIGNAL(moveClicked()), scene, SLOT(clearSphere()));
    connect(menu, SIGNAL(moveClicked()), scene, SLOT(showMoveSphere()));
    connect(menu, SIGNAL(attackClicked()), scene, SLOT(clearSphere()));
    connect(menu, SIGNAL(attackClicked()), scene, SLOT(showAttackSphere()));
}
