#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include "gameWidget.h"
#include "gameprocess.h"
#include "carditem.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
/*
    QTranslator translator;
    translator.load("lang__zhCN.qm", ":/");
    a.installTranslator(&translator);
*/
    qRegisterMetaType<HandCard>("HandCard");
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    MainWindow m;

    return 0;
}
