#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
