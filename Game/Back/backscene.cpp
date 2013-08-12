#include "backscene.h"
#include "itemcollector.h"
#include "heroitem.h"
#include "heroengine.h"
#include "backinfo.h"
#include "cardengine.h"
#include "coordinate.h"
#include "mapelement.h"


backScene::backScene(gameBackInfo* gbi, gameCoordinate *gc, QList<struct externInfo> i, QObject *parent) :
    gbi(gbi),
    gc(gc)
{
    this->setSceneRect(gbi->getPixmap().rect()-=QMargins(10, 10, 10, 10));
    QGraphicsPixmapItem *back = new QGraphicsPixmapItem();
    back->setPixmap(QPixmap(gbi->getPixmap()));
    back->setZValue(-10);
    this->addItem(back);

    ic = new itemCollector(gbi, gc, this);
    ic->setCardEngine(new cardEngine(gbi));
    ic->setHeroFactory(new heroFactory(gbi), i);
    ic->setMapElement(new mapEngine(gbi));
    ic->setCampHealth();

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
/*
    if(isPressing)
    {
        //TODO has Delay
        qDebug()<<sceneRect()<<event->scenePos()<<oldPointF;
        double xLength = - event->scenePos().x() + oldPointF.x();
        double yLength = - event->scenePos().y() + oldPointF.y();
        qDebug()<<xLength<<yLength;

        qDebug()<<sceneRect().x()+xLength<<sceneRect().y()+yLength;
        if((xLength+sceneRect().x()<0) ||
                (xLength + sceneRect().width() > this->gbi->getPixmap().width()))
            return;

        if((yLength+sceneRect().y()<0) ||
                (yLength + sceneRect().height() > this->gbi->getPixmap().height()))
            return;

        QPointF ff = event->scenePos();
//        setSceneRect(sceneRect().x() + xLength,
//                     sceneRect().y() + yLength,
//                     sceneRect().width(),
//                     sceneRect().height());


        oldPointF = ff;
        return;
    }
    */
    QPoint newPoint = gc->getCooxWithPos(event->scenePos());
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

    if(ic->isPointHasHero(oldPoint))
    {
        heroItem* hero = ic->getHeroByPoint(oldPoint);
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
    QString coordinate = tr("coordinates: ") + QString::number(gmeT->getPoint().x()) + tr(", ") + QString::number(gmeT->getPoint().y());
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
//        heroItem* hero = ic->getHeroByPoint(oldPoint);
        emit buildMenu(hi, this->views()[0]->mapFromScene(event->scenePos()));
//        if(ic->isLocalHero(hero))
//        {
//        }
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

    if(ic->isPointHasHero(oldPoint))
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
    rangeList = ic->listRange(hi, ModeAttack);
    for(int i=0; i<rangeList.size(); i++)
    {
        ic->setElementSpecialPen(rangeList.at(i), QPen(Qt::cyan, 5));
    }

}

QList<QString> backScene::getHeroListAvaterPath(char in)
{
    return ic->getHeroListAvaterPath(in);
}
