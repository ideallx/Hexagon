#ifndef HEROLABEL_H
#define HEROLABEL_H

#include <QToolButton>

class HeroLabel : public QToolButton
{
    Q_OBJECT
public:
    HeroLabel(QWidget *parent=0);

    void setPixmap(const QPixmap &qp);
    void setHeroNum(int i) { theHeroNum = i; }
    int heroNum() { return theHeroNum; }

private:
    static const int pixWidth = 200;
    int theHeroNum;
};

#endif // HEROLABEL_H
