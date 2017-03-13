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
    //ui->New_Game->hide();

    //Change_user("BOB");

    for (int i = 0; i < 52; ++i) {
        Images.push_back(new QLabel(this));
    }

    Title_Message = "BlackJack Game: Version 1.0";
    this->setWindowTitle(Title_Message);

    Deck.addStandardDeck(1);
    Deck.Shuffle();

    //Asks for the number of players playing
    Number_of_Players = 1;

    //Asks for the number of players. DO NOT DELETE!!
    /*
    do {
        Number_of_Players = QInputDialog::getInt(this, "Player Counter", "Please enter the number of players currently playing(Maximum 5)");
       } while(Number_of_Players < 1 || Number_of_Players > 5);

    */
    Start_Game();

}
void MainWindow::Start_Game() {
    ui->New_Game->hide();
    current_player_number = 0;
    current_hand_number = 0;
    Dealers_Turn = false;

    //players.reserve(10);
    players.resize(Number_of_Players);
    Dealer.resize(1);
    Dealer[0].Set_Player_Identity(true);


    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < (int)players.size(); ++j) {
            Deck.draw(players[j], 0); //Draws the first player and is their first hand
            if (j != 0)
                players[j].Hide_Hand();
        }
        Deck.draw(Dealer[0], 0);
        if (i == 1)
            Dealer[0].Flip_Card(0);

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

void MainWindow::New_Game() {
   Deck.Discard_Current_Cards();
   players.clear();
   Dealer.clear();
   Start_Game();
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
        Dealer[0].Flip_Card(0);
        Players_Turn = "It is currently the Dealers's turn\n";
        current_hand_number = 0;

        while(Dealer[0].Get_Current_Hand_value(0) < 17) {
            on_Hit_Button_clicked();
        Players_Turn += "The Dealer has a Total of ";
        Players_Turn += QString::number(Dealer[0].Get_Current_Hand_value(0));
        if (Dealer[0].Get_Current_Hand_value(0) > 21)
            Players_Turn += "\nThe Dealer has Busted!";
        }
        ui->New_Game->show();
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

void MainWindow::on_New_Game_clicked()
{
    New_Game();
}

bool MainWindow::Change_user(string username) {
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < Images.size(); ++i) {
        delete Images.takeAt(0);
    }
    delete ui;
}
