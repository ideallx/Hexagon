#include "gamebackpic.h"

gameBackInfo::gameBackInfo(QPixmap picture, QString configFilePath) :
    QPixmap(picture)
{
    variableInitial(configFilePath);
}

void gameBackInfo::variableInitial(QString configFilePath)
{
    QFile file(configFilePath);
    isLoadingCorrectly = true;

    try
    {
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            throw QString("cant open file %1").arg(configFilePath);
        }

        QXmlStreamReader xml(file.readAll());
        if(xml.readNextStartElement())
        {
            if(xml.name() == "skin")
            {
                widthCount = xml.attributes().value("widthCount").toString().toInt();
                heightCount = xml.attributes().value("heightCount").toString().toInt();
                lineLength = xml.attributes().value("lineLength").toString().toInt();

                QStringList temp = xml.attributes().value("beginPosition").toString().split(", ");
                beginPosition = QPointF(temp[0].toDouble(), temp[1].toDouble());

                temp = xml.attributes().value("mapElement").toString().simplified().split(", ");
                for(int i=0; i<heightCount; i++)
                {
                    if(temp[i].length() != widthCount)
                    {
                        throw QString("wrong map element");
                    }
                    for(int j=0; j<widthCount; j++)
                    {
                        mapElement.append(temp[i][j].toLatin1());
                    }
                }
            }
        }
    }catch(QString e)
    {
        isLoadingCorrectly = false;
    }
}
