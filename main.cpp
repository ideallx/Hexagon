//#include "gameWidget.h"
#include "gameprocess.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    QTranslator translator;
    translator.load("lang__zhCN.qm", ":/");
    a.installTranslator(&translator);
*/
    //MainWindow w;
    //w.setWindowState(Qt::WindowMaximized);
    //w.show();

    gameProcess gp(5);

    
    return a.exec();
}
