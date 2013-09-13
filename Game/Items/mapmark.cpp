#include <QDebug>
#include <QPainter>
#include "mapmark.h"

MapMark::MapMark(QString path, int width) {
    QPixmap* pic = new QPixmap(path);
    if (pic->isNull()) {
        qDebug() << "Map Mark Not Found";
    }

    setBrush(pic->scaled(width, width, Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation));

    setZValue(1);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setRect(0, 0, width, width);
}

QRectF MapMark::boundingRect() const {
    return rect();
}

QPainterPath MapMark::shape() const {
    QPainterPath path;
    path.addEllipse(rect());
    return path;
}
void MapMark::paint(QPainter* painter,
                    const QStyleOptionGraphicsItem* option,
                    QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setOpacity(1.0);
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawEllipse(rect());
}
