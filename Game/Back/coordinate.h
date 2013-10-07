#ifndef GAME_BACK_COORDINATE_H_
#define GAME_BACK_COORDINATE_H_

#include <QPoint>
#include <QList>
#include <QQueue>
#include <QVector>

// ALGORITHM

class GameBackInfo;

class GameCoordinate {
 public:
    enum PointState {
        NotChecked,
        Added,
        Checked
    };

    struct RecursivePoint_t {
        QPoint parent;
        QPoint self;
        enum PointState state;
    };

    explicit GameCoordinate(GameBackInfo* gbi);
    QList<QPoint> getMovePoint() const { return showRange; }
    static QPoint goUpLeft(QPoint);
    static QPoint goUpRight(QPoint);
    static QPoint goUp(QPoint);
    static QPoint goDownLeft(QPoint);
    static QPoint goDownRight(QPoint);
    static QPoint goDown(QPoint);
    QList<QPoint> path (QPoint from, QPoint to);
    bool addPointToQueue(QPoint p, QPoint from);
    static QPoint outPoint() { return QPoint(-1, -1); }
    bool checkPointAvailable(QPoint in);
    struct RecursivePoint_t getStruct(QPoint in);
    QPoint getCooxWithPos(QPointF);
    QPointF leftUpPosNoOffset(QPoint);
    QPointF getBeginPosWithCoo(QPoint);
    QPointF getBeginPosOfHero(QPoint);
    QPointF getCenterPosWithCoo(QPoint);
    void clearPoints();

 private:
    QQueue<struct RecursivePoint_t> queue;
    QList<QList<struct RecursivePoint_t> > points;
    int beginX;
    int beginY;
    int lineLength;
    double halfSqrt3;
    int widthCount;
    int heightCount;
    QVector<char> mapElement;
    QList<QPoint> showRange;
};


#endif  // GAME_BACK_COORDINATE_H_
