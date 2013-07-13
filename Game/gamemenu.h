#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QtWidgets>

class gameMenu : public QObject
{
    Q_OBJECT
public:
    enum menu_type_t
    {
        MENULIST,
        MOVELIST,
        ATTACKLIST,
        ABILITYLIST,
        CANCELLIST
    };

    gameMenu(QWidget *parent = 0);
    void showMenu(gameMenu::menu_type_t, QPointF pos = QPointF());
    void hideMenu(gameMenu::menu_type_t);

private:
    void menuInitial();
    QList<QPushButton*> menuList;
    QWidget* parent;

signals:
    void moveClicked();

public slots:
    void hideAllMenu();

};


#endif // GAMEMENU_H
