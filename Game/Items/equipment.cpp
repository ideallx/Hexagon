#include <QBrush>
#include "equipment.h"

Equipment::Equipment(struct EquipmentInfo ei)
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

void EquipmentShop::addEquipmentPackage(AbstractEquipmentPackage* aep) {
    epl.append(aep);
}

Equipment *EquipmentShop::createEquipment(struct EquipmentInfo ei) {
    Equipment* ep = new Equipment(ei);
    theLists[ep->type()].append(ep);
    return ep;
}

QList<QList<Equipment*> > EquipmentShop::generateEquipment() {
    foreach(AbstractEquipmentPackage *aep, epl) {
        foreach(struct EquipmentInfo ei, aep->getAllEquipments()) {
            createEquipment(ei);
        }
    }
    return theLists;
}
