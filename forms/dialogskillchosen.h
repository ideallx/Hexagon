#ifndef DIALOGSKILLCHOSEN_H
#define DIALOGSKILLCHOSEN_H

#include <QDialog>
#include <QSignalMapper>
#include <QList>
#include <QCheckBox>

class PictureLabel;

namespace Ui {
class DialogSkillChosen;
}

class DialogSkillChosen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSkillChosen(QString path, QWidget *parent = 0);
    ~DialogSkillChosen();

private slots:
    void on_checkSkill1_clicked(bool checked);
    void on_checkSkill2_clicked(bool checked);
    void on_checkSkill3_clicked(bool checked);
    void on_buttonBox_accepted();
    void checkCheckBoxes();
    void labelClicked(int n);
    void on_buttonBox_rejected();

    void on_DialogSkillChosen_rejected();

private:
    Ui::DialogSkillChosen *ui;
    QSignalMapper *qsm;
    int chosenNum;
    QList<PictureLabel*> labels;
    QList<QCheckBox*> checkboxs;
};

#endif // DIALOGSKILLCHOSEN_H
