/********************************************************************************
** Form generated from reading UI file 'chooseBirth.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEBIRTH_H
#define UI_CHOOSEBIRTH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseBirth
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGraphicsView *graphicsView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChooseBirth)
    {
        if (ChooseBirth->objectName().isEmpty())
            ChooseBirth->setObjectName(QStringLiteral("ChooseBirth"));
        ChooseBirth->resize(501, 473);
        widget = new QWidget(ChooseBirth);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 40, 421, 401));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        graphicsView = new QGraphicsView(widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ChooseBirth);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChooseBirth, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChooseBirth, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChooseBirth);
    } // setupUi

    void retranslateUi(QDialog *ChooseBirth)
    {
        ChooseBirth->setWindowTitle(QApplication::translate("ChooseBirth", "Dialog", 0));
        label->setText(QApplication::translate("ChooseBirth", "Choose Your Birth", 0));
    } // retranslateUi

};

namespace Ui {
    class ChooseBirth: public Ui_ChooseBirth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEBIRTH_H
