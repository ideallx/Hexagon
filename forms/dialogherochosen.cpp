#include "dialogherochosen.h"
#include "ui_dialogherochosen.h"
#include "heroitem.h"

const int DialogHeroChosen::commonWidth = 100;

DialogHeroChosen::DialogHeroChosen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHeroChosen) {
    ui->setupUi(this);
}

DialogHeroChosen::~DialogHeroChosen()
{
    delete ui;
}

void DialogHeroChosen::importAllHeros(QList<HeroItem*> hl) {
    allHeros = hl;
}

// eight contents of HeroNum
#define showPix(n) ui->label##n->setPixmap(allHeros[shownHeros[n]]->wholePic()-> \
    scaledToWidth(commonWidth, Qt::SmoothTransformation));

void DialogHeroChosen::importInitialList(QList<int> hn) {
    shownHeros = hn;
    buildList();
}

void DialogHeroChosen::buildList() {
    showPix(0);
    showPix(1);
    showPix(2);
    showPix(3);
    showPix(4);
    showPix(5);
    showPix(6);
    showPix(7);
}

// position
// 0 1 2 3
// 4 5 6 7
//
void DialogHeroChosen::changeHeroNum(int pos, int newHeroNum) {
    shownHeros[pos] = newHeroNum;
    buildList();
}
