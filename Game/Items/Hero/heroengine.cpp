#include "heroitem.h"
#include "heroengine.h"
#include "backinfo.h"

const struct heroInfo heroFactory::msz  = {1, 4, 8,  sex_female, tr("mieShaZhe")};
const struct heroInfo heroFactory::ls   = {1, 2, 8,  sex_male,   tr("leiShen")};
const struct heroInfo heroFactory::bzsn = {1, 2, 8,  sex_female, tr("bingZhiShengNv")};
const struct heroInfo heroFactory::hwz  = {1, 2, 8,  sex_female, tr("huoWuZhe")};
const struct heroInfo heroFactory::fxz  = {1, 3, 7,  sex_female, tr("fengXingZhe")};
const struct heroInfo heroFactory::hyzq = {1, 3, 8,  sex_female, tr("huanYingZhiQiang")};
const struct heroInfo heroFactory::lhyz = {1, 3, 7,  sex_female, tr("lingHunYiZhe")};
const struct heroInfo heroFactory::dt   = {1, 4, 8,  sex_male,   tr("duTu")};
const struct heroInfo heroFactory::yy   = {1, 3, 8,  sex_male,   tr("yingYan")};
const struct heroInfo heroFactory::shz  = {1, 4, 8,  sex_female, tr("shiHunZhe")};
const struct heroInfo heroFactory::ayzr = {1, 4, 7,  sex_male,   tr("anYingZhiRen")};
const struct heroInfo heroFactory::rz   = {1, 4, 8,  sex_male,   tr("renZhe")};
const struct heroInfo heroFactory::xzlz = {1, 4, 8,  sex_male,   tr("xueZhiLiZhua")};
const struct heroInfo heroFactory::qyz  = {1, 4, 8,  sex_male,   tr("qiYueZhe")};
const struct heroInfo heroFactory::sqs  = {1, 3, 8,  sex_female, tr("shengQiShi")};
const struct heroInfo heroFactory::zlzj = {1, 3, 9,  sex_male,   tr("zhanLanZhiJian")};
const struct heroInfo heroFactory::zkzs = {1, 3, 10, sex_male,   tr("zhongKaiZhanShi")};
const struct heroInfo heroFactory::ks   = {1, 3, 9,  sex_male,   tr("kuangSha")};
const struct heroInfo heroFactory::ss   = {1, 3, 9,  sex_male,   tr("siShen")};
const struct heroInfo heroFactory::bx   = {1, 4, 8,  sex_male,   tr("baoXiong")};

heroFactory::heroFactory(gameBackInfo* gbi):
    innerDir(gbi->getConfigDir() + "heros/"),
    lineLength(gbi->getLineLength())
{
    heroInfoMap[MieShaZhe] = msz;
    heroInfoMap[RenZhe] = rz;
    heroInfoMap[AnYingZhiRen] = ayzr;
    heroInfoMap[LeiShen] = ls;
    heroInfoMap[ShengQiShi] = sqs;
    heroInfoMap[KuangSha] = ks;
    heroInfoMap[YingYan] = yy;
    heroInfoMap[LingHunYiZhe] = lhyz;
    heroInfoMap[BingZhiShengNv] = bzsn;
    heroInfoMap[ZhongKaiZhanShi] = zkzs;
    heroInfoMap[QiYueZhe] = qyz;
    heroInfoMap[BaoXiong] = bx;
    heroInfoMap[ShiHunZhe] = shz;
    heroInfoMap[FengXingZhe] = fxz;
    heroInfoMap[DuTu] = dt;
    heroInfoMap[XueZhiLiZhua] = xzlz;
    heroInfoMap[SiShen] = ss;
    heroInfoMap[HuanYingZhiQiang] = hyzq;
    heroInfoMap[ZhanLanZhiJian] = zlzj;
    heroInfoMap[HuoWuZhe] = hwz;
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
