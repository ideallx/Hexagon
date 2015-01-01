/********************************************************************************
** Form generated from reading UI file 'enviroSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENVIROSETTINGS_H
#define UI_ENVIROSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_enviroSetting
{
public:
    QDialogButtonBox *buttonBox;
    QRadioButton *radioButton;

    void setupUi(QDialog *enviroSetting)
    {
        if (enviroSetting->objectName().isEmpty())
            enviroSetting->setObjectName(QStringLiteral("enviroSetting"));
        enviroSetting->resize(400, 300);
        buttonBox = new QDialogButtonBox(enviroSetting);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        radioButton = new QRadioButton(enviroSetting);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(60, 60, 89, 16));

        retranslateUi(enviroSetting);
        QObject::connect(buttonBox, SIGNAL(accepted()), enviroSetting, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), enviroSetting, SLOT(reject()));

        QMetaObject::connectSlotsByName(enviroSetting);
    } // setupUi

    void retranslateUi(QDialog *enviroSetting)
    {
        enviroSetting->setWindowTitle(QApplication::translate("enviroSetting", "Enviroment Setting", 0));
        radioButton->setText(QApplication::translate("enviroSetting", "RadioButton", 0));
    } // retranslateUi

};

namespace Ui {
    class enviroSetting: public Ui_enviroSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENVIROSETTINGS_H
