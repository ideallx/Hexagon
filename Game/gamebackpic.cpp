#include "gamebackpic.h"

gameBackInfo::gameBackInfo(QPixmap picture, QString configFilePath) :
    QPixmap(picture)
{
    variableInitial(configFilePath);
}

void gameBackInfo::variableInitial(QString configFilePath)
{
    QFile file(configFilePath);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug("cant open file %s", configFilePath);
        return;
    }

    QXmlStreamReader xml(file.readAll());
    if(xml.readNextStartElement())
    {
        if(xml.name() == "skin")
        {
            widthCount = xml.attributes().value("widthCount").toString().toInt();
            heightCount = xml.attributes().value("heightCount").toString().toInt();
            lineLength = xml.attributes().value("lineLength").toString().toInt();
            qDebug("%d", lineLength);

            QStringList temp = xml.attributes().value("beginPosition").toString().split(", ");
            beginPosition = QPointF(temp[0].toDouble(), temp[1].toDouble());

            temp = xml.attributes().value("mapElement").toString().simplified().split(", ");
            for(int i=0; i<heightCount; i++)
            {
                if(temp[i].length() != widthCount)
                {
                    qDebug("wrong map element");
                    return;
                }
                for(int j=0; j<widthCount; j++)
                {
                    mapElement.append(temp[i][j].toLatin1());
                }
            }
        }
    }

}
