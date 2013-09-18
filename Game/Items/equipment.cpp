#include "equipment.h"

Equipment::Equipment(struct EquipmentInfo ei)
    : theInfo(ei) {
}

void EquipmentShop::soldEquipment(Equipment* eq) {
    if (!theLists[eq->type()].removeOne(eq))
        qDebug() << "Delete Equipment Error";
}

void EquipmentShop::recoverEquipment(Equipment* eq) {
    if (theLists[eq->type()].contains(eq)) {
        qDebug() << "Equipment Aready In Shop";
        return;
    }
    theLists[eq->type()].append(eq);
}
