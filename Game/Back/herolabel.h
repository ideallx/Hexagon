#ifndef HEROLABEL_H
#define HEROLABEL_H

#include <QToolButton>

class heroLabel : public QToolButton
{
    Q_OBJECT
public:
    heroLabel(QWidget *parent=0);

    void setPixmap(const QPixmap &qp);
    void setHeroNum(int i) { theHeroNum = i; }
    int heroNum() { return theHeroNum; }

private:
    int theHeroNum;
};

#endif // HEROLABEL_H
