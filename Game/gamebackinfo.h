#ifndef gameBackInfo_H
#define gameBackInfo_H

#include <QtWidgets>
#include "gamemapelement.h"

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


    QPointF getBeginPosWithCoo(QPoint);
    QPointF getCenterPosWithCoo(QPoint);
    QPoint getCooxWithPos(QPointF);

    QPoint goUpLeft(QPoint);
    QPoint goUpRight(QPoint);
    QPoint goUp(QPoint);
    QPoint goDownLeft(QPoint);
    QPoint goDownRight(QPoint);
    QPoint goDown(QPoint);

    int getBlockNumber(QPoint);
    void listAddAsSet(QList<QPoint>*, QPoint);
    bool listAddSeies(QList<QPoint>*, QPoint);
    bool isPointAvailable(QPoint);
    void listMoveSphere(QPoint, int);

private:
    QList<gameMapElement*> map;
    void variableInitial(QString configFilePath);

    double halfSqrt3;
    int beginX;
    int beginY;

    QList<QPoint> showSphere;
    QList<QPoint> moveList;

    QPixmap backgroundPicture;
    QVector<char> mapElement;
    QPointF beginPosition;
    int lineLength;
    int widthCount;
    int heightCount;
    bool isLoadingCorrectly;


};

#endif // gameBackInfo_H
