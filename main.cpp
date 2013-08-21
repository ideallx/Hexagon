//#include "gameWidget.h"
#include "gameprocess.h"
#include <QApplication>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    QTranslator translator;
    translator.load("lang__zhCN.qm", ":/");
    a.installTranslator(&translator);
*/
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    gameProcess gp;

    
    return a.exec();
}
