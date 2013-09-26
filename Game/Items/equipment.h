#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QList>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsRectItem>
#include "enums.h"


class Equipment : public QGraphicsRectItem {
 public:
    Equipment(struct EquipmentInfo ei);
    int type() { return theInfo.type; }
    int price() { return theInfo.price; }
    QString name() { return theInfo.name; }
    void setPixmap(QString s);
    QPixmap getPixmap() { return pix; }

 private:
    QPixmap pix;
    struct EquipmentInfo theInfo;
};

class AbstractEquipmentPackage : public QObject {
 public:
    virtual int equipmentNumInPackage() = 0;
    virtual enum EquipmentPackage_t equipmentPackageIdicator() = 0;
    virtual struct EquipmentInfo getEquipmentInfo(int n) = 0;
    virtual QList<struct EquipmentInfo> getAllEquipments() const = 0;
    virtual Equipment* getEquipmentByEquipmentType(int i) = 0;
};


class EquipmentShop {
 public:
    EquipmentShop();
    void soldEquipment(Equipment* eq);
    void recoverEquipment(Equipment* eq);
    void addEquipmentPackage(AbstractEquipmentPackage* aep);

    const QList<Equipment*> weapons() { return theWeapons; }
    const QList<Equipment*> armors() { return theArmors; }
    const QList<Equipment*> omaments() { return theOmaments; }
    const QList<Equipment*> shoes() { return theShoes; }

 private:
    QList<QList<Equipment*> >theLists;
    QList<Equipment*> theWeapons;
    QList<Equipment*> theArmors;
    QList<Equipment*> theOmaments;
    QList<Equipment*> theShoes;

};

#endif // EQUIPMENT_H
