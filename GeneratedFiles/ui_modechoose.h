/********************************************************************************
** Form generated from reading UI file 'modechoose.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODECHOOSE_H
#define UI_MODECHOOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_modeChoose
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QToolButton *singleGame;
    QToolButton *lanGame;
    QToolButton *settings;
    QToolButton *replay;
    QVBoxLayout *verticalLayout_2;
    QToolButton *cardsView;
    QToolButton *mapsView;
    QToolButton *herosView;
    QToolButton *about;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *modeChoose)
    {
        if (modeChoose->objectName().isEmpty())
            modeChoose->setObjectName(QStringLiteral("modeChoose"));
        modeChoose->resize(800, 600);
        centralwidget = new QWidget(modeChoose);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 215, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(292, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        singleGame = new QToolButton(centralwidget);
        singleGame->setObjectName(QStringLiteral("singleGame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(singleGame->sizePolicy().hasHeightForWidth());
        singleGame->setSizePolicy(sizePolicy);
        singleGame->setBaseSize(QSize(100, 100));
        singleGame->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(singleGame);

        lanGame = new QToolButton(centralwidget);
        lanGame->setObjectName(QStringLiteral("lanGame"));

        verticalLayout->addWidget(lanGame);

        settings = new QToolButton(centralwidget);
        settings->setObjectName(QStringLiteral("settings"));

        verticalLayout->addWidget(settings);

        replay = new QToolButton(centralwidget);
        replay->setObjectName(QStringLiteral("replay"));

        verticalLayout->addWidget(replay);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cardsView = new QToolButton(centralwidget);
        cardsView->setObjectName(QStringLiteral("cardsView"));

        verticalLayout_2->addWidget(cardsView);

        mapsView = new QToolButton(centralwidget);
        mapsView->setObjectName(QStringLiteral("mapsView"));

        verticalLayout_2->addWidget(mapsView);

        herosView = new QToolButton(centralwidget);
        herosView->setObjectName(QStringLiteral("herosView"));

        verticalLayout_2->addWidget(herosView);

        about = new QToolButton(centralwidget);
        about->setObjectName(QStringLiteral("about"));

        verticalLayout_2->addWidget(about);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(292, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 214, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        modeChoose->setCentralWidget(centralwidget);
        menubar = new QMenuBar(modeChoose);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        modeChoose->setMenuBar(menubar);
        statusbar = new QStatusBar(modeChoose);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        modeChoose->setStatusBar(statusbar);

        retranslateUi(modeChoose);

        QMetaObject::connectSlotsByName(modeChoose);
    } // setupUi

    void retranslateUi(QMainWindow *modeChoose)
    {
        modeChoose->setWindowTitle(QApplication::translate("modeChoose", "MainWindow", 0));
        singleGame->setText(QApplication::translate("modeChoose", "Single Game", 0));
        lanGame->setText(QApplication::translate("modeChoose", "LAN Game", 0));
        settings->setText(QApplication::translate("modeChoose", "Settings", 0));
        replay->setText(QApplication::translate("modeChoose", "Replay", 0));
        cardsView->setText(QApplication::translate("modeChoose", "Cards View", 0));
        mapsView->setText(QApplication::translate("modeChoose", "Maps View", 0));
        herosView->setText(QApplication::translate("modeChoose", "Heros View", 0));
        about->setText(QApplication::translate("modeChoose", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class modeChoose: public Ui_modeChoose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODECHOOSE_H
