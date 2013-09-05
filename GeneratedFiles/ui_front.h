/********************************************************************************
** Form generated from reading UI file 'front.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRONT_H
#define UI_FRONT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "layoutscene.h"

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *leftBlock;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *leftHeros;
    QSpacerItem *verticalSpacer;
    QLabel *head;
    QVBoxLayout *centerBlock;
    QSpacerItem *verticalSpacer_4;
    QProgressBar *heroHp;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *essenial;
    QGraphicsView *ability;
    QVBoxLayout *rightBlock;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *rightHeros;
    QSpacerItem *verticalSpacer_3;
    ViewSendResize *items;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(1219, 673);
        horizontalLayout_5 = new QHBoxLayout(Form);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 20);
        leftBlock = new QVBoxLayout();
        leftBlock->setObjectName(QStringLiteral("leftBlock"));
        leftBlock->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        leftHeros = new QVBoxLayout();
        leftHeros->setObjectName(QStringLiteral("leftHeros"));

        verticalLayout_3->addLayout(leftHeros);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        head = new QLabel(Form);
        head->setObjectName(QStringLiteral("head"));

        verticalLayout_3->addWidget(head);


        horizontalLayout_3->addLayout(verticalLayout_3);


        leftBlock->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(leftBlock);

        centerBlock = new QVBoxLayout();
        centerBlock->setObjectName(QStringLiteral("centerBlock"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        centerBlock->addItem(verticalSpacer_4);

        heroHp = new QProgressBar(Form);
        heroHp->setObjectName(QStringLiteral("heroHp"));
        heroHp->setValue(24);
        heroHp->setAlignment(Qt::AlignCenter);
        heroHp->setTextVisible(true);
        heroHp->setInvertedAppearance(false);
        heroHp->setTextDirection(QProgressBar::TopToBottom);

        centerBlock->addWidget(heroHp);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        essenial = new QGraphicsView(Form);
        essenial->setObjectName(QStringLiteral("essenial"));

        horizontalLayout->addWidget(essenial);

        ability = new QGraphicsView(Form);
        ability->setObjectName(QStringLiteral("ability"));
        ability->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ability->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout->addWidget(ability);


        centerBlock->addLayout(horizontalLayout);


        horizontalLayout_5->addLayout(centerBlock);

        rightBlock = new QVBoxLayout();
        rightBlock->setObjectName(QStringLiteral("rightBlock"));
        rightBlock->setSizeConstraint(QLayout::SetFixedSize);
        rightBlock->setContentsMargins(-1, -1, 20, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        rightHeros = new QVBoxLayout();
        rightHeros->setObjectName(QStringLiteral("rightHeros"));

        horizontalLayout_4->addLayout(rightHeros);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        items = new ViewSendResize(Form);
        items->setObjectName(QStringLiteral("items"));
        items->setLayoutDirection(Qt::LeftToRight);
        items->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        items->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout->addWidget(items);


        horizontalLayout_2->addLayout(verticalLayout);


        rightBlock->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(rightBlock);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        head->setText(QString());
        heroHp->setFormat(QApplication::translate("Form", "%v/%m", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRONT_H
