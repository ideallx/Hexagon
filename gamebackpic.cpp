#include "gamebackpic.h"

gameBackPic::gameBackPic(QPixmap picture) :
    QPixmap(picture)
{

}

QPixmap gameBackPic::getPixmap(void)
{
    return backgroundPicture;
}

QPointF gameBackPic::getBeginPostion(void)
{
    return QPointF(50.0, 50.0);
}
