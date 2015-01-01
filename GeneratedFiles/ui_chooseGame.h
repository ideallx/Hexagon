/********************************************************************************
** Form generated from reading UI file 'chooseGame.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEGAME_H
#define UI_CHOOSEGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseGame
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QRadioButton *mode_2person;
    QRadioButton *mode_4person;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_dd1;
    QRadioButton *radioButton_dd2;

    void setupUi(QDialog *ChooseGame)
    {
        if (ChooseGame->objectName().isEmpty())
            ChooseGame->setObjectName(QStringLiteral("ChooseGame"));
        ChooseGame->resize(448, 370);
        buttonBox = new QDialogButtonBox(ChooseGame);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(60, 310, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(ChooseGame);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 50, 371, 231));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 60, 121, 101));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mode_2person = new QRadioButton(layoutWidget1);
        mode_2person->setObjectName(QStringLiteral("mode_2person"));

        verticalLayout->addWidget(mode_2person);

        mode_4person = new QRadioButton(layoutWidget1);
        mode_4person->setObjectName(QStringLiteral("mode_4person"));
        mode_4person->setChecked(true);

        verticalLayout->addWidget(mode_4person);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        layoutWidget2 = new QWidget(groupBox_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 60, 111, 101));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton_dd1 = new QRadioButton(layoutWidget2);
        radioButton_dd1->setObjectName(QStringLiteral("radioButton_dd1"));
        radioButton_dd1->setChecked(false);

        verticalLayout_2->addWidget(radioButton_dd1);

        radioButton_dd2 = new QRadioButton(layoutWidget2);
        radioButton_dd2->setObjectName(QStringLiteral("radioButton_dd2"));
        radioButton_dd2->setChecked(true);

        verticalLayout_2->addWidget(radioButton_dd2);


        horizontalLayout->addWidget(groupBox_2);


        retranslateUi(ChooseGame);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChooseGame, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChooseGame, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChooseGame);
    } // setupUi

    void retranslateUi(QDialog *ChooseGame)
    {
        ChooseGame->setWindowTitle(QApplication::translate("ChooseGame", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("ChooseGame", "Game Mode", 0));
        mode_2person->setText(QApplication::translate("ChooseGame", "2 Persons", 0));
        mode_4person->setText(QApplication::translate("ChooseGame", "4 Persons", 0));
        groupBox_2->setTitle(QApplication::translate("ChooseGame", "Map Choose", 0));
        radioButton_dd1->setText(QApplication::translate("ChooseGame", "Death Desert 1", 0));
        radioButton_dd2->setText(QApplication::translate("ChooseGame", "Death Desert 2", 0));
    } // retranslateUi

};

namespace Ui {
    class ChooseGame: public Ui_ChooseGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEGAME_H
