#include "mainwindow.h"
#include <vector>
#include <QApplication>
#include <QLabel>
#include <iostream>

//For using rand()
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
