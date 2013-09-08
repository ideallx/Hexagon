#include "heroitem.h"
#include "heroengine.h"
#include "backinfo.h"

HeroFactory::HeroFactory(GameBackInfo* gbi)
    : scene(NULL),
    innerDir(gbi->getConfigDir() + "heros/"),
    lineLength(gbi->getLineLength()),
    heroAmount(0) {
}

HeroItem* HeroFactory::createHero(struct ExternInfo ei) {
    HeroItem * item = new HeroItem(lineLength);
    item->setAvaterPic(new QPixmap(innerDir +
                                   getHeroInfoByNum(ei.h).heroName +
                                   "_Head.png"));
    item->setwholePic(new QPixmap(innerDir +
                                  getHeroInfoByNum(ei.h).heroName +
                                  "_Whole.png"));
    item->setBrush(item->avaterPic()->scaledToWidth(item->rect().width(),
                                                    Qt::SmoothTransformation));
    item->setHeroProperty(getHeroInfoByNum(ei.h));
    item->setHeroName(getHeroInfoByNum(ei.h).heroName);
    item->setPoint(ei.p);
    item->setCamp(ei.c);
    return item;
}

QList<HeroItem*> HeroFactory::generateHeroes(QList<struct ExternInfo> list) {
    QList<HeroItem*> result;
    for (int i = 0; i < list.size(); i++) {
        result.append(createHero(list[i]));
    }
    return result;
}

void HeroFactory::addPackage(AbstractHeroPacakage* ahp) {
    hpl.append(ahp);
    heroAmount += ahp->heroNumInPackage();
}

struct HeroInfo HeroFactory::getHeroInfoByNum(int n) {
    for (int i = 0; i < hpl.size(); i++) {
        if (n > hpl[i]->heroNumInPackage()) {
            n -= hpl[i]->heroNumInPackage();
        } else {
            return hpl[i]->getHeroInfo(n);
        }
    }
    qDebug() << "Hero Num Wrong";
    struct HeroInfo white = {2, 3, 9,  sex_male, tr("wrongHero")};
    return white;
}

#define HeroInfoStructBuild(Abbr, AR, MR, HP, SEX, Name) \
    const struct heroInfo HeroPackageNormal::##Abbr = \
{ AR, MR, HP, SEX, Name }


HeroPackageNormal::HeroPackageNormal() {
    const struct HeroInfo msz  = {1, 4, 8,  sex_female,
                                  tr("MieShaZhe")};
    const struct HeroInfo ls   = {1, 2, 8,  sex_male,
                                  tr("LeiShen")};
    const struct HeroInfo bzsn = {1, 2, 8,  sex_female,
                                  tr("BingZhiShengNv")};
    const struct HeroInfo hwz  = {1, 2, 8,  sex_female,
                                  tr("HuoWuZhe")};
    const struct HeroInfo fxz  = {1, 3, 7,  sex_female,
                                  tr("FengXingZhe")};
    const struct HeroInfo hyzq = {1, 3, 8,  sex_female,
                                  tr("HuanYingZhiQiang")};
    const struct HeroInfo lhyz = {1, 3, 7,  sex_female,
                                  tr("LingHunYiZhe")};
    const struct HeroInfo dt   = {1, 4, 8,  sex_male,
                                  tr("DuTu")};
    const struct HeroInfo yy   = {1, 3, 8,  sex_male,
                                  tr("YingYan")};
    const struct HeroInfo shz  = {1, 4, 8,  sex_female,
                                  tr("ShiHunZhe")};
    const struct HeroInfo ayzr = {1, 4, 7,  sex_male,
                                  tr("AnYingZhiRen")};
    const struct HeroInfo rz   = {1, 4, 8,  sex_male,
                                  tr("RenZhe")};
    const struct HeroInfo xzlz = {1, 4, 8,  sex_male,
                                  tr("XueZhiLiZhua")};
    const struct HeroInfo qyz  = {1, 4, 8,  sex_male,
                                  tr("QiYueZhe")};
    const struct HeroInfo sqs  = {1, 3, 8,  sex_female,
                                  tr("ShengQiShi")};
    const struct HeroInfo zlzj = {1, 3, 9,  sex_male,
                                  tr("ZhanLanZhiJian")};
    const struct HeroInfo zkzs = {1, 3, 10, sex_male,
                                  tr("ZhongKaiZhanShi")};
    const struct HeroInfo ks   = {1, 3, 9,  sex_male,
                                  tr("KuangSha")};
    const struct HeroInfo ss   = {1, 3, 9,  sex_male,
                                  tr("SiShen")};
    const struct HeroInfo bx   = {1, 4, 8,  sex_male,
                                  tr("BaoXiong")};

    hil.append(msz);
    hil.append(ls);
    hil.append(bzsn);
    hil.append(hwz);
    hil.append(fxz);
    hil.append(hyzq);
    hil.append(lhyz);
    hil.append(dt);
    hil.append(yy);
    hil.append(shz);
    hil.append(ayzr);
    hil.append(rz);
    hil.append(xzlz);
    hil.append(qyz);
    hil.append(sqs);
    hil.append(zlzj);
    hil.append(zkzs);
    hil.append(ks);
    hil.append(ss);
    hil.append(bx);
}
