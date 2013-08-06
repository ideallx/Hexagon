#ifndef EVENTCENTER_H
#define EVENTCENTER_H

#include <QtWidgets>

#include "itemcollector.h"
#include "backscene.h"
#include "menu.h"
#include "backview.h"

class eventCenter : public QObject
{
    Q_OBJECT
public:
    eventCenter(backScene* scene, gameMenu* menu);


private:
    backScene *scene;
    gameMenu* menu;
    itemCollector* ic;

public slots:
    void heroChosen(heroItem*);
    void getCard(int num = 1);

};

#endif // EVENTCENTER_H
