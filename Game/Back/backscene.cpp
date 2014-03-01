#include "backscene.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "heroengine.h"
#include "cardengine.h"
#include "mapelement.h"
#include "QEventLoop"

BackScene::BackScene(ItemCollector *ic, QObject *parent)
    :ic(ic) {
    this->setSceneRect(ic->getPixmap().rect()-=QMargins(10, 10, 10, 10));
    QGraphicsPixmapItem *back = new QGraphicsPixmapItem();
    back->setPixmap(QPixmap(ic->getPixmap()));
    back->setZValue(-10);
    this->addItem(back);
    isPressing = false;
    oldPoint = ic->outPoint();
}

BackScene::~BackScene() {
    delete ic;
}

void BackScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QStringList strList;
    QPoint newPoint = ic->getCooxWithPos(event->scenePos());
    if (!ic->isPointAvailable(newPoint)) {
        emit changeStatusBar(strList);
        newPoint = ic->outPoint();
        restoreOldPoint(oldPoint);
        if (oldPoint != newPoint) {
            oldPoint = newPoint;
        }
        return;
    }
    if (oldPoint == newPoint) {
        return;
    }
    restoreOldPoint(oldPoint);

    if (newPoint == ic->outPoint()) {
        ic->setElementRestorePen(oldPoint);
    }

    ic->setElementBoldPen(newPoint, 5);
    oldPoint = newPoint;

    GameMapElement* gmeT = ic->getMapElementByPoint(newPoint);

    if (HeroItem* hero = ic->getHeroByPoint(oldPoint)) {
        QString strHero = tr("hero: ") + hero->heroName();
        strList.append(strHero);
        emit heroMovedIn(hero);
    } else {
        QString strGme = tr("area: ") + gmeT->getElementName();
        strList.append(strGme);
        emit mapElementMovedIn(oldPoint);
    }
    QString coordinate = tr("coordinates: ") +
            QString::number(gmeT->point().x()) + tr(", ") +
            QString::number(gmeT->point().y());
    strList.append(coordinate);
    emit changeStatusBar(strList);
}


void BackScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    isPressing = false;
}


void BackScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    HeroItem* hi = ic->getHeroByPoint(oldPoint);
    if (hi != NULL) {
        emit buildMenu(hi, this->views()[0]->mapFromScene(event->scenePos()));
    }
}

void BackScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    isPressing = true;
    oldPointF = event->scenePos();

    if (rangeList.contains(oldPoint)) {
        emit rangeClicked(oldPoint);
        emit mapElementClicked(oldPoint);
        return;
    }

    if (ic->getHeroByPoint(oldPoint)) {
        HeroItem* hero = ic->getHeroByPoint(oldPoint);
        emit heroClicked(hero);
    } else {
        emit mapElementClicked(oldPoint);
    }
}

void BackScene::showMoveRange(HeroItem* hi) {
    if (hi == NULL)
        return;
    rangeList = ic->listRange(hi, RangeMode::ModeMove);

    for (int i = 0; i < rangeList.size(); i++) {
        ic->setElementSpecialPen(rangeList.at(i), QPen(Qt::yellow, 5));
    }
}

void BackScene::clearRange() {
    for (int i = 0; i < rangeList.size(); i++) {
        ic->setElementDefaultPen(rangeList.at(i));
    }
    rangeList.clear();
}


void BackScene::showAttackRange(HeroItem* hi) {
    rangeList.clear();
    rangeList = ic->listRange(hi, RangeMode::ModeAttack);
    for (int i = 0; i < rangeList.size(); i++) {
        ic->setElementSpecialPen(rangeList.at(i), QPen(Qt::red, 5));
    }
}

void BackScene::showSkillRange(HeroItem* hi, MapRangeType t, int range) {
    rangeList.clear();

    if (range < 0) {
        rangeList = ic->listAllMap();
    } else {
        rangeList = ic->listSpecialRange(hi->point(), t, range);
    }

    for (int i = 0; i < rangeList.size(); i++) {
        ic->setElementSpecialPen(rangeList.at(i), QPen(Qt::cyan, 5));
    }
}

void BackScene::showRangePoints(QList<QPoint> lp) {
    rangeList.clear();
    rangeList = lp;
    foreach(QPoint p, rangeList) {
        ic->setElementSpecialPen(p, QPen(Qt::cyan, 5));
    }
}

QList<QString> BackScene::getHeroListAvaterPath(Camp c) {
    return ic->getHeroListAvaterPath(c);
}

void BackScene::showBirthSquare(Camp c, QList<QPoint> unshow) {
    rangeList.clear();
    QList<GameMapElement*> l;
    if (c == Camp::CampBlue) {
        l = ic->getBlueTeamCamp();
    } else if (c == Camp::CampRed) {
        l = ic->getRedTeamCamp();
    }

    for (int i = 0; i < l.size(); i++) {
        if (unshow.contains(l[i]->point()))
            continue;
        rangeList.append(l[i]->point());
    }
    for (int i = 0; i < rangeList.size(); i++) {
        ic->setElementSpecialPen(rangeList.at(i), QPen(Qt::cyan, 5));
    }
    this->views()[0]->centerOn(
                ic->getBeginPosOfHero(rangeList[0]));
}

void BackScene::restoreOldPoint(QPoint old) {
    if (rangeList.contains(old))
        ic->setElementRestorePen(old);
    else
        ic->setElementDefaultPen(old);
}

QList<QPoint> BackScene::getSkillRange(QPoint o,
                                       MapRangeType t,
                                       int range) {
    QList<QPoint> list;
    list = ic->listSpecialRange(o, t, range);
    return list;
}
