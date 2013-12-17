#ifndef GAME_BACK_BACKINFO_H_
#define GAME_BACK_BACKINFO_H_

#include <QPixmap>
#include <QFile>
#include <QXmlStreamReader>

class GameBackInfo {
 public:
    explicit GameBackInfo(QString configFilePath);

    inline QPixmap getPixmap() const { return backgroundPicture; }
    inline QRectF getCardRect() const { return backCardRect; }
    inline QPointF getBeginPosition() const { return beginPosition; }
    inline QString getConfigDir() const { return configDir; }
    inline int getLineLength() const { return lineLength; }
    inline int getWidthCount() const { return widthCount; }
    inline int getHeightCount() const { return heightCount; }
    inline QVector<char> getMapElement() const { return mapElement; }
    inline bool isLoadSuccess() const { return isLoadingCorrectly; }

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
