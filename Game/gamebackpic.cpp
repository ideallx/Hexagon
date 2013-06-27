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

int gameBackPic::getLineLength()
{
    return 50;
}

int gameBackPic::getWidthCount()
{
    return 10;
}

int gameBackPic::getHeightCount()
{
    return 10;
}
