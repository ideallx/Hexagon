#include "Widget/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("lang__zhCN.qm", ":/");
    a.installTranslator(&translator);

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    
    return a.exec();
}
