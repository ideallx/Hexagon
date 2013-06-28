#include "gamebackpic.h"

gameBackInfo::gameBackInfo(QPixmap picture, QString configFilePath) :
    QPixmap(picture)
{
    variableInitial(configFilePath);
}

void gameBackInfo::variableInitial(QString configFilePath)
{
    setMapElement();
}

QPixmap gameBackInfo::getPixmap(void)
{
    return backgroundPicture;
}

QPointF gameBackInfo::getBeginPosition(void)
{
    return QPointF(50.0, 50.0);
}

int gameBackInfo::getLineLength()
{
    return 50;
}

int gameBackInfo::getWidthCount()
{
    return 8;
}

int gameBackInfo::getHeightCount()
{
    return 8;
}

void gameBackInfo::setMapElement()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            mapElement.append(j);
        }
    }
}

QVector<int> gameBackInfo::getMapElement()
{
    return mapElement;
}
