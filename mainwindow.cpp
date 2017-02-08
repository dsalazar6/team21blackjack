#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deck.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Deck temp;
    temp.Display_Deck();

    int random_card, random_suit;
    random_card = randomizer(13);
    random_suit = randomizer(4);

    QString current_card = Get_Card_Name(random_card, random_suit);
    user_card_size = dealers_card_size = 0;
    user_cards[0].card_number = random_card;
    user_cards[0].card_suit = random_suit;
    ++user_card_size;



    //These card images are saved by a 55x80 resolution
    Image_File = "Ace of Spades.png";
    images[0] = ui->label_1;
    images[1] = ui->label_2;
    images[2] = ui->label_3;
    images[3] = ui->label_4;
    images[4] = ui->label_5;
    images[5] = ui->label_6;
    images[6] = ui->label_7;
    images[7] = ui->label_8;
    images[8] = ui->label_9;
    images[9] = ui->label_10;


    //images[0]->setPixmap(QString("BackSide.png"));
    //ui->label_1->setPixmap(Image_File);
    //ui->label_3->setPixmap(Image_File);
    Image_File = "BackSide.png";

    //The table image is saved by a 450x600 resolution
    Table_Image_File = "Table_Foreground.png";

    //ui->label_2->setPixmap(Image_File);
    //ui->label_4->setPixmap(Image_File);

    for (int i = 0; i < 10; ++i) {
        if (i == 0 || i == 2)
            images[i]->setPixmap(QString("Ace of Spades.png"));
        else if (i == 1 || i == 3)
            images[i]->setPixmap(QString("BackSide.png"));
        else
            images[i]->hide();

    }


    ui->Table->setPixmap(Table_Image_File);

    //ui->label_5->hide();
    //ui->label_6->hide();
    //ui->label_7->hide();
    //ui->label_8->hide();
    //ui->label_9->hide();
    //ui->label_10->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::randomizer(int range) {

    return (rand() % range);
}

QString MainWindow::Get_Card_Name(int card_index, int color_index) {
    QString card_name;

    switch(card_index) {
       case 0:
        card_name = "Ace";
        break;
       case 1:
        card_name = "Two";
        break;
       case 2:
        card_name = "Three";
        break;
       case 3:
        card_name = "Four";
        break;
       case 4:
        card_name = "Five";
        break;
       case 5:
        card_name = "Six";
        break;
       case 6:
        card_name = "Seven";
        break;
       case 7:
        card_name = "Eight";
        break;
       case 8:
        card_name = "Nine";
        break;
       case 9:
        card_name = "Ten";
        break;
       case 10:
        card_name = "Jack";
        break;
       case 11:
        card_name = "Queen";
        break;
       case 12:
        card_name = "King";
        break;
    }

    card_name += " of ";

    switch(color_index) {
       case 0:
        card_name += "Diamonds";
        break;
       case 1:
        card_name += "Hearts";
        break;
       case 2:
        card_name += "Clubs";
        break;
       case 3:
        card_name += "Spades";
    }
    return card_name;
}

void MainWindow::on_pushButton_clicked()
{

    if (Image_File == "BackSide.png"){
        Image_File = "Ace of Spades.png";
    }

    else {
        Image_File = "BackSide.png";
    }

    ui->label_2->setPixmap(Image_File);
    ui->label_4->setPixmap(Image_File);
}

