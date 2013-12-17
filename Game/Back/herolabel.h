#ifndef GAME_BACK_HEROLABEL_H_
#define GAME_BACK_HEROLABEL_H_

#include <QToolButton>
#include "enums.h"

class HeroLabel : public QToolButton {
    Q_OBJECT

 public:
    explicit HeroLabel(QWidget *parent = 0);

    void setPixmap(const QPixmap &qp);
    inline void setHeroNum(HeroNum i) {theHeroNum = i; }
    inline HeroNum heroNum() { return theHeroNum; }

 private:
    static const int pixWidth = 200;
    HeroNum theHeroNum;
};

#endif  // GAME_BACK_HEROLABEL_H_
