#ifndef ANIMATIONCENTER_H
#define ANIMATIONCENTER_H

#include <QGraphicsItemAnimation>
#include <QTimeLine>

class animationCenter
{
public:
    animationCenter();

    QGraphicsItemAnimation* gia() { return theGia; }
    QTimeLine* giaTimer() { return theGiaTimer; }


private:
    QGraphicsItemAnimation* theGia;
    QTimeLine* theGiaTimer;
};

#endif // ANIMATIONCENTER_H
