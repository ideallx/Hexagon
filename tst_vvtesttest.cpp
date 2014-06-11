#include <QString>
#include <QtTest>
#include <QList>
#include <QtWidgets>
#include "backinfo.h"
#include "heroengine.h"
#include "heroitem.h"
#include "normalpackage.h"
#include "coordinate.h"
#include "itemcollector.h"
#include "mapelement.h"
#include "cardengine.h"
#include "carditem.h"
#include "Package/normalpackage.h"
#include "eventcenter.h"
#include "backview.h"

/**
 * @brief The VvTestTest class
 * object initial Sequence
 *
 *  MainWindow
 *      UiMainWindow
 *      GameProcess
 *      EventCenter
 *          GameCoordinate
 *          ItemCollector
 *              MapEngine
 *                  GameMapElement
 *              CardEngine
 *                  CardItem
 *              HeroFactory
 *                  HeroItem
 *              EquipShop
 *                  Equipment
 *
 */


class VvTestTest : public QObject
{
    Q_OBJECT

public:
    VvTestTest();

private:
    void testGameMapElement(GameMapElement*gme, int id);
    void testCardItem(HandCard* hc, int id);

private Q_SLOTS:
    void testGbiDesert2();
    void testGameCoordinate();
    void testItemCollector();
    void testMapEngine();
    void testCardEngine();
    void testHf();
    void testHero();
    // void testEquipShop();

    void testEventCenter();

private:
    int lineLength;
    QString pathPrefix;

    GameBackInfo *gbi;
    HeroFactory* hf;
    GameCoordinate* gc;
    ItemCollector* ic;
    MapEngine* me;
    CardEngine* ce;
    CardPackageNormal* cpn;
    EventCenter* ec;
};

VvTestTest::VvTestTest()
    : lineLength(50),
      pathPrefix("C:/Users/xiang/Documents/GitHub/") {

}

/**
 * @brief essential background of the game
 */
void VvTestTest::testGbiDesert2()
{
    gbi = new GameBackInfo(QString("%1rsc/DeathDesert2.xml").arg(pathPrefix));
    QVERIFY2(gbi->isLoadingCorrectly, "Initialize Failed");
    QCOMPARE(gbi->configDir, QString("%1rsc/").arg(pathPrefix));
    QCOMPARE(gbi->halfSqrt3, sqrt(3) / 2);  // important factor  sin(60)

    QCOMPARE(gbi->beginX, 320);             // begin positon of the leftTop element in the map
    QCOMPARE(gbi->beginY, 200);

    QCOMPARE(gbi->lineLength, lineLength);  // line length of single hexagon slide
    QCOMPARE(gbi->backCardRect,             // card size depand on the line Length;
             QRectF(0, 0, 190.0, 130.0));   // width is 3.8x  height is 2.6x

    QCOMPARE(gbi->widthCount, 5);           // count of width map element in game
    QCOMPARE(gbi->heightCount, 16);         // count of height
    QCOMPARE(gbi->backgroundPicture,
             QPixmap(QString("%1rsc/skinDefault/wallpaper4.jpg").arg(pathPrefix)).
             scaled(1500, 1200));

    QCOMPARE(gbi->mapElement.size(), 80);   // TODO how to check total 80 convenient
    QCOMPARE(gbi->mapElement[0], 'Z');
    QCOMPARE(gbi->mapElement[79], 'Z');
}


void VvTestTest::testHf()
{
    hf = new HeroFactory(gbi);
    hf->addPackage(new HeroPackageNormal());
    // ic->setHeroFactory(hf);
    QCOMPARE(hf->getHeroAmount(), 20);      // count of hero in this package
    QCOMPARE(hf->hpl.size(), 1);
    QCOMPARE(hf->hpl[0]->heroPackageIndicator(),
            HeroPackage::HeroPackage_Normal);
    QCOMPARE(hf->innerDir, QString("%1rsc/heros/").arg(pathPrefix));
    QCOMPARE(hf->lineLength, lineLength);   // make sure no error

    QVector<QString> heros;
    for (int i = 0; i < 20; i++) {
        QString heroName = hf->getHeroInfoByNum(static_cast<HeroNum> (i)).heroName;
        if (heros.contains(heroName))
            break;
        else
            heros.append(heroName);
    }
    QCOMPARE(heros.size(), 20);             // make sure no repeat hero name
}

void VvTestTest::testHero() {
    ExternInfo ei;                  // example hero baoxiong
    ei.c = Camp::CampBlue;          // hero camp
    ei.h = HeroNum::BaoXiong;       // hero name
    ei.p = QPoint(0, 1);            // hero birth position
    HeroItem* hi = hf->createHero(ei);

    // TODO all hero pixmap remain unchecked

    // initial status test
    QCOMPARE(hi->thePlayerName, QString("player 1"));   // TODO now all player 1
    QCOMPARE(hi->theCards, QList<int>());               // no cards;
    QCOMPARE(hi->skills, QList<SkillBase*>());          // no skill
    QCOMPARE(hi->heroSkills, QList<SkillBase*>());      // TODO no hero skill now
    QCOMPARE(hi->theMaxHealth, 8);                      // max hp 8
    QCOMPARE(hi->theHealth, 8);                         // cur hp 8
    QCOMPARE(hi->equipments.size(), 4);                 // 4 NULL equipment, for 4 types equip 1 each
    QCOMPARE(hi->heroStates.size(), 0);                 // no states now
    QCOMPARE(hi->theSexual, Sexual::SexMale);           // masculine hero
    QCOMPARE(hi->theHeroName, QString("BaoXiong"));     // hero name
    QCOMPARE(hi->lineLength, lineLength);               // ordinary check
    QCOMPARE(hi->theMoney, 0);                          // no money now
    //QCOMPARE(hi->ai, );  error when compare null      // no ai now
    QCOMPARE(hi->isAlive, DeathStatus::Alive);                        // still alive~


    // functional method test

    // hp system
    hi->addHealth(2);               // now are max
    QCOMPARE(hi->theHealth, 8);     // remain unchange
    hi->addHealth(-2);              // hp reduce
    QCOMPARE(hi->theHealth, 6);     // hp changed
    hi->addHealth(-10);             // you may die
    QCOMPARE(hi->theHealth, 0);     // no hp
    QCOMPARE(hi->isAlive, DeathStatus::Dying);  // and dying
    hi->ambulance();                // you were aided
    QCOMPARE(hi->isAlive, DeathStatus::Alive);  // alive
    QCOMPARE(hi->theHealth, 2);     // get 2 HP from aid
    hi->addHealth(-5);              // once again no hp
    hi->ambulance(false);           // but no one save you
    QCOMPARE(hi->heroAliveState(), DeathStatus::Died);  // now you died
    hi->revive();                   // wake up to next test

    // money system
    hi->addMoney(6);        // given so much money
    hi->addMoney(3);
    hi->addMoney(4);
    QList<int> expected;
    expected.append(6);
    expected.append(3);
    expected.append(4);
    QCOMPARE(hi->moneyLists(), expected);   // you should record these coin
    QCOMPARE(hi->theMoney, 13);             // and total amount
    expected.clear();
    expected.append(4);
    hi->useMoney(expected);                 // now we use coin cost 4
    expected.clear();
    expected.append(6);
    expected.append(3);
    QCOMPARE(hi->moneyLists(), expected);   // I shall have coin cost 3 and 6
    QCOMPARE(hi->theMoney, 9);              // and total amount 9

    // process control
    QCOMPARE(hi->ma->moveRange(), 4);       // move ability test
    QCOMPARE(hi->ma->remainingTimes(), 1);  // you can only move 1 time
    QCOMPARE(hi->aa->attackRange(), 1);     // all hero's attack range is 1
    QCOMPARE(hi->aa->remainingTimes(), 1);  // attack also only 1 time
    hi->ma->moveTimeMinus();                // make the condition that
    hi->aa->attackTimeMinus();              // you can neither move or attack
    QCOMPARE(hi->ma->remainingTimes(), 0);
    QCOMPARE(hi->aa->remainingTimes(), 0);  // condition done
    hi->beginTurnSettle();                  // reset your condition
    QCOMPARE(hi->ma->remainingTimes(), 1);  // now you can move and attack
    QCOMPARE(hi->aa->remainingTimes(), 1);
    // TODO end turn settle


    // skill system TODO
}

// contain the algorithm
void VvTestTest::testGameCoordinate() {
    gc = new GameCoordinate(gbi);
    QCOMPARE(gc->beginX, gbi->beginX);
    QCOMPARE(gc->beginY, gbi->beginY);
    QCOMPARE(gc->lineLength, lineLength);
    QCOMPARE(gc->widthCount, gbi->widthCount);
    QCOMPARE(gc->heightCount, gbi->heightCount);
    QCOMPARE(gc->halfSqrt3, sqrt(3) / 2);
    QCOMPARE(gc->mapElement, gbi->mapElement);

    // up left down right
    QCOMPARE(gc->goUp(QPoint(2, 2)), QPoint(2, 0));
    QCOMPARE(gc->goUpLeft(QPoint(2, 2)), QPoint(1, 1));
    QCOMPARE(gc->goUpRight(QPoint(2, 2)), QPoint(2, 1));
    QCOMPARE(gc->goDown(QPoint(2, 2)), QPoint(2, 4));
    QCOMPARE(gc->goDownLeft(QPoint(2, 2)), QPoint(1, 3));
    QCOMPARE(gc->goDownRight(QPoint(2, 2)), QPoint(2, 3));

    QCOMPARE(gc->goUp(QPoint(1, 2)), QPoint(1, 0));
    QCOMPARE(gc->goUpLeft(QPoint(1, 2)), QPoint(0, 1));
    QCOMPARE(gc->goUpRight(QPoint(1, 2)), QPoint(1, 1));
    QCOMPARE(gc->goDown(QPoint(1, 2)), QPoint(1, 4));
    QCOMPARE(gc->goDownLeft(QPoint(1, 2)), QPoint(0, 3));
    QCOMPARE(gc->goDownRight(QPoint(1, 2)), QPoint(1, 3));

    // TODO other algorithm test
}

void VvTestTest::testGameMapElement(GameMapElement *gme, int id) {
    int j = id / gbi->widthCount;
    int i = id % gbi->widthCount;
    QCOMPARE(gme->point(), QPoint(i, j));
    QCOMPARE(gme->lineLength, lineLength);
    QCOMPARE(gme->halfSqrt3, sqrt(3) / 2);
    QCOMPARE(gme->path, QString("%1rsc/elements/").arg(pathPrefix));
    QCOMPARE(gme->elementType, static_cast<AreaHexagon> (gbi->mapElement[id]));
    QPixmap block;
    QString elementName;
    bool moveAvailable = true;
    switch (gme->elementType) {
    case AreaHexagon::AreaGrass:
        block = QPixmap(gme->path + "forest.png");
        elementName = QString(tr("grass"));
        break;
    case AreaHexagon::AreaStone:
        block = QPixmap(gme->path + "stone.png");
        elementName = QString(tr("stone"));
        moveAvailable = false;
        break;
    case AreaHexagon::AreaShop:
        block = QPixmap(gme->path + "shop.png");
        elementName = QString(tr("shop"));
        moveAvailable = false;
        break;
    case AreaHexagon::AreaAlchemy:
        block = QPixmap(gme->path + "alchemy.png");
        elementName = QString(tr("alchemy"));
        break;
    case AreaHexagon::AreaSpring:
        block = QPixmap(gme->path + "spring.png");
        elementName = QString(tr("spring"));
        moveAvailable = false;
        break;
    case AreaHexagon::AreaCamp:
        block = QPixmap(gme->path + "camp.png");
        elementName = QString(tr("camp"));
        break;
    case AreaHexagon::AreaSwamp:
        block = QPixmap(gme->path + "swamp.png");
        elementName = QString(tr("swamp"));
        break;
    case AreaHexagon::AreaDesert:
        block = QPixmap(gme->path + "desert.png");
        elementName = QString(tr("desert"));
        break;
    case AreaHexagon::AreaWater:
        block = QPixmap(gme->path + "water.png");
        elementName = QString(tr("water"));
        break;
    case AreaHexagon::AreaFort:
        block = QPixmap(gme->path + "fort.png");
        elementName = QString(tr("fort"));
        moveAvailable = false;
        break;
    case AreaHexagon::AreaRedHome:
        block = QPixmap(gme->path + "red.png");
        elementName = QString(tr("red camp"));
        break;
    case AreaHexagon::AreaTree:
        block = QPixmap(gme->path + "tree.png");
        elementName = QString(tr("tree"));;
        moveAvailable = false;
        break;
    case AreaHexagon::AreaBlueHome:
        block = QPixmap(gme->path + "blue.png");
        elementName = QString(tr("blue camp"));
        break;
    default:
        block = QPixmap(gme->path + "desert.png");
        elementName = QString(tr("desert"));
    }
//    QCOMPARE(gme->brush(), QBrush(block.scaledToWidth(2 * lineLength,
//                                                      Qt::SmoothTransformation)));
    QCOMPARE(gme->elementName, elementName);
    QCOMPARE(gme->moveAvailable, moveAvailable);
}

void VvTestTest::testMapEngine() {
    me = new MapEngine(gbi);
    ic->setMapEngine(me);
    QList<GameMapElement*> mapList = me->generateMapElements();
    for (int i = 0; i < mapList.size(); i++) {
        GameMapElement *gme = mapList[i];
        testGameMapElement(gme, i);
    }
}

void VvTestTest::testItemCollector() {
    ic = new ItemCollector(gbi, gc);
    QVERIFY(!ic->initialCompete());

}

void VvTestTest::testCardEngine() {
    ce = new CardEngine(gbi);
    QCOMPARE(ce->cardAmount, 0);    // no cards before add package
    QCOMPARE(ce->cardsId, 0);       //

    cpn = new CardPackageNormal();
    ce->addPackage(cpn);            // TODO add new package to test

    QCOMPARE(ce->cardAmount, 60);   // 60 cards in this package
    QCOMPARE(ce->cardsId, 0);       // this package will count begin as 0
    QCOMPARE(ce->path, QString("%1rsc/cards/").arg(pathPrefix));    // dir of cards pixmap

    ce->cardsId = 0;                // regenerate cards;
    QList<HandCard*> cards = ce->generateHandCards();
    for (int i = 0; i < ce->cardAmount; i++) {
        testCardItem(cards[i], i);
    }
    QCOMPARE(ce->cardsId, 60);      // next package begin at 60
}

void VvTestTest::testCardItem(HandCard* hc, int id) {   // TODO multi package
    QCOMPARE(hc->theId, id);
    QCOMPARE(hc->type(), id);       // its type is id
    QCOMPARE(static_cast<int> (hc->cardType()),
             static_cast<int> (cpn->getCardInfo(id).cardType));
    QCOMPARE(hc->pixmap(), QPixmap(QString("%1%2.jpg").
                                   arg(ce->path).
                                   arg(cpn->getCardInfo(id).name)));

    // card skills remain undone
}

// use its own inner variable not involve with the upstairs case
void VvTestTest::testEventCenter() {
    BackView* bv = new BackView();
    ec = new EventCenter(bv);
    QCOMPARE(ec->roundNum, 0);          // game not begun now
    QCOMPARE(ec->gameBegined, false);
    QCOMPARE(ec->gameTerminated, false);
    QCOMPARE(ec->playerHeroNum, 0);     // no hero now
    QCOMPARE(ec->heroSeq.size(), 0);    //

    ec->preGame();                      // choose hero, birth, camp
    QCOMPARE(ec->playerHeroNum, 0);     // no hero now
    QCOMPARE(ec->heroSeq.size(), 0);    //
    // TODO

    ec->gameBegin();
    QCOMPARE(ec->gameBegined, true);
    QCOMPARE(ec->gameTerminated, false);
//    QCOMPARE(ec->playerHeroNum, 4);     // have hero now ??
//    QCOMPARE(ec->heroSeq.size(), 4);    //

    // now player 1 is human player 2 3 4 are all AI

}

QTEST_MAIN(VvTestTest)

#include "tst_vvtesttest.moc"
