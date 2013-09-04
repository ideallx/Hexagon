#include "cardengine.h"
#include "carditem.h"
#include "backinfo.h"

const struct cardInfo CardEngine::kb   = {KuangBao,
                                          tr("KuangBao")};
const struct cardInfo CardEngine::zy   = {ZheYue,
                                          tr("ZheYue")};
const struct cardInfo CardEngine::flrs = {FaLiRanShao,
                                          tr("FaLiRanShao")};
const struct cardInfo CardEngine::smlz = {ShengMingLiZan,
                                          tr("ShengMingLiZan")};
const struct cardInfo CardEngine::cs   = {ChuanSong,
                                          tr("ChuanSong")};
const struct cardInfo CardEngine::fyfw = {FangYuFuWen,
                                          tr("FangYuFuWen")};
const struct cardInfo CardEngine::ztjh = {ZhuangTaiJingHua,
                                          tr("ZhuangTaiJingHua")};
const struct cardInfo CardEngine::mfhd = {MoFaHuDun,
                                          tr("MoFaHuDun")};
const struct cardInfo CardEngine::mfzh = {MoFaZhiHeng,
                                          tr("MoFaZhiHeng")};
const struct cardInfo CardEngine::mjbd = {MoJingBaoDan,
                                          tr("MoJingBaoDan")};
const struct cardInfo CardEngine::nlxj = {NengLiangXianJing,
                                          tr("NengLiangXianJing")};
const struct cardInfo CardEngine::jb2  = {JinBi_2,
                                          tr("JinBi_2")};
const struct cardInfo CardEngine::jb3  = {JinBi_3,
                                          tr("JinBi_3")};
const struct cardInfo CardEngine::jb4  = {JinBi_4,
                                          tr("JinBi_4")};
const struct cardInfo CardEngine::zjj  = {ZhengJingJi,
                                          tr("ZhengJingJi")};
const struct cardInfo CardEngine::jjy  = {JiJiuYao,
                                          tr("JiJiuYao")};
const struct cardInfo CardEngine::sb   = {ShanBi,
                                          tr("ShanBi")};

CardEngine::CardEngine(GameBackInfo *gbi) {
    path = gbi->getConfigDir() + "cards/";
}

QList<HandCard*> CardEngine::generateHandCards(int package) {
    Q_UNUSED(package);
    QList<HandCard*> handList;
    int i = 0;

    for (i = 0; i < 2; i++) {
        handList.append(new HandCard(fyfw.cartType, path+fyfw.name+".jpg"));
        handList.append(new HandCard(jjy.cartType,  path+jjy.name+".jpg"));
        handList.append(new HandCard(ztjh.cartType, path+ztjh.name+".jpg"));
        handList.append(new HandCard(smlz.cartType, path+smlz.name+".jpg"));;
        handList.append(new HandCard(mfzh.cartType, path+mfzh.name+".jpg"));
        handList.append(new HandCard(flrs.cartType, path+flrs.name+".jpg"));
    }
    for (i = 0; i < 3; i++) {
        handList.append(new HandCard(sb.cartType,   path+sb.name+".jpg"));
        handList.append(new HandCard(jb2.cartType,  path+jb2.name+".jpg"));
        handList.append(new HandCard(nlxj.cartType, path+nlxj.name+".jpg"));
        handList.append(new HandCard(cs.cartType,   path+cs.name+".jpg"));
        handList.append(new HandCard(zy.cartType,   path+zy.name+".jpg"));
    }
    for (i = 0; i < 4; i++) {
        handList.append(new HandCard(mfhd.cartType, path+mfhd.name+".jpg"));
    }
    for (i = 0; i < 5; i++) {
        handList.append(new HandCard(kb.cartType,   path+kb.name+".jpg"));
    }
    for (i = 0; i < 6; i++) {
        handList.append(new HandCard(jb3.cartType,  path+jb3.name+".jpg"));
        handList.append(new HandCard(jb4.cartType,  path+jb4.name+".jpg"));
        handList.append(new HandCard(ztjh.cartType, path+ztjh.name+".jpg"));
        handList.append(new HandCard(mjbd.cartType, path+mjbd.name+".jpg"));
    }
    return handList;
}
