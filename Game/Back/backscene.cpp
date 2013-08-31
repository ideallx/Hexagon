#include "backscene.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "heroengine.h"
#include "cardengine.h"
#include "mapelement.h"
#include "skillcenter.h"


backScene::backScene(itemCollector *ic, QObject *parent) :
    ic(ic)
{
    this->setSceneRect(ic->getPixmap().rect()-=QMargins(10, 10, 10, 10));
    QGraphicsPixmapItem *back = new QGraphicsPixmapItem();
    back->setPixmap(QPixmap(ic->getPixmap()));
    back->setZValue(-10);
    this->addItem(back);
    this->setParent(parent);
    isPressing = false;
}

backScene::~backScene()
{
    delete ic;
}

void backScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QStringList strList;
    QPoint newPoint = ic->getCooxWithPos(event->scenePos());
    if(!ic->isPointAvailable(newPoint))
    {
        emit changeStatusBar(strList);
        newPoint = QPoint(-1, -1);
        ic->setElementDefaultPen(oldPoint);
        oldPoint = newPoint;
        return;
    }
    if(oldPoint == newPoint)
    {
        return;
    }
    if(rangeList.contains(oldPoint))
        ic->setElementRestorePen(oldPoint);
    else
        ic->setElementDefaultPen(oldPoint);

    ic->setElementBoldPen(newPoint, 5);
    oldPoint = newPoint;

    gameMapElement* gmeT = ic->getMapElementByPoint(newPoint);

    if(heroItem* hero = ic->getHeroByPoint(oldPoint))
    {
        QString strHero = tr("hero: ") + hero->heroName();
        strList.append(strHero);
        emit heroClicked(hero);
    }
    else
    {
        QString strGme = tr("area: ") + gmeT->getElementName();
        strList.append(strGme);
        emit mapElementMovedIn(oldPoint);
    }
    QString coordinate = tr("coordinates: ") + QString::number(gmeT->point().x()) + tr(", ") + QString::number(gmeT->point().y());
    strList.append(coordinate);
    emit changeStatusBar(strList);
}


void backScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    isPressing = false;

}


void backScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    heroItem* hi;
    if(hi = ic->getHeroByPoint(oldPoint))
    {
        emit buildMenu(hi, this->views()[0]->mapFromScene(event->scenePos()));
    }
}

void backScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"Screen"<<event->screenPos();
//    qDebug()<<"Scene "<<event->scenePos();
//    qDebug()<<"View  "<<this->views()[0]->mapFromScene(event->scenePos());

    isPressing = true;
    oldPointF = event->scenePos();

    if(rangeList.contains(oldPoint))
    {
        emit rangeClicked(oldPoint);
        return;
    }

    if(ic->getHeroByPoint(oldPoint))
    {
        heroItem* hero = ic->getHeroByPoint(oldPoint);
        emit heroClicked(hero);
    }
    else
    {
        emit mapElementClicked(oldPoint);
    }
}

void backScene::showMoveRange(heroItem* hi)
{
    if(hi == NULL)
        return;
    rangeList = ic->listRange(hi, ModeMove);
    for(int i=0; i<rangeList.size(); i++)
    {
        ic->setElementSpecialPen(rangeList.at(i), QPen(Qt::yellow, 5));
    }
}

void backScene::clearRange()
{
    for(int i=0; i<rangeList.size(); i++)
    {
        ic->setElementDefaultPen(rangeList.at(i));
    }
    rangeList.clear();
}


void backScene::showAttackRange(heroItem* hi)
{
    rangeList.clear();
    rangeList = ic->listRange(hi, ModeAttack);
    for(int i=0; i<rangeList.size(); i++)
    {
        ic->setElementSpecialPen(rangeList.at(i), QPen(Qt::red, 5));
    }
}

void backScene::showSkillRange(heroItem* hi, enum mapRangeType_t t, int range)
{
    rangeList.clear();
    rangeList = ic->listRange(hi, ModeMove);
    for(int i=0; i<rangeList.size(); i++)
    {
        ic->setElementSpecialPen(rangeList.at(i), QPen(Qt::cyan, 5));
    }

}

QList<QString> backScene::getHeroListAvaterPath(char in)
{
    return ic->getHeroListAvaterPath(in);
}
