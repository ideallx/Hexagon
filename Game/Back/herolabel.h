#ifndef HEROLABEL_H
#define HEROLABEL_H

#include <QLabel>

class heroLabel : public QLabel
{
    Q_OBJECT
public:
    heroLabel(QWidget *parent=0, Qt::WindowFlags f=0);

    void setPixmap(const QPixmap &qp);
    void setHeroNum(int i) { heroNum = i; }

    void mouseMoveEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *);

signals:
    void heroChosen(int);

private:
    int heroNum;
};

#endif // HEROLABEL_H
