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
    QPixmap getPixmap(void) { return backgroundPicture; }
    QPointF getBeginPosition() { return beginPosition; }
    int getLineLength() { return lineLength; }
    int getWidthCount() { return widthCount; }
    int getHeightCount() { return heightCount; }
    QVector<char> getMapElement() { return mapElement; }
    bool isLoadSuccess() { return isLoadingCorrectly; }



private:
    void variableInitial(QString configFilePath);

    QPixmap backgroundPicture;
    QVector<char> mapElement;
    QPointF beginPosition;
    int lineLength;
    int widthCount;
    int heightCount;
    bool isLoadingCorrectly;


};

#endif // gameBackInfo_H
