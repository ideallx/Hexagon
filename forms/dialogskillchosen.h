#ifndef DIALOGSKILLCHOSEN_H
#define DIALOGSKILLCHOSEN_H

#include <QDialog>

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

private:
    Ui::DialogSkillChosen *ui;
    int chosenNum;
};

#endif // DIALOGSKILLCHOSEN_H
