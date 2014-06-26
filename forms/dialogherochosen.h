#ifndef DIALOGHEROCHOSEN_H
#define DIALOGHEROCHOSEN_H

#include <QDialog>

// shouldn't build without import

// given all heros pictures
// return number which hero player choose

namespace Ui {
class DialogHeroChosen;
}

class HeroItem;
class DialogHeroChosen : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogHeroChosen(QWidget *parent = 0);
    void importAllHeros(QList<HeroItem*> hl);
    void importInitialList(QList<int> hn);
    void changeHeroNum(int pos, int newHeroNum);
    void buildList();
    ~DialogHeroChosen();
    
private:
    Ui::DialogHeroChosen *ui;
    QList<HeroItem*> allHeros;
    QList<int> shownHeros;
    const static int commonWidth;
};

#endif // DIALOGHEROCHOSEN_H
