#include "herolabel.h"
#include <QDebug>

heroLabel::heroLabel(QWidget *parent) :
    QToolButton(parent)
{
    theHeroNum = 0;
}

void heroLabel::setPixmap(const QPixmap &qp)
{
    QToolButton::setIcon(QIcon(qp));
    this->setIconSize(qp.size());
}
