#ifndef GAME_BACK_BACKINFO_H_
#define GAME_BACK_BACKINFO_H_

#include <QPixmap>
#include <QFile>
#include <QXmlStreamReader>

class GameBackInfo {
 public:
    explicit GameBackInfo(QString configFilePath);

    QPixmap getPixmap(void) const { return backgroundPicture; }
    QRectF getCardRect(void) const { return backCardRect; }
    QPointF getBeginPosition() const { return beginPosition; }
    QString getConfigDir() const { return configDir; }
    int getLineLength() const { return lineLength; }
    int getWidthCount() const { return widthCount; }
    int getHeightCount() const { return heightCount; }
    QVector<char> getMapElement() const { return mapElement; }
    bool isLoadSuccess() const { return isLoadingCorrectly; }

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
