#include <QString>
#include <QtTest>
#include <QtWidgets>
#include "backinfo.h"
#include "heroengine.h"
#include "heroitem.h"
#include "normalpackage.h"

class VvTestTest : public QObject
{
    Q_OBJECT

public:
    VvTestTest();

private Q_SLOTS:
    void testGbiDesert2();
    void testHf();
    void testHero();

private:
    GameBackInfo *gbi;
    HeroFactory* hf;
};

VvTestTest::VvTestTest()
{

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
    QCOMPARE(hi->lineLength, 50);                       // ordinary check
    QCOMPARE(hi->theMoney, 0);                          // no money now
    //QCOMPARE(hi->ai, );  error when compare null      // no ai now
    QCOMPARE(hi->isAlive, true);                        // still alive~

    QCOMPARE(hi->ma->moveRange(), 4);       // move ability test
    QCOMPARE(hi->ma->remainingTimes(), 1);  // you can only move 1 time
    QCOMPARE(hi->aa->attackRange(), 1);     // all hero's attack range is 1
    QCOMPARE(hi->aa->remainingTimes(), 1);  // attack also only 1 time

    // functional method test

    // hp system
    hi->addHealth(2);               // now are max
    QCOMPARE(hi->theHealth, 8);     // remain unchange
    hi->addHealth(-2);              // hp reduce
    QCOMPARE(hi->theHealth, 6);     // hp changed
    hi->addHealth(-10);             // you may die
    QCOMPARE(hi->theHealth, 0);     // no hp
    QCOMPARE(hi->isAlive, false);   // and died
    hi->ambulance();                // you were aided
    QCOMPARE(hi->isAlive, true);    // alive
    QCOMPARE(hi->theHealth, 2);     // get 2 HP from aid

    // skill system TODO

    // move system


}

void VvTestTest::testHf()
{
    hf = new HeroFactory(gbi);
    hf->addPackage(new HeroPackageNormal());
    QCOMPARE(hf->getHeroAmount(), 20);      // count of hero in this package
    QCOMPARE(hf->hpl.size(), 1);
    QCOMPARE(hf->hpl[0]->heroPackageIndicator(),
            HeroPackage::HeroPackage_Normal);
    QCOMPARE(hf->innerDir, QString("C:/Users/xiang/Documents/GitHub/rsc/heros/"));
    QCOMPARE(hf->lineLength, 50);           // make sure no error

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

void VvTestTest::testGbiDesert2()
{
    gbi = new GameBackInfo("C:/Users/xiang/Documents/GitHub/rsc/DeathDesert2.xml");
    QVERIFY2(gbi->isLoadingCorrectly, "Initialize Failed");
    QCOMPARE(gbi->configDir, QString("C:/Users/xiang/Documents/GitHub/rsc/"));
    QCOMPARE(gbi->halfSqrt3, sqrt(3) / 2);  // important factor  sin(60)

    QCOMPARE(gbi->beginX, 320);             // begin positon of the leftTop element in the map
    QCOMPARE(gbi->beginY, 200);

    QCOMPARE(gbi->lineLength, 50);          // line length of single hexagon slide
    QCOMPARE(gbi->backCardRect,             // card size depand on the line Length;
             QRectF(0, 0, 190.0, 130.0));   // width is 3.8x  height is 2.6x

    QCOMPARE(gbi->widthCount, 5);           // count of width map element in game
    QCOMPARE(gbi->heightCount, 16);         // count of height
    QCOMPARE(gbi->backgroundPicture,
             QPixmap("C:/Users/xiang/Documents/GitHub/rsc/skinDefault/wallpaper4.jpg").
             scaled(1500, 1200));

    QCOMPARE(gbi->mapElement.size(), 80);   // TODO how to check total 80 convenient
    QCOMPARE(gbi->mapElement[0], 'Z');
    QCOMPARE(gbi->mapElement[79], 'Z');
}

QTEST_MAIN(VvTestTest)

#include "tst_vvtesttest.moc"
