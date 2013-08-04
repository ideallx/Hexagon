#ifndef CARDENGINE_H
#define CARDENGINE_H

#include <QtWidgets>
#include "carditem.h"
#include "backinfo.h"

struct cardInfo
{
    int cartType;
    QString name;
};

class cardEngine : public QObject
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


    cardEngine(gameBackInfo *gbi);
    QList<handCard*> generateHandCards(int package = 0);

private:
    static const struct cardInfo kb;
    static const struct cardInfo zy;
    static const struct cardInfo flrs;
    static const struct cardInfo smlz;
    static const struct cardInfo cs;
    static const struct cardInfo fyfw;
    static const struct cardInfo ztjh;
    static const struct cardInfo mfhd;
    static const struct cardInfo mfzh;
    static const struct cardInfo mjbd;
    static const struct cardInfo nlxj;
    static const struct cardInfo jb2;
    static const struct cardInfo jb3;
    static const struct cardInfo jb4;
    static const struct cardInfo zjj;
    static const struct cardInfo jjy;
    static const struct cardInfo sb;
    QString path;
};


#endif // CARDENGINE_H
