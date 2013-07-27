/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQt;
    QAction *actionGame;
    QAction *actionTest;
    QAction *actionTest2;
    QAction *actionEndTurn;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *viewLeft;
    backview *viewCenter;
    QGraphicsView *viewRight;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(994, 654);
        actionQt = new QAction(MainWindow);
        actionQt->setObjectName(QStringLiteral("actionQt"));
        actionGame = new QAction(MainWindow);
        actionGame->setObjectName(QStringLiteral("actionGame"));
        actionGame->setCheckable(true);
        actionGame->setChecked(true);
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionTest->setCheckable(true);
        actionTest2 = new QAction(MainWindow);
        actionTest2->setObjectName(QStringLiteral("actionTest2"));
        actionTest2->setCheckable(true);
        actionEndTurn = new QAction(MainWindow);
        actionEndTurn->setObjectName(QStringLiteral("actionEndTurn"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        viewLeft = new QGraphicsView(centralWidget);
        viewLeft->setObjectName(QStringLiteral("viewLeft"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(viewLeft->sizePolicy().hasHeightForWidth());
        viewLeft->setSizePolicy(sizePolicy);
        viewLeft->setMinimumSize(QSize(300, 0));
        viewLeft->setMaximumSize(QSize(300, 16777215));

        horizontalLayout->addWidget(viewLeft);

        viewCenter = new backview(centralWidget);
        viewCenter->setObjectName(QStringLiteral("viewCenter"));

        horizontalLayout->addWidget(viewCenter);

        viewRight = new QGraphicsView(centralWidget);
        viewRight->setObjectName(QStringLiteral("viewRight"));
        sizePolicy.setHeightForWidth(viewRight->sizePolicy().hasHeightForWidth());
        viewRight->setSizePolicy(sizePolicy);
        viewRight->setMinimumSize(QSize(300, 0));
        viewRight->setMaximumSize(QSize(300, 16777215));

        horizontalLayout->addWidget(viewRight);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 994, 21));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionQt);
        menu_2->addAction(actionEndTurn);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionQt->setText(QApplication::translate("MainWindow", "Qt", 0));
        actionGame->setText(QApplication::translate("MainWindow", "\346\270\270\346\210\217\350\247\206\345\233\276", 0));
        actionTest->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225\351\241\265\351\235\242", 0));
        actionTest2->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225\351\241\265\351\235\2422", 0));
        actionEndTurn->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\345\233\236\345\220\210\347\273\223\346\235\237", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\265\213\350\257\225\351\241\271", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
