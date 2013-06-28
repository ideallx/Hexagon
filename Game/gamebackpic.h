#ifndef gameBackInfo_H
#define gameBackInfo_H
#include <QWidget>
#include <QFile>

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
    QVector<int> getMapElement();
    void setMapElement();

    enum gameEnvironment_t
    {
        areaSpace,
        areaGrass,
        areaHome,
        areaStone,
        areaShop,
        area
    };


private:
    void variableInitial(QString configFilePath);

    QPixmap backgroundPicture;
    QVector<int> mapElement;
    int lineLength;
    int beginPosition;
    int widthCount;
    int HeightCount;


};

#endif // gameBackInfo_H
