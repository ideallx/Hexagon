#include "carditem.h"

Q_DECLARE_METATYPE(HandCard)

HandCard::HandCard(CardNormalPackageType t, int id, QString s, SkillBase* sk)
    : typeCard(t),
      theId(id),
      pixmapPath(QPixmap(s)),
      theSkill(sk) {
    setRect(0, 0, 137, 200);
    setBrush(pixmapPath.scaledToHeight(200, Qt::SmoothTransformation));
}

HandCard::HandCard()
    : typeCard(CardNormalPackageType::None),
      theId(-1),
      pixmapPath(""),
      theSkill(NULL) {
}

HandCard::~HandCard() {

}

HandCard::HandCard(const HandCard& that) {
    this->typeCard = that.typeCard;
    this->theId = that.theId;
    this->pixmapPath = that.pixmapPath;
    this->theSkill = that.theSkill;
}

QRectF HandCard::boundingRect() const {
    return rect();
}

void HandCard::paint(QPainter* p,
                     const QStyleOptionGraphicsItem* i,
                     QWidget* w) {
    Q_UNUSED(i);
    Q_UNUSED(w);
    p->setBrush(brush());
    p->drawRect(rect());
}
