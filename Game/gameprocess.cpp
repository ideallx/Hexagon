#include <QDebug>
#include <QMessageBox>

#include "gameprocess.h"
#include "otherwidgets.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "eventcenter.h"
#include "herolabel.h"
#include "gameWidget.h"
#include "backinfo.h"
#include "coordinate.h"
#include "backscene.h"
#include "heroengine.h"
#include "cardengine.h"
#include "mapelement.h"
#include "normalpackage.h"

#define GIVEN_CONDITION
#define CONFIGPATH "../rsc/config.xml"

/**
 * ModeChoose -> GameChoose -> HeroChoose -> BirthChoose -> GameBegin
 */
GameProcess::GameProcess(QWidget *p)
    : parent(p),
      playerHeroSeq(0) {
}

GameProcess::~GameProcess() {
    qDebug() << "deconstructor";
}

void GameProcess::loadResources(QString path) {
    try {
        gbi = new GameBackInfo(path);
        qDebug() << "gbi load complete...";

        hf = new HeroFactory(gbi);
        hf->addPackage(new HeroPackageNormal());
        qDebug() << "hf  load complete...";
    } catch(const QString& e) {
        QMessageBox::critical(NULL, tr("LYBNS"), e);
    }
}

void GameProcess::preGame() {
#ifdef GIVEN_CONDITION
    loadResources("../rsc/DeathDesert2.xml");
    for (int i = 0; i < 4; i++) {
        ExternInfo ei;
        ei.h = static_cast<HeroNum>(rand() % hf->getHeroAmount());
        ei.p = QPoint(300, 300);  // untouchable point
        eil.append(ei);
    }
    eil[0].h = HeroNum::AnYingZhiRen;
    chosenHeroNum = HeroNum::MieShaZhe;
    buildGameInfo();
#else
    modeChooseScreen();
#endif
}

void GameProcess::preGameClean() {
#ifndef GIVEN_CONDITION
    delete mcw;
    delete uic;
    delete uig;
#endif
}

void GameProcess::endGame() {
}

void GameProcess::gameChooseScreen() {
    uig = new Ui::ChooseGame();
    chooseDialog = new QDialog(mcw);
    chooseDialog->setModal(true);
    uig->setupUi(chooseDialog);

    int res = chooseDialog->exec();
    if (res == QDialog::Accepted) {
        ExternInfo ei;
        int totalHero = 4;

        if (uig->mode_2person->isChecked())
            totalHero = 2;
        else if (uig->mode_4person->isChecked())
            totalHero = 4;

        QString path;
        if (uig->radioButton_dd1->isChecked())
            path = "../rsc/config.xml";
        else if (uig->radioButton_dd2->isChecked())
            path = "../rsc/DeathDesert2.xml";

        loadResources(path);

        ei.h = HeroNum::MieShaZhe;
        ei.p = QPoint(300, 300);  // untouchable point

        for (int i = 0; i < totalHero; i++) {
            eil.append(ei);
        }

        playerHeroSeq = rand() % totalHero;
        heroChooseScreen();
    }
}

void GameProcess::modeChooseScreen() {
    mcw = new ModeChooseWidget(parent);
    connect(mcw->singleButton(), &QToolButton::clicked,
            this, &GameProcess::gameChooseScreen);
    mcw->show();
}

void GameProcess::buildGameInfo() {
    qDebug() << "choose num:" << static_cast<int>(chosenHeroNum);

    gc = new GameCoordinate(gbi);
    qDebug() << "gc  load complete...";

    ic = new ItemCollector(gbi, gc);

    ic->setMapElement(new MapEngine(gbi));

    CardEngine *ce = new CardEngine(gbi);
    ce->addPackage(new CardPackageNormal());
    ic->setCardEngine(ce);

    ic->setCampHealth();

    QVector<HeroNum> heroCode;
    heroCode.append(eil[playerHeroSeq].h);
    for (int i = 0; i < eil.size(); i++) {
        if (i%2)
            eil[i].c = Camp::CampRed;
        else
            eil[i].c = Camp::CampBlue;

        if (i == playerHeroSeq)
            continue;

        HeroNum code;
        do {
            code = static_cast<HeroNum>(rand()%hf->getHeroAmount());
        } while (heroCode.contains(code));
        heroCode.append(code);

        eil[i].h = code;
    }

    ic->setHeroFactory(hf, eil);
    ic->setPlaySeq(playerHeroSeq);
    qDebug() << "ic  load complete...";
    EquipmentShop* es = new EquipmentShop(gbi->getConfigDir());
    es->addEquipmentPackage(new EquipmentPackageNormal());
    ic->setEquipmentShop(es);
    emit gameStart();
}

void GameProcess::inGame() {
}


void GameProcess::heroChooseScreen() {
    qDebug() << "chosse hero screen";
    uic = new Ui::chooseHero();
    chooseDialog = new QDialog(mcw);
    chooseDialog->setModal(true);
    uic->setupUi(chooseDialog);

    QList<HeroNum> heroNumList;
    qDebug() << "Total Hero Num:" << hf->getHeroAmount();
    for (int i = 0; i < 8; i++) {
        HeroNum code;
        do {
            code = static_cast<HeroNum>(rand()%hf->getHeroAmount());
        } while (heroNumList.contains(code));
        heroNumList.append(code);
    }
    for (int i = 0; i < 4; i++) {
        HeroLabel* ql = new HeroLabel(chooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" +
                              hf->getHeroInfoByNum(heroNumList[i]).heroName +
                              "_Whole.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout->addWidget(ql);
        connect(ql, &HeroLabel::clicked, this, &GameProcess::heroChosed);
    }
    for (int i = 4; i < 8; i++) {
        HeroLabel* ql = new HeroLabel(chooseDialog);
        ql->setPixmap(QPixmap(gbi->getConfigDir() + "/heros/" +
                              hf->getHeroInfoByNum(heroNumList[i]).heroName +
                              "_Whole.png"));
        ql->setHeroNum(heroNumList[i]);
        uic->horizontalLayout1->addWidget(ql);
        connect(ql, &HeroLabel::clicked, this, &GameProcess::heroChosed);
    }
    int res = chooseDialog->exec();
    if (res != QDialog::Accepted)
        chosenHeroNum = heroNumList[rand()%8];
    eil[playerHeroSeq].h = static_cast<HeroNum>(chosenHeroNum);
    buildGameInfo();
}

void GameProcess::heroChosed() {
    chosenHeroNum = static_cast<HeroLabel*>(this->sender())->heroNum();
    chooseDialog->accept();
}

// deprecated
void GameProcess::birthChooseScreen() {
    qDebug() << "chosse birth screen";
    uib = new Ui::ChooseBirth();
    chooseDialog = new QDialog(mcw);
    chooseDialog->setModal(true);
    uib->setupUi(chooseDialog);

    QGraphicsScene *qgs = new QGraphicsScene();
    for (int i = 0; i < 2; i++) {
        GameMapElement* gme = new GameMapElement
                (gbi->getLineLength(), (AreaHexagon)0,
                 QPoint(i, 1), gbi->getConfigDir()+"elements/");
        gme->setPos(gc->leftUpPosNoOffset(gme->point()));
        qgs->addItem(gme);
    }
    for (int i = 0; i < 3; i++) {
        GameMapElement* gme = new GameMapElement
                (gbi->getLineLength(), (AreaHexagon)0,
                 QPoint(i, 2), gbi->getConfigDir()+"elements/");
        gme->setPos(gc->leftUpPosNoOffset(gme->point()));
        qgs->addItem(gme);
    }
    for (int i = 0; i < 2; i++) {
        GameMapElement* gme = new GameMapElement
                (gbi->getLineLength(), (AreaHexagon)0,
                 QPoint(i, 3), gbi->getConfigDir()+"elements/");
        gme->setPos(gc->leftUpPosNoOffset(gme->point()));
        qgs->addItem(gme);
    }
    for (int i = 0; i < 2; i++) {
        GameMapElement* gme = new GameMapElement
                (gbi->getLineLength(), (AreaHexagon)0,
                 QPoint(1, i*4), gbi->getConfigDir()+"elements/");
        gme->setPos(gc->leftUpPosNoOffset(gme->point()));
        qgs->addItem(gme);
    }

    uib->graphicsView->setScene(qgs);

    QList<GameMapElement*> l = ic->getBlueTeamCamp();
    for (int i = 0; i < l.size(); i++) {
        qDebug() << l[i]->point();
    }

    chooseDialog->exec();
}
