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
    inline int price() { return theInfo.price; }
    inline QString name() { return theInfo.name; }
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

    inline const QList<QList<Equipment*> > allEquips() { return theLists; }
    inline const QList<Equipment*> weapons() { return theWeapons; }
    inline const QList<Equipment*> armors() { return theArmors; }
    inline const QList<Equipment*> omaments() { return theOmaments; }
    inline const QList<Equipment*> shoes() { return theShoes; }

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
