/********************************************************************************
** Form generated from reading UI file 'dialogskillchosen.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSKILLCHOSEN_H
#define UI_DIALOGSKILLCHOSEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <picturelabel.h>

QT_BEGIN_NAMESPACE

class Ui_DialogSkillChosen
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkSkill1;
    PictureLabel *label;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkSkill2;
    PictureLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkSkill3;
    PictureLabel *label_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSkillChosen)
    {
        if (DialogSkillChosen->objectName().isEmpty())
            DialogSkillChosen->setObjectName(QStringLiteral("DialogSkillChosen"));
        DialogSkillChosen->resize(770, 525);
        verticalLayout_4 = new QVBoxLayout(DialogSkillChosen);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        checkSkill1 = new QCheckBox(DialogSkillChosen);
        checkSkill1->setObjectName(QStringLiteral("checkSkill1"));

        verticalLayout->addWidget(checkSkill1);

        label = new PictureLabel(DialogSkillChosen);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8("../../rsc/heros/skill_icons/back.jpg")));

        verticalLayout->addWidget(label);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        checkSkill2 = new QCheckBox(DialogSkillChosen);
        checkSkill2->setObjectName(QStringLiteral("checkSkill2"));

        verticalLayout_2->addWidget(checkSkill2);

        label_2 = new PictureLabel(DialogSkillChosen);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../rsc/heros/skill_icons/back.jpg")));

        verticalLayout_2->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        checkSkill3 = new QCheckBox(DialogSkillChosen);
        checkSkill3->setObjectName(QStringLiteral("checkSkill3"));

        verticalLayout_3->addWidget(checkSkill3);

        label_3 = new PictureLabel(DialogSkillChosen);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8("../../rsc/heros/skill_icons/back.jpg")));

        verticalLayout_3->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(DialogSkillChosen);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);


        retranslateUi(DialogSkillChosen);
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSkillChosen, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSkillChosen);
    } // setupUi

    void retranslateUi(QDialog *DialogSkillChosen)
    {
        DialogSkillChosen->setWindowTitle(QApplication::translate("DialogSkillChosen", "Dialog", 0));
        checkSkill1->setText(QApplication::translate("DialogSkillChosen", "Skill1", 0));
        label->setText(QString());
        checkSkill2->setText(QApplication::translate("DialogSkillChosen", "Skill2", 0));
        label_2->setText(QString());
        checkSkill3->setText(QApplication::translate("DialogSkillChosen", "Skill3", 0));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogSkillChosen: public Ui_DialogSkillChosen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSKILLCHOSEN_H
