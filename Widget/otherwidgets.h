#ifndef OTHERWIDGETS_H
#define OTHERWIDGETS_H

#include <QWidget>
#include <QToolButton>
#include "ui_modechoose.h"
#include "ui_gameSetting.h"
#include "ui_enviroSettings.h"


class modeChooseWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit modeChooseWidget(QWidget *parent = 0);
	QToolButton* singleButton() { return ui->singleGame; }


private:
    Ui::modeChoose *ui;
    Ui::gameSetting *uig;
    Ui::enviroSetting *uie;
    QDialog *qdlg;
    
signals:
    
public slots:
    
private slots:
    void on_settings_clicked();
};

#endif // OTHERWIDGETS_H
