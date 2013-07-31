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
    eventCenter(backScene* scene, gameMenu* menu, backview* view);
};

#endif // EVENTCENTER_H
