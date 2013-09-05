/********************************************************************************
** Form generated from reading UI file 'chooseGame.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
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
    QGroupBox *groupBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *mode_2person;
    QRadioButton *mode_4person;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QDialog *ChooseGame)
    {
        if (ChooseGame->objectName().isEmpty())
            ChooseGame->setObjectName(QStringLiteral("ChooseGame"));
        ChooseGame->resize(570, 609);
        buttonBox = new QDialogButtonBox(ChooseGame);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(190, 550, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(ChooseGame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(70, 90, 411, 391));
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 30, 371, 331));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mode_2person = new QRadioButton(widget);
        mode_2person->setObjectName(QStringLiteral("mode_2person"));

        verticalLayout->addWidget(mode_2person);

        mode_4person = new QRadioButton(widget);
        mode_4person->setObjectName(QStringLiteral("mode_4person"));
        mode_4person->setChecked(true);

        verticalLayout->addWidget(mode_4person);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        horizontalLayout->addLayout(verticalLayout_2);


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
    } // retranslateUi

};

namespace Ui {
    class ChooseGame: public Ui_ChooseGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEGAME_H
