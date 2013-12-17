#include "herolabel.h"
#include <QDebug>

HeroLabel::HeroLabel(QWidget *parent)
    : QToolButton(parent) {
    theHeroNum = HeroNum::MieShaZhe;
}

void HeroLabel::setPixmap(const QPixmap &qp) {
    QToolButton::setIcon(
                QIcon(qp.scaledToWidth(pixWidth, Qt::SmoothTransformation)));
    this->setIconSize(QSize(pixWidth, pixWidth*1.4625));
}
