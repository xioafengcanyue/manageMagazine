#include "mainwindow.h"
#include"mainwindow2.h"
#include <QApplication>
#include"sqlthread.h"
#include"mydb.h"
#include"mydb.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
