#include "heroitem.h"
#include "heroengine.h"
#include "backinfo.h"

#define HeroInfoStructBuild(Abbr, AR, MR, HP, SEX, Name) \
	const struct heroInfo HeroPackageNormal::##Abbr = { AR, MR, HP, SEX, Name };

HeroInfoStructBuild(msz, 1, 2, 5, sex_male, "fsfsf");
//const struct heroInfo HeroPackageNormal::msz  = {1, 4, 8,  sex_female, tr("mieShaZhe")};
//const struct heroInfo ls   = {1, 2, 8,  sex_male,   tr("leiShen")};
//const struct heroInfo bzsn = {1, 2, 8,  sex_female, tr("bingZhiShengNv")};
//const struct heroInfo hwz  = {1, 2, 8,  sex_female, tr("huoWuZhe")};
//const struct heroInfo fxz  = {1, 3, 7,  sex_female, tr("fengXingZhe")};
//const struct heroInfo hyzq = {1, 3, 8,  sex_female, tr("huanYingZhiQiang")};
//const struct heroInfo lhyz = {1, 3, 7,  sex_female, tr("lingHunYiZhe")};
//const struct heroInfo dt   = {1, 4, 8,  sex_male,   tr("duTu")};
//const struct heroInfo yy   = {1, 3, 8,  sex_male,   tr("yingYan")};
//const struct heroInfo shz  = {1, 4, 8,  sex_female, tr("shiHunZhe")};
//const struct heroInfo ayzr = {1, 4, 7,  sex_male,   tr("anYingZhiRen")};
//const struct heroInfo rz   = {1, 4, 8,  sex_male,   tr("renZhe")};
//const struct heroInfo xzlz = {1, 4, 8,  sex_male,   tr("xueZhiLiZhua")};
//const struct heroInfo qyz  = {1, 4, 8,  sex_male,   tr("qiYueZhe")};
//const struct heroInfo sqs  = {1, 3, 8,  sex_female, tr("shengQiShi")};
//const struct heroInfo zlzj = {1, 3, 9,  sex_male,   tr("zhanLanZhiJian")};
//const struct heroInfo zkzs = {1, 3, 10, sex_male,   tr("zhongKaiZhanShi")};
//const struct heroInfo ks   = {1, 3, 9,  sex_male,   tr("kuangSha")};
//const struct heroInfo ss   = {1, 3, 9,  sex_male,   tr("siShen")};
//const struct heroInfo bx   = {1, 4, 8,  sex_male,   tr("baoXiong")};

heroFactory::heroFactory(gameBackInfo* gbi):
    innerDir(gbi->getConfigDir() + "heros/"),
    lineLength(gbi->getLineLength())
{
    //heroInfoMap[MieShaZhe] = msz;
    //heroInfoMap[RenZhe] = rz;
    //heroInfoMap[AnYingZhiRen] = ayzr;
    //heroInfoMap[LeiShen] = ls;
    //heroInfoMap[ShengQiShi] = sqs;
    //heroInfoMap[KuangSha] = ks;
    //heroInfoMap[YingYan] = yy;
    //heroInfoMap[LingHunYiZhe] = lhyz;
    //heroInfoMap[BingZhiShengNv] = bzsn;
    //heroInfoMap[ZhongKaiZhanShi] = zkzs;
    //heroInfoMap[QiYueZhe] = qyz;
    //heroInfoMap[BaoXiong] = bx;
    //heroInfoMap[ShiHunZhe] = shz;
    //heroInfoMap[FengXingZhe] = fxz;
    //heroInfoMap[DuTu] = dt;
    //heroInfoMap[XueZhiLiZhua] = xzlz;
    //heroInfoMap[SiShen] = ss;
    //heroInfoMap[HuanYingZhiQiang] = hyzq;
    //heroInfoMap[ZhanLanZhiJian] = zlzj;
    //heroInfoMap[HuoWuZhe] = hwz;
}

heroItem* heroFactory::createHero(enum heroNum_t hero, QPoint pt, enum camp_t c)
{
    heroItem * item = new heroItem(lineLength);
    item->setAvaterPic(new QPixmap(innerDir + heroInfoMap[hero].heroName + "_Head.png"));
    item->setwholePic(new QPixmap(innerDir + heroInfoMap[hero].heroName + "_Whole.png"));
    item->setBrush(item->avaterPic()->scaledToWidth(item->rect().width(), Qt::SmoothTransformation));
    item->setHeroProperty(heroInfoMap[hero].sexual, heroInfoMap[hero].attackRange, heroInfoMap[hero].moveRange, heroInfoMap[hero].healthMax);
    item->setHeroName(heroInfoMap[hero].heroName);
    item->setPoint(pt);
    item->setCamp(c);
    return item;
}

QList<heroItem*> heroFactory::generateHeroes(QList<struct externInfo> list)
{
    QList<heroItem*> result;
    for(int i=0; i<list.size(); i++)
    {
        result.append(createHero(list[i].h, list[i].p, list[i].c));
    }
    return result;
}

QPixmap heroFactory::getHeroAvaterByNum(int n)
{
	return QPixmap(innerDir + heroInfoMap[(enum heroNum_t)n].heroName + "_Head.png");
}