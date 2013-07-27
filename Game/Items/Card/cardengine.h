#ifndef CARDENGINE_H
#define CARDENGINE_H

#include <QtWidgets>
#include "carditem.h"

class cardEngine
{
public:
    enum cardType_t
    {
        KuangBao,
        ZheYue,
        FaLiRanShao,
        ShengMingLiZan,
        ChuanSong,
        FangYuFuWen,
        ZhuangTaiJingHua,
        MoFaHuDun,
        MoFaZhiHeng,
        MoJingBaoDan,
        NengLiangXianJing,
        JinBi_2,
        JinBi_3,
        JinBi_4,
        ZhengJingJi,
        JiJiuYao,
        ShanBi,

        PackageII,

        UserDefined
    };


    cardEngine();
    QList<handCard*> generateHandCards(int package = 0);

private:
    QList<handCard*> handList;
};


#endif // CARDENGINE_H
