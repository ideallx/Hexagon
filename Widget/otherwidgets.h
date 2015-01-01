#ifndef WIDGET_OTHERWIDGETS_H_
#define WIDGET_OTHERWIDGETS_H_

#include <QWidget>
#include <QToolButton>
#include "ui_modechoose.h"
#include "ui_enviroSettings.h"


class ModeChooseWidget : public QWidget {
    Q_OBJECT
 public:
    explicit ModeChooseWidget(QWidget *parent = 0);
    ~ModeChooseWidget();
    inline QToolButton* singleButton() { return ui->singleGame; }

 private:
    Ui::modeChoose *ui;
    Ui::enviroSetting *uie;
    QDialog *qdlg;

 private slots:
    void on_settings_clicked();
};

#endif  // WIDGET_OTHERWIDGETS_H_
