#ifndef GAME_ITEMS_CARD_CARDITEM_H_
#define GAME_ITEMS_CARD_CARDITEM_H_

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include "enums.h"

class SkillBase;

class HandCard : public QGraphicsRectItem {
 public:
    HandCard(CardNormalPackageType type, int id, QString pixmapPath, SkillBase* skill);
    QPixmap pixmap() { return pixmapPath; }
    void setPixmap(QString s) { pixmapPath = s; }
    void setId(int n) { theId = n; }
    int type() { return theId; }
    CardNormalPackageType cardType() { return typeCard; }
    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    SkillBase* skill() { return theSkill; }

 private:
    CardNormalPackageType typeCard;
    int theId;
    QPixmap pixmapPath;
    SkillBase* theSkill;
};
#endif  // GAME_ITEMS_CARD_CARDITEM_H_
