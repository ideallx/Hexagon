#include "cardengine.h"
#include "carditem.h"
#include "backinfo.h"

CardPackageNormal::CardPackageNormal() {
    const struct CardInfo kb   = {KuangBao,          tr("KuangBao")};
    const struct CardInfo zy   = {ZheYue,            tr("ZheYue")};
    const struct CardInfo flrs = {FaLiRanShao,       tr("FaLiRanShao")};
    const struct CardInfo smlz = {ShengMingLiZan,    tr("ShengMingLiZan")};
    const struct CardInfo cs   = {ChuanSong,         tr("ChuanSong")};
    const struct CardInfo fyfw = {FangYuFuWen,       tr("FangYuFuWen")};
    const struct CardInfo ztjh = {ZhuangTaiJingHua,  tr("ZhuangTaiJingHua")};
    const struct CardInfo mfhd = {MoFaHuDun,         tr("MoFaHuDun")};
    const struct CardInfo mfzh = {MoFaZhiHeng,       tr("MoFaZhiHeng")};
    const struct CardInfo mjbd = {MoJingBaoDan,      tr("MoJingBaoDan")};
    const struct CardInfo nlxj = {NengLiangXianJing, tr("NengLiangXianJing")};
    const struct CardInfo jb2  = {JinBi_2,           tr("JinBi_2")};
    const struct CardInfo jb3  = {JinBi_3,           tr("JinBi_3")};
    const struct CardInfo jb4  = {JinBi_4,           tr("JinBi_4")};
    const struct CardInfo zjj  = {ZhengJingJi,       tr("ZhengJingJi")};
    const struct CardInfo jjy  = {JiJiuYao,          tr("JiJiuYao")};
    const struct CardInfo sb   = {ShanBi,            tr("ShanBi")};

    int i = 0;

    for (i = 0; i < 2; i++) {
        cil.append(fyfw);
        cil.append(jjy);
        cil.append(zjj);
        cil.append(smlz);
        cil.append(mfzh);
        cil.append(flrs);
    }
    for (i = 0; i < 3; i++) {
        cil.append(sb);
        cil.append(jb2);
        cil.append(nlxj);
        cil.append(cs);
        cil.append(zy);
    }
    for (i = 0; i < 4; i++) {
        cil.append(mfhd);
    }
    for (i = 0; i < 5; i++) {
        cil.append(kb);
    }
    for (i = 0; i < 6; i++) {
        cil.append(jb3);
        cil.append(jb4);
        cil.append(ztjh);
        cil.append(mjbd);
    }
}


CardEngine::CardEngine(GameBackInfo *gbi)
    : cardAmount(0),
    path(gbi->getConfigDir() + "cards/") {
}

QList<HandCard*> CardEngine::generateHandCards() {
    QList<HandCard*> result;
    for (int i = 0; i < cpl.size(); i++) {
        QList<struct CardInfo> hcl = cpl[i]->getAllCards();
        for (int j = 0; j < hcl.size(); j++) {
            result.append(createCard(hcl[j]));
        }
    }
    return result;
}

HandCard* CardEngine::createCard(struct CardInfo ci) {
    return new HandCard(ci.cartType, path+ci.name+".jpg");
}

QList<HandCard*> CardEngine::backCard(int num) {
    QList<HandCard*> handList;
    for (int i = 0; i < num; i++) {
        handList.append(new HandCard(BACK, path + "back.png"));
    }
    return handList;
}

void CardEngine::addPackage(AbstractCardPackage* acp) {
    cpl.append(acp);
    cardAmount += acp->cardNumInPackage();
}
