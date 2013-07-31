#include "backinfo.h"

gameBackInfo::gameBackInfo(QString configFilePath)
{
    QFile file(configFilePath);
    isLoadingCorrectly = true;
    halfSqrt3 = sqrt(3.0)/2;
    beginX = beginPosition.x();
    beginY = beginPosition.y();
    int i = configFilePath.lastIndexOf(QChar('/'));
    configDir = configFilePath.left(i) + '/';

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

                backCardRect = QRectF(0, 0, 3.8*lineLength, 2.6*lineLength);

                QStringList temp = xml.attributes().value("beginPosition").toString().split(", ");
                beginPosition = QPointF(temp[0].toDouble(), temp[1].toDouble());
                beginX = beginPosition.x();
                beginY = beginPosition.y();

                temp = xml.attributes().value("backRect").toString().split(", ");
                QRect rect = QRect(0, 0, temp[0].toInt(), temp[1].toInt());

                backgroundPicture = QPixmap(xml.attributes().value("backpic").toString()).scaled(rect.width(), rect.height());
                if(backgroundPicture.isNull())
                    throw QString("no pic");

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
        qDebug(qPrintable(e));
        isLoadingCorrectly = false;
    }
}
