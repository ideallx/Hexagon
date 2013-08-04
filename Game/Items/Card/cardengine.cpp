#include "cardengine.h"

const struct cardInfo cardEngine::kb   = {cardEngine::KuangBao,          tr("KuangBao")};
const struct cardInfo cardEngine::zy   = {cardEngine::ZheYue,            tr("ZheYue")};
const struct cardInfo cardEngine::flrs = {cardEngine::FaLiRanShao,       tr("FaLiRanShao")};
const struct cardInfo cardEngine::smlz = {cardEngine::ShengMingLiZan,    tr("ShengMingLiZan")};
const struct cardInfo cardEngine::cs   = {cardEngine::ChuanSong,         tr("ChuanSong")};
const struct cardInfo cardEngine::fyfw = {cardEngine::FangYuFuWen,       tr("FangYuFuWen")};
const struct cardInfo cardEngine::ztjh = {cardEngine::ZhuangTaiJingHua,  tr("ZhuangTaiJingHua")};
const struct cardInfo cardEngine::mfhd = {cardEngine::MoFaHuDun,         tr("MoFaHuDun")};
const struct cardInfo cardEngine::mfzh = {cardEngine::MoFaZhiHeng,       tr("MoFaZhiHeng")};
const struct cardInfo cardEngine::mjbd = {cardEngine::MoJingBaoDan,      tr("MoJingBaoDan")};
const struct cardInfo cardEngine::nlxj = {cardEngine::NengLiangXianJing, tr("NengLiangXianJing")};
const struct cardInfo cardEngine::jb2  = {cardEngine::JinBi_2,           tr("JinBi_2")};
const struct cardInfo cardEngine::jb3  = {cardEngine::JinBi_3,           tr("JinBi_3")};
const struct cardInfo cardEngine::jb4  = {cardEngine::JinBi_4,           tr("JinBi_4")};
const struct cardInfo cardEngine::zjj  = {cardEngine::ZhengJingJi,       tr("ZhengJingJi")};
const struct cardInfo cardEngine::jjy  = {cardEngine::JiJiuYao,          tr("JiJiuYao")};
const struct cardInfo cardEngine::sb   = {cardEngine::ShanBi,            tr("ShanBi")};

cardEngine::cardEngine(gameBackInfo *gbi)
{
    path = gbi->getConfigDir() + "cards/";
}

QList<handCard*> cardEngine::generateHandCards(int package)
{
    Q_UNUSED(package);
    QList<handCard*> handList;
    int i=0;

    for(i=0; i<2; i++)
    {
        handList.append(new handCard(fyfw.cartType, path+fyfw.name+".jpg"));
        handList.append(new handCard(jjy.cartType,  path+jjy.name+".jpg"));
        handList.append(new handCard(ztjh.cartType, path+ztjh.name+".jpg"));
        handList.append(new handCard(smlz.cartType, path+smlz.name+".jpg"));;
        handList.append(new handCard(mfzh.cartType, path+mfzh.name+".jpg"));
        handList.append(new handCard(flrs.cartType, path+flrs.name+".jpg"));
    }
    for(i=0; i<3; i++)
    {
        handList.append(new handCard(sb.cartType,   path+sb.name+".jpg"));
        handList.append(new handCard(jb2.cartType,  path+jb2.name+".jpg"));
        handList.append(new handCard(nlxj.cartType, path+nlxj.name+".jpg"));
        handList.append(new handCard(cs.cartType,   path+cs.name+".jpg"));
        handList.append(new handCard(zy.cartType,   path+zy.name+".jpg"));
    }
    for(i=0; i<4; i++)
    {
        handList.append(new handCard(mfhd.cartType, path+mfhd.name+".jpg"));
    }
    for(i=0; i<5; i++)
    {
        handList.append(new handCard(kb.cartType,   path+kb.name+".jpg"));
    }
    for(i=0; i<6; i++)
    {
        handList.append(new handCard(jb3.cartType,  path+jb3.name+".jpg"));
        handList.append(new handCard(jb4.cartType,  path+jb4.name+".jpg"));
        handList.append(new handCard(ztjh.cartType, path+ztjh.name+".jpg"));
        handList.append(new handCard(mjbd.cartType, path+mjbd.name+".jpg"));
    }
    return handList;
}
