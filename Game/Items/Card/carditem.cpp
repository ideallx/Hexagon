#include "carditem.h"

HandCard::HandCard(int t, int id, QString s, SkillBase* sk)
    : type(t),
      theId(id),
      pixmapPath(QPixmap(s)),
      theSkill(sk) {
    setRect(0, 0, 137, 200);
    setBrush(pixmapPath.scaledToHeight(200, Qt::SmoothTransformation));
}

QRectF HandCard::boundingRect() const {
    return rect();
}

void HandCard::paint(QPainter* p,
                     const QStyleOptionGraphicsItem* i,
                     QWidget* w) {
    p->setBrush(brush());
    p->drawRect(rect());
}
