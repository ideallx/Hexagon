#include "cardengine.h"
#include "carditem.h"
#include "backinfo.h"
#include "heroitem.h"

CardPackageNormal::CardPackageNormal() {
    const struct CardInfo kb   = {KuangBao, CardPackage_Normal, 0,
                                  tr("KuangBao")};
    const struct CardInfo zy   = {ZheYue, CardPackage_Normal, 0,
                                  tr("ZheYue")};
    const struct CardInfo flrs = {FaLiRanShao, CardPackage_Normal, 0,
                                  tr("FaLiRanShao")};
    const struct CardInfo smlz = {ShengMingLiZan, CardPackage_Normal, 0,
                                  tr("ShengMingLiZan")};
    const struct CardInfo cs   = {ChuanSong, CardPackage_Normal, 0,
                                  tr("ChuanSong")};
    const struct CardInfo fyfw = {FangYuFuWen, CardPackage_Normal, 0,
                                  tr("FangYuFuWen")};
    const struct CardInfo ztjh = {ZhuangTaiJingHua, CardPackage_Normal, 0,
                                  tr("ZhuangTaiJingHua")};
    const struct CardInfo mfhd = {MoFaHuDun, CardPackage_Normal, 0,
                                  tr("MoFaHuDun")};
    const struct CardInfo mfzh = {MoFaZhiHeng, CardPackage_Normal, 0,
                                  tr("MoFaZhiHeng")};
    const struct CardInfo mjbd = {MoJingBaoDan, CardPackage_Normal, 0,
                                  tr("MoJingBaoDan")};
    const struct CardInfo nlxj = {NengLiangXianJing, CardPackage_Normal, 0,
                                  tr("NengLiangXianJing")};
    const struct CardInfo jb2  = {JinBi_2, CardPackage_Normal, 0,
                                  tr("JinBi_2")};
    const struct CardInfo jb3  = {JinBi_3, CardPackage_Normal, 0,
                                  tr("JinBi_3")};
    const struct CardInfo jb4  = {JinBi_4,  CardPackage_Normal, 0,
                                  tr("JinBi_4")};
    const struct CardInfo zjj  = {ZhengJingJi, CardPackage_Normal, 0,
                                  tr("ZhengJingJi")};
    const struct CardInfo jjy  = {JiJiuYao, CardPackage_Normal, 0,
                                  tr("JiJiuYao")};
    const struct CardInfo sb   = {ShanBi, CardPackage_Normal, 0,
                                  tr("ShanBi")};

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
      cardsId(0),
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
    return new HandCard(ci.cardType, cardsId++, path+ci.name+".jpg");
}

//QList<HandCard*> CardEngine::backCard(int num) {
//    QList<HandCard*> handList;
//    for (int i = 0; i < num; i++) {
//        handList.append(new HandCard(BACK, path + "back.png"));
//    }
//    return handList;
//}

void CardEngine::addPackage(AbstractCardPackage* acp) {
    cpl.append(acp);
    cardAmount += acp->cardNumInPackage();
}

CsKuangBao::CsKuangBao()
    : AttackBuffSkill(AttackBuffAddDamage, 1){
    setObjectName("KuangBao");
}

void CsKuangBao::skillAct(HeroItem *from, HeroItem *to) {
    to->setHealth(to->health()-1);
}
