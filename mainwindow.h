#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
#include "card.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void Show_Card(string PictureName, int label_number);
    void Display_Cards(vector <Card>&Hand, vector <Card>&DealerHand);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;


    QLabel *images[10];
    QString Image_File;
    QString Table_Image_File;
    int user_card_size;
    int dealers_card_size;

};

#endif // MAINWINDOW_H
