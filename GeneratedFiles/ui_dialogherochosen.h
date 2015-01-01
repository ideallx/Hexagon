/********************************************************************************
** Form generated from reading UI file 'dialogherochosen.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGHEROCHOSEN_H
#define UI_DIALOGHEROCHOSEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogHeroChosen
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label0;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QLabel *label7;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogHeroChosen)
    {
        if (DialogHeroChosen->objectName().isEmpty())
            DialogHeroChosen->setObjectName(QStringLiteral("DialogHeroChosen"));
        DialogHeroChosen->resize(356, 232);
        verticalLayout = new QVBoxLayout(DialogHeroChosen);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label0 = new QLabel(DialogHeroChosen);
        label0->setObjectName(QStringLiteral("label0"));

        horizontalLayout->addWidget(label0);

        label1 = new QLabel(DialogHeroChosen);
        label1->setObjectName(QStringLiteral("label1"));

        horizontalLayout->addWidget(label1);

        label2 = new QLabel(DialogHeroChosen);
        label2->setObjectName(QStringLiteral("label2"));

        horizontalLayout->addWidget(label2);

        label3 = new QLabel(DialogHeroChosen);
        label3->setObjectName(QStringLiteral("label3"));

        horizontalLayout->addWidget(label3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label4 = new QLabel(DialogHeroChosen);
        label4->setObjectName(QStringLiteral("label4"));

        horizontalLayout_2->addWidget(label4);

        label5 = new QLabel(DialogHeroChosen);
        label5->setObjectName(QStringLiteral("label5"));

        horizontalLayout_2->addWidget(label5);

        label6 = new QLabel(DialogHeroChosen);
        label6->setObjectName(QStringLiteral("label6"));

        horizontalLayout_2->addWidget(label6);

        label7 = new QLabel(DialogHeroChosen);
        label7->setObjectName(QStringLiteral("label7"));

        horizontalLayout_2->addWidget(label7);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(DialogHeroChosen);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogHeroChosen);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogHeroChosen, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogHeroChosen, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogHeroChosen);
    } // setupUi

    void retranslateUi(QDialog *DialogHeroChosen)
    {
        DialogHeroChosen->setWindowTitle(QApplication::translate("DialogHeroChosen", "Dialog", 0));
        label0->setText(QApplication::translate("DialogHeroChosen", "TextLabel", 0));
        label1->setText(QApplication::translate("DialogHeroChosen", "TextLabel", 0));
        label2->setText(QApplication::translate("DialogHeroChosen", "TextLabel", 0));
        label3->setText(QApplication::translate("DialogHeroChosen", "TextLabel", 0));
        label4->setText(QApplication::translate("DialogHeroChosen", "TextLabel", 0));
        label5->setText(QApplication::translate("DialogHeroChosen", "TextLabel", 0));
        label6->setText(QApplication::translate("DialogHeroChosen", "TextLabel", 0));
        label7->setText(QApplication::translate("DialogHeroChosen", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogHeroChosen: public Ui_DialogHeroChosen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGHEROCHOSEN_H
