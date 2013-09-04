#ifndef GAME_BACK_BACKINFO_H_
#define GAME_BACK_BACKINFO_H_

#include <QPixmap>
#include <QFile>
#include <QXmlStreamReader>

class GameBackInfo {
 public:
    explicit GameBackInfo(QString configFilePath);

    QPixmap getPixmap(void) { return backgroundPicture; }
    QRectF getCardRect(void) { return backCardRect; }
    QPointF getBeginPosition() { return beginPosition; }
    QString getConfigDir() { return configDir; }
    int getLineLength() { return lineLength; }
    int getWidthCount() { return widthCount; }
    int getHeightCount() { return heightCount; }
    QVector<char> getMapElement() { return mapElement; }
    bool isLoadSuccess() { return isLoadingCorrectly; }

 private:
    double halfSqrt3;
    int beginX;
    int beginY;

    QVector<char> mapElement;
    QRectF backCardRect;
    QString configDir;
    QPixmap backgroundPicture;
    QPointF beginPosition;

    int lineLength;
    int widthCount;
    int heightCount;
    bool isLoadingCorrectly;
};

#endif  // GAME_BACK_BACKINFO_H_
