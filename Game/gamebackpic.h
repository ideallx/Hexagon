#ifndef GAMEBACKPIC_H
#define GAMEBACKPIC_H
#include <QWidget>

class gameBackPic : public QPixmap
{
public:
    gameBackPic(QPixmap picture);
    QPixmap getPixmap(void);
    QPointF getBeginPostion();
    int getLineLength();
    int getWidthCount();
    int getHeightCount();


private:
    QPixmap backgroundPicture;
};

#endif // GAMEBACKPIC_H
