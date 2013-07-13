#ifndef gameBackInfo_H
#define gameBackInfo_H

#include <QtWidgets>

class gameBackInfo
{
public:
    gameBackInfo(QString configFilePath);

    QPixmap getPixmap(void) { return backgroundPicture; }
    QPointF getBeginPosition() { return beginPosition; }
    int getLineLength() { return lineLength; }
    int getWidthCount() { return widthCount; }
    int getHeightCount() { return heightCount; }

    QVector<char> getMapElement() { return mapElement; }

    bool isLoadSuccess() { return isLoadingCorrectly; }


private:
    void variableInitial(QString configFilePath);

    double halfSqrt3;
    int beginX;
    int beginY;
    QVector<char> mapElement;


    QPixmap backgroundPicture;
    QPointF beginPosition;

    int lineLength;
    int widthCount;
    int heightCount;
    bool isLoadingCorrectly;


};

#endif // gameBackInfo_H
