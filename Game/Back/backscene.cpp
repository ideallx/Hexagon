#include "backscene.h"

backScene::backScene(gameBackInfo* gbi, gameCoordinate *gc, QList<heroFactory::ExternInfo> i, QObject *parent) :
    gbi(gbi),
    gc(gc)
{
    this->setSceneRect(gbi->getPixmap().rect());

    ic = new itemCollector(gbi, gc, this);
    ic->setCardEngine(new cardEngine());
    ic->setHeroFactory(new heroFactory(gbi), i);
    ic->setMapElement();

//    QGraphicsRectItem* rect = new QGraphicsRectItem();
//    rect->setRect(0, 0, 200, 200);
//    rect->setPen(QPen(Qt::black, 5));//??
//    this->addItem(rect);

    this->setParent(parent);
}

void backScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QStringList strList;
    QPoint newPoint = gc->getCooxWithPos(event->scenePos());
    if(!ic->isPointAvailable(newPoint))
    {
        emit changeStatusBar(strList);
        newPoint = QPoint(-1, -1);
        ic->setElementRestorePen(oldPoint);
        oldPoint = newPoint;
        return;
    }
    if(oldPoint == newPoint)
    {
        return;
    }
    if(sphereList.contains(oldPoint))
        ic->setElementRestorePen(oldPoint);
    else
        ic->setElementDefaultPen(oldPoint);

    ic->setElementBoldPen(newPoint, 5);
    oldPoint = newPoint;

    gameMapElement* gmeT = ic->getMapElementByPoint(newPoint);

    if(ic->isPointHasHero(oldPoint))
    {
        heroItem* hero = ic->getHeroByPoint(oldPoint);
        QString strHero = tr("hero: ") + hero->getHeroName();
        strList.append(strHero);
        emit heroMovedIn(oldPoint);
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

bool backScene::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);
    Q_UNUSED(event);
    return false;
}

void backScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event->scenePos().x()<<event->scenePos().y();
    if(ic->isPointHasHero(oldPoint))
    {
        qDebug("df");
        if(ic->localHero().contains(ic->getHeroByPoint(oldPoint)))
            emit localHeroClicked(event->scenePos());
        else
            emit heroClicked(oldPoint);
    }
    else
    {
        emit mapElementClicked(oldPoint);
    }
}

void backScene::showMoveSphere()
{
    heroItem* hi = ic->getHeroByPoint(oldPoint);
    sphereList = ic->listSphere(oldPoint, hi->getMoveSphere(), 'm');
    for(int i=0; i<sphereList.size(); i++)
    {
        ic->setElementSpecialPen(sphereList.at(i), QPen(Qt::yellow, 5));
    }
}

void backScene::clearSphere()
{
    for(int i=0; i<sphereList.size(); i++)
    {
        ic->setElementDefaultPen(sphereList.at(i));
    }
    sphereList.clear();
}


void backScene::showAttackSphere()
{
    heroItem* hi = ic->getHeroByPoint(oldPoint);
    sphereList = ic->listSphere(oldPoint, hi->getAttackSphere(), 'a');
    sphereList.removeFirst();
    for(int i=0; i<sphereList.size(); i++)
    {
        ic->setElementSpecialPen(sphereList.at(i), QPen(Qt::red, 5));
    }
}
