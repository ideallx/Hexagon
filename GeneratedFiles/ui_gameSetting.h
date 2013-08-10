/********************************************************************************
** Form generated from reading UI file 'gameSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESETTING_H
#define UI_GAMESETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_gameSetting
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton;

    void setupUi(QDialog *gameSetting)
    {
        if (gameSetting->objectName().isEmpty())
            gameSetting->setObjectName(QStringLiteral("gameSetting"));
        gameSetting->resize(407, 304);
        buttonBox = new QDialogButtonBox(gameSetting);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        pushButton = new QPushButton(gameSetting);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 20, 75, 23));

        retranslateUi(gameSetting);
        QObject::connect(buttonBox, SIGNAL(accepted()), gameSetting, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), gameSetting, SLOT(reject()));

        QMetaObject::connectSlotsByName(gameSetting);
    } // setupUi

    void retranslateUi(QDialog *gameSetting)
    {
        gameSetting->setWindowTitle(QApplication::translate("gameSetting", "Game Setting", 0));
#ifndef QT_NO_WHATSTHIS
        gameSetting->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        pushButton->setText(QApplication::translate("gameSetting", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class gameSetting: public Ui_gameSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESETTING_H
