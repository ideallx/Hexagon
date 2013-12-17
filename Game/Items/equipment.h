#ifndef GAME_ITEMS_EQUIPMENT_H_
#define GAME_ITEMS_EQUIPMENT_H_

#include <QString>
#include <QList>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsRectItem>
#include "enums.h"


class Equipment : public QGraphicsRectItem {
 public:
    explicit Equipment(EquipmentInfo ei);
    inline EquipmentType type() { return theInfo.type; }
    int price() { return theInfo.price; }
    QString name() { return theInfo.name; }
    void setPixmap(QString s);
    QPixmap getPixmap() { return pix; }

 private:
    QPixmap pix;
    EquipmentInfo theInfo;
};

class AbstractEquipmentPackage : public QObject {
 public:
    virtual int equipmentNumInPackage() = 0;
    virtual EquipmentPackage equipmentPackageIdicator() = 0;
    virtual EquipmentInfo getEquipmentInfo(int n) = 0;
    virtual QList<EquipmentInfo> getAllEquipments() const = 0;
};


class EquipmentShop {
 public:
    explicit EquipmentShop(QString path);
    void soldEquipment(Equipment* eq);
    void recoverEquipment(Equipment* eq);
    void addEquipmentPackage(AbstractEquipmentPackage* aep);
    Equipment* createEquipment(EquipmentInfo ei);
    QList<QList<Equipment *> > generateEquipment();

    const QList<QList<Equipment*> > allEquips() { return theLists; }
    const QList<Equipment*> weapons() { return theWeapons; }
    const QList<Equipment*> armors() { return theArmors; }
    const QList<Equipment*> omaments() { return theOmaments; }
    const QList<Equipment*> shoes() { return theShoes; }

 private:
    QString path;
    QList<QList<Equipment*> >theLists;
    QList<Equipment*> theWeapons;
    QList<Equipment*> theArmors;
    QList<Equipment*> theOmaments;
    QList<Equipment*> theShoes;
    QList<AbstractEquipmentPackage*> epl;
};

#endif  // GAME_ITEMS_EQUIPMENT_H_
