#include "heroitem.h"
#include "heroengine.h"
#include "backinfo.h"
#include "eventcenter.h"
#include "carditem.h"

HeroFactory::HeroFactory(GameBackInfo* gbi)
    : scene(NULL),
    innerDir(gbi->getConfigDir() + "heros/"),
    lineLength(gbi->getLineLength()),
    heroAmount(0) {
}

HeroItem* HeroFactory::createHero(ExternInfo ei) {
    HeroItem * item = new HeroItem(lineLength);
    QString temp = innerDir +
            getHeroInfoByNum(ei.h).heroName +
            "_Head.jpg";
    item->setAvaterPic(new QPixmap(temp));
    item->setwholePic(QString(innerDir +
                              getHeroInfoByNum(ei.h).heroName +
                              "_Whole.png"));
    item->setSkillPics(QString(innerDir + "skill_icons/" +
                               getHeroInfoByNum(ei.h).heroName +
                               "SI*.png"));
    item->setBrush(item->avaterPic()->scaledToWidth(item->rect().width(),
                                                    Qt::SmoothTransformation));
    item->setHeroProperty(getHeroInfoByNum(ei.h));
    item->setHeroName(getHeroInfoByNum(ei.h).heroName);
    item->setPoint(ei.p);
    item->setCamp(ei.c);
    return item;
}

QList<HeroItem*> HeroFactory::generateHeroes(QList<ExternInfo> list) {
    QList<HeroItem*> result;
    for (int i = 0; i < list.size(); i++) {
        result.append(createHero(list[i]));
    }
    return result;
}

void HeroFactory::addPackage(AbstractHeroPacakage* ahp) {
    hpl.append(ahp);
    heroAmount += ahp->heroNumInPackage();
}

HeroInfo HeroFactory::getHeroInfoByNum(HeroNum hn) {
    int n = static_cast<int>(hn);
    for (int i = 0; i < hpl.size(); i++) {
        if (n > hpl[i]->heroNumInPackage()) {
            n -= hpl[i]->heroNumInPackage();
        } else {
            return hpl[i]->getHeroInfo(n);
        }
    }
    qDebug() << "Hero Num Wrong";
    HeroInfo white = {2, 3, 9,  Sexual::SexMale, tr("wrongHero")};
    return white;
}
