#include "mainwindow.h"
#include "card.h"
#include "deck.h"
#include <string>
#include <vector>
#include <list>
#include <QApplication>
#include <QLabel>

//For using rand()
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
