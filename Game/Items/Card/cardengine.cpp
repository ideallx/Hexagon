#include "cardengine.h"

cardEngine::cardEngine()
{
}

QList<handCard*> cardEngine::generateHandCards(int package)
{
    Q_UNUSED(package);
    int i=0;

    for(i=0; i<2; i++)
    {
        handList.append(new handCard(FangYuFuWen));
        handList.append(new handCard(ShanBi));
        handList.append(new handCard(JiJiuYao));
        handList.append(new handCard(ZhuangTaiJingHua));
        handList.append(new handCard(ShengMingLiZan));
        handList.append(new handCard(MoFaZhiHeng));
        handList.append(new handCard(FaLiRanShao));
    }
    for(i=0; i<3; i++)
    {
        handList.append(new handCard(JinBi_2));
        handList.append(new handCard(NengLiangXianJing));
        handList.append(new handCard(ChuanSong));
        handList.append(new handCard(ZheYue));
    }
    for(i=0; i<4; i++)
    {
        handList.append(new handCard(MoFaHuDun));
    }
    for(i=0; i<5; i++)
    {
        handList.append(new handCard(KuangBao));
    }
    for(i=0; i<6; i++)
    {
        handList.append(new handCard(JinBi_3));
        handList.append(new handCard(JinBi_4));
        handList.append(new handCard(ZhengJingJi));
        handList.append(new handCard(MoJingBaoDan));
    }
    return handList;
}
