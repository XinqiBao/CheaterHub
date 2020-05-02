#include "mainwindow.h"
#include "cfg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cfg cfg;
    MainWindow w(cfg);
    w.show();
    return a.exec();
}
