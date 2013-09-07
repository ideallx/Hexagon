#ifndef GAME_ITEMS_CARD_CARDENGINE_H_
#define GAME_ITEMS_CARD_CARDENGINE_H_

#include <QList>
#include <QString>
#include <QObject>
#include "enums.h"

class HandCard;
class GameBackInfo;

struct cardInfo {
    int cartType;
    QString name;
};

class CardEngine : public QObject {
 public:
    explicit CardEngine(GameBackInfo *gbi);
    QList<HandCard*> generateHandCards(int package = 0);
    QList<HandCard*> backCard(int num);

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

#endif  // GAME_ITEMS_CARD_CARDENGINE_H_
