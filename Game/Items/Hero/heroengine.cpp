#include "heroitem.h"
#include "heroengine.h"
#include "backinfo.h"

HeroFactory::HeroFactory(GameBackInfo* gbi)
    : innerDir(gbi->getConfigDir() + "heros/"),
    lineLength(gbi->getLineLength()),
    scene(NULL),
    heroAmount(0) {
}

HeroItem* HeroFactory::createHero(struct externInfo ei) {
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

QList<HeroItem*> HeroFactory::generateHeroes(QList<struct externInfo> list) {
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

struct heroInfo HeroFactory::getHeroInfoByNum(int n) {
    for (int i = 0; i < hpl.size(); i++) {
        if (n > hpl[i]->heroNumInPackage()) {
            n -= hpl[i]->heroNumInPackage();
        } else {
            return hpl[i]->getHeroInfo(n);
        }
    }
    qDebug() << "Hero Num Wrong";
    struct heroInfo white = {2, 3, 9,  sex_male, tr("wrongHero")};
    return white;
}

#define HeroInfoStructBuild(Abbr, AR, MR, HP, SEX, Name) \
    const struct heroInfo HeroPackageNormal::##Abbr = \
{ AR, MR, HP, SEX, Name }


HeroPackageNormal::HeroPackageNormal() {
    const struct heroInfo msz  = {1, 4, 8,  sex_female,
                                  tr("mieShaZhe")};
    const struct heroInfo ls   = {1, 2, 8,  sex_male,
                                  tr("leiShen")};
    const struct heroInfo bzsn = {1, 2, 8,  sex_female,
                                  tr("bingZhiShengNv")};
    const struct heroInfo hwz  = {1, 2, 8,  sex_female,
                                  tr("huoWuZhe")};
    const struct heroInfo fxz  = {1, 3, 7,  sex_female,
                                  tr("fengXingZhe")};
    const struct heroInfo hyzq = {1, 3, 8,  sex_female,
                                  tr("huanYingZhiQiang")};
    const struct heroInfo lhyz = {1, 3, 7,  sex_female,
                                  tr("lingHunYiZhe")};
    const struct heroInfo dt   = {1, 4, 8,  sex_male,
                                  tr("duTu")};
    const struct heroInfo yy   = {1, 3, 8,  sex_male,
                                  tr("yingYan")};
    const struct heroInfo shz  = {1, 4, 8,  sex_female,
                                  tr("shiHunZhe")};
    const struct heroInfo ayzr = {1, 4, 7,  sex_male,
                                  tr("anYingZhiRen")};
    const struct heroInfo rz   = {1, 4, 8,  sex_male,
                                  tr("renZhe")};
    const struct heroInfo xzlz = {1, 4, 8,  sex_male,
                                  tr("xueZhiLiZhua")};
    const struct heroInfo qyz  = {1, 4, 8,  sex_male,
                                  tr("qiYueZhe")};
    const struct heroInfo sqs  = {1, 3, 8,  sex_female,
                                  tr("shengQiShi")};
    const struct heroInfo zlzj = {1, 3, 9,  sex_male,
                                  tr("zhanLanZhiJian")};
    const struct heroInfo zkzs = {1, 3, 10, sex_male,
                                  tr("zhongKaiZhanShi")};
    const struct heroInfo ks   = {1, 3, 9,  sex_male,
                                  tr("kuangSha")};
    const struct heroInfo ss   = {1, 3, 9,  sex_male,
                                  tr("siShen")};
    const struct heroInfo bx   = {1, 4, 8,  sex_male,
                                  tr("baoXiong")};

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
