#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QList>
#include <QDebug>
#include "enums.h"

class Equipment {
 public:
    Equipment(struct EquipmentInfo ei);
    enum EquipmentType_t type() { return theInfo.type; }
    int price() { return theInfo.price; }
    QString path() { return theInfo.path; }\
    QString name() { return theInfo.name; }

 private:
    struct EquipmentInfo theInfo;
};

class AbstractEquipmentPackage : public QObject {
 public:
    virtual int equipmentNumInPackage() = 0;
    virtual enum Card_Package_t cardPackageIdicator() = 0;
    virtual struct CardInfo getEquipmentInfo(int n) = 0;
    virtual QList<struct CardInfo> getAllEquipments() const = 0;
    virtual Equipment* getEquipmentByEquipmentType(int i) = 0;
};

class EquipmentShop {
 public:
    EquipmentShop();
    void soldEquipment(Equipment* eq);
    void recoverEquipment(Equipment* eq);

 private:
    QList<QList<Equipment*> >theLists;
    QList<Equipment*> theWeapons;
    QList<Equipment*> theArmors;
    QList<Equipment*> theOmaments;
    QList<Equipment*> theShoes;

};

#endif // EQUIPMENT_H
