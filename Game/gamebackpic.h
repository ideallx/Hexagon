#ifndef gameBackInfo_H
#define gameBackInfo_H
#include <QWidget>
#include <QFile>
#include <QXmlStreamReader>

class gameBackInfo : public QPixmap
{
    Q_PROPERTY(char* mapElement READ getMapElement WRITE setMapElement)

public:
    gameBackInfo(QPixmap picture, QString configFilePath);
    QPixmap getPixmap(void);
    QPointF getBeginPosition();
    int getLineLength();
    int getWidthCount();
    int getHeightCount();
    QVector<char> getMapElement();



private:
    void variableInitial(QString configFilePath);

    QPixmap backgroundPicture;
    QVector<char> mapElement;
    QPointF beginPosition;
    int lineLength;
    int widthCount;
    int heightCount;


};

#endif // gameBackInfo_H
