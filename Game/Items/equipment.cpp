#include <QBrush>
#include "equipment.h"

Equipment::Equipment(EquipmentInfo ei)
    : theInfo(ei) {
}

void Equipment::setPixmap(QString s) {
    pix = QPixmap(s).scaledToWidth(200, Qt::SmoothTransformation);
    setBrush(QBrush(pix));
}

EquipmentShop::EquipmentShop(QString path)
    : path(path) {
    QList<Equipment*> epl;
    theLists.append(epl);
    theLists.append(epl);
    theLists.append(epl);
    theLists.append(epl);
}

void EquipmentShop::soldEquipment(Equipment* eq) {
    if (!theLists[static_cast<int>(eq->type())].removeOne(eq))
        qDebug() << "Delete Equipment Error";
}

void EquipmentShop::recoverEquipment(Equipment* eq) {
    if (theLists[static_cast<int>(eq->type())].contains(eq)) {
        qDebug() << "Equipment Aready In Shop";
        return;
    }
    theLists[static_cast<int>(eq->type())].append(eq);
}

void EquipmentShop::addEquipmentPackage(AbstractEquipmentPackage* aep) {
    epl.append(aep);
}

Equipment *EquipmentShop::createEquipment(EquipmentInfo ei) {
    Equipment* eq = new Equipment(ei);
    theLists[static_cast<int>(eq->type())].append(eq);
    return eq;
}

QList<QList<Equipment*> > EquipmentShop::generateEquipment() {
    foreach(AbstractEquipmentPackage *aep, epl) {
        foreach(EquipmentInfo ei, aep->getAllEquipments()) {
            createEquipment(ei);
        }
    }
    return theLists;
}
