#include "herolabel.h"
#include <QDebug>

heroLabel::heroLabel(QWidget *parent) :
    QToolButton(parent)
{
    theHeroNum = 0;
}

void heroLabel::setPixmap(const QPixmap &qp)
{
    QToolButton::setIcon(QIcon(qp.scaledToWidth(pixWidth, Qt::SmoothTransformation)));
    this->setIconSize(QSize(pixWidth, pixWidth*1.4625));
}
