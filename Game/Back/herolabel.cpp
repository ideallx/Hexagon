#include "herolabel.h"
#include <QDebug>

heroLabel::heroLabel(QWidget *parent, Qt::WindowFlags f) :
    QLabel(parent, f)
{
    setMouseTracking(true);
    heroNum = 0;
}

void heroLabel::setPixmap(const QPixmap &qp)
{
    QLabel::setPixmap(qp);
    this->setFixedSize(qp.size());
}

void heroLabel::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug()<<"mouse moved";
}

void heroLabel::mouseDoubleClickEvent(QMouseEvent *ev)
{
    qDebug()<<"double clicked";
    emit heroChosen(heroNum);
}
