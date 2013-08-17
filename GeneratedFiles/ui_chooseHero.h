/********************************************************************************
** Form generated from reading UI file 'chooseHero.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEHERO_H
#define UI_CHOOSEHERO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_chooseHero
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *chooseHero)
    {
        if (chooseHero->objectName().isEmpty())
            chooseHero->setObjectName(QStringLiteral("chooseHero"));
        chooseHero->resize(556, 403);
        gridLayout = new QGridLayout(chooseHero);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(chooseHero);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout1 = new QHBoxLayout();
        horizontalLayout1->setObjectName(QStringLiteral("horizontalLayout1"));

        verticalLayout->addLayout(horizontalLayout1);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(chooseHero);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(chooseHero);
        QObject::connect(buttonBox, SIGNAL(accepted()), chooseHero, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), chooseHero, SLOT(reject()));

        QMetaObject::connectSlotsByName(chooseHero);
    } // setupUi

    void retranslateUi(QDialog *chooseHero)
    {
        chooseHero->setWindowTitle(QApplication::translate("chooseHero", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("chooseHero", "Choose Your Hero", 0));
    } // retranslateUi

};

namespace Ui {
    class chooseHero: public Ui_chooseHero {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEHERO_H
