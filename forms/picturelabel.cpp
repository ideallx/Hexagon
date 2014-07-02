#include <QDebug>
#include "picturelabel.h"

PictureLabel::PictureLabel(QWidget *parent) :
    QLabel(parent)
{
}

void PictureLabel::mouseReleaseEvent(QMouseEvent *ev) {
    Q_UNUSED(ev);
    emit clicked();
}
