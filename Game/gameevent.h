#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <QEvent>
#include <QPoint>

class GameEvent : public QEvent
{
    Q_OBJECT
public:
    explicit GameEvent(QObject *parent = 0);

    enum type {
        HeroMove,
        HeroAttact,
        HeroSkill,
        HeroCardUse
    };

    QPoint fromPos;
    QPoint toPos;

    inline QPoint from() { return fromPos; }
    inline QPoint to() { return toPos; }
    
signals:
    
public slots:
    
};

#endif // GAMEEVENT_H
