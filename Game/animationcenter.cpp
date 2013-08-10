#include "animationcenter.h"

animationCenter::animationCenter()
{
    theGia = new QGraphicsItemAnimation();
    theGiaTimer = new QTimeLine(500);
}
