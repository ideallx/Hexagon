#include <QString>
#include <QtTest>
#include <QtWidgets>
#include "backinfo.h"
#include "heroengine.h"
#include "normalpackage.h"

class VvTestTest : public QObject
{
    Q_OBJECT

public:
    VvTestTest();

private Q_SLOTS:
    void testGbiDesert2();
    void testHf();

private:
    GameBackInfo *gbi;
    HeroFactory* hf;
};

VvTestTest::VvTestTest()
{

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

    // HeroItem* hi = hf->createHero()  TODO
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
