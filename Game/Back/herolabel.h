#ifndef GAME_BACK_HEROLABEL_H_
#define GAME_BACK_HEROLABEL_H_

#include <QToolButton>

class HeroLabel : public QToolButton {
    Q_OBJECT

 public:
    explicit HeroLabel(QWidget *parent = 0);

    void setPixmap(const QPixmap &qp);
    void setHeroNum(int i) { theHeroNum = i; }
    int heroNum() { return theHeroNum; }

 private:
    static const int pixWidth = 200;
    int theHeroNum;
};

#endif  // GAME_BACK_HEROLABEL_H_
