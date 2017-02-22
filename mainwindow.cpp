#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "deck.h"
//#include "card.h"
//#include "hand.h"
//#include <vector>
#include <QLabel>
#include <QString>
#include <QInputDialog>

QList<QLabel*> Images;
int free_index = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < 52; ++i) {
        Images.push_back(new QLabel(this));
    }

    Title_Message = "BlackJack Game: Version 1.0";
    this->setWindowTitle(Title_Message);

    //Asks for the number of players playing
    int value = 1;
    do {
        value = QInputDialog::getInt(this, "Player Counter", "Please enter the number of players currently playing(Maximum 5)");
       } while(value < 1 || value > 5);

    current_player_number = 0;
    current_hand_number = 0;
    Dealers_Turn = false;

    //players.reserve(10);
    players.resize(value);
    Dealer.resize(1);
    Dealer[0].Set_Player_Identity(true);

    Deck.addStandardDeck(1);
    Deck.Shuffle();


    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < (int)players.size(); ++j) {
            Deck.draw(players[j], 0); //Draws the first player and is their first hand
            if (j != 0)
                players[j].Hide_Hand();
        }
        Deck.draw(Dealer[0], 0);
    }

    for (int k = 0; k <= (int)players.size(); ++k) {
       if (k == (int)players.size()) {
           cout << "The Dealers Cards are the Following:" << endl;
           Dealer[0].Display_Hands();
       }
       else {
           cout << "Player #" << k + 1 << " Cards are the Following:" << endl;
           players[k].Display_Hands();
       }

    }

    Players_Turn = "It is currently player #";
    Players_Turn += QString::number(current_player_number+1);
    Players_Turn += "'s Turn\n";
    ui->textBrowser->setText(Players_Turn);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// This needs to check the hand size and needs to allow them to hit based on how many hands they have
void MainWindow::on_Hit_Button_clicked()
{
    if (Dealers_Turn)
        Deck.draw(Dealer[0], 0);
    else {
        Deck.draw(players[current_player_number], current_hand_number);
    }
    if (Dealers_Turn) {
        if (Dealer[0].Is_Busted(0))
            Dialog_Text = "You Busted with a value of " + QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n";
        else
            Dialog_Text = "Your current hand value is " + QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n";
    }

    else {
        if (players[current_player_number].Is_Busted(0))
            Dialog_Text = "You Busted with a value of " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n";
        else
            Dialog_Text = "Your current hand value is " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n";
    }

    Dialog_Text = Players_Turn + Dialog_Text;

    ui->textBrowser->setText(Dialog_Text);

}

void MainWindow::on_Stay_Button_clicked()
{
    cout << "Players size is " << players.size() << endl;
    if (Dealers_Turn == true) {
        Dealers_Turn = false;
        current_player_number = 0;
        Players_Turn = "It is currently player #1's turn\n";
        players[players.size()-1].Hide_Hand();
        players[0].Show_Hand();
    }

    else if (int(players.size()) == (current_player_number + 1) && (players[current_player_number].Get_Hand_Count()-1 == current_hand_number)) {
        Dealers_Turn = true;
        Players_Turn = "It is currently the Dealers's turn\n";
        current_hand_number = 0;
    }
    else {
        if (current_hand_number == (int)players[current_player_number].Get_Hand_Count()-1) {
            current_hand_number = 0;
        players[current_player_number].Hide_Hand();
        ++current_player_number;

        players[current_player_number].Show_Hand();
        Players_Turn = "It is currently player #";
        Players_Turn += QString::number(current_player_number+1);
        Players_Turn += "'s Turn\n";
        }
        else {
            ++current_hand_number;
            Players_Turn = "It is currently player #";
            Players_Turn += QString::number(current_player_number+1);
            Players_Turn += "'s Turn\nHand number " + QString::number(current_hand_number+1);
        }
   }
    ui->textBrowser->setText(Players_Turn);
}

void MainWindow::on_Split_Button_clicked()
{
    players[current_player_number].Split();
    current_hand_number = 0;

    //if (int(players.size()) == (current_player_number + 1))
    //        current_player_number = 0;

}
