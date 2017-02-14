#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deck.h"
#include "card.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

// If you want to run this as a console program, uncomment everthing
// from this line until line 164. Also make sure to comment
// everything from main.cpp from line 29 to the return statement
/*
    vector<Card> Deck;
    vector<Card> Hand;
    vector<Card> DealerHand;
    vector<Card> Graveyard;

    deck d;

    bool end=false; //will end the game when true



        cout << "Welcome to Blackjack\n";
        while (!end) {
            int option;
            //phase 1 start game
            cout << "1) New game\n";
            cout << "2) Exit\n";
            cin >> option;
            if (option == 1)
            {
                d.addStandardDeck(Deck);
                //			cout << "cards successfully added in the following order with a length of " << Deck.size() <<"\n";

                //			for (int i = 1; i < Deck.size(); i++)
                //				cout << Deck[i].getName() << endl;

                d.Shuffle(Deck); //The deck is being shuffled
    //			cout << "cards successfully shuffled in the following order with a length of " << Deck.size() << "\n";

    //			for (int i = 1; i < Deck.size(); i++)
    //				cout << Deck[i].getName() << endl;


                //Phase 2 Draw card for player and Dealer

                bool hold = false;
                bool bust = false;
                bool dealerBust = false;

                int value = 0;
                int dealerValue = 0;
                int hitHold = -1; //determines whether you want to hit, hold or exit

                while (hitHold != 3)
                {
                    cout << "The dealer is giving you cards.\n";
                    d.draw(Deck, Hand, Graveyard, value, bust);
                    d.draw(Deck, Hand, Graveyard, value, bust);
                    cout << "The dealer is giving himself cards cards.\n";

                    d.draw(Deck, DealerHand, Graveyard, dealerValue, dealerBust);
                    d.draw(Deck, DealerHand, Graveyard, dealerValue, dealerBust);

                    //Phase 3 Player may draw or hit
                    while (!bust && !hold && value != 21) //while the player isn't choosing to stand and hasn't busted and hasn't already drawn 21
                    {

                        cout << "\n\nYou currently have the following cards:\n";
                        for (int i = 0; i < Hand.size(); i++)
                            cout << " " << Hand[i].getName() << endl;

                        cout << "the current value of your hand is " << value << endl;
                        cout << "The Dealer currently has a\n " << DealerHand[0].getName() << "\n a face down card";
                        cout << "\nSelect an option :\n1)Hit\n2)Hold\n3)End Game\n";
                        cin >> hitHold;


                        if (hitHold == 1)
                        {
                            d.draw(Deck, Hand, Graveyard, value, bust);
                            cout << "You have drawn a " << Hand[Hand.size() - 1].getName() << endl;
                        }
                        else if (hitHold == 2)
                            hold = true;
                        else if (hitHold == 3)
                            return;
                    }

                    //Phase 4 Dealer will Draw or hit if the player didn't bust and the player hasn't quit the game
                    if (!bust && value != 21 && hitHold != 3)
                    {
                        cout << "The dealer has revealed his face down card is the " << DealerHand[1].getName() << endl;
                        if (dealerValue == 21)
                        {
                            cout << "the dealer hit blackjack.\n";
                        }
                        else if (dealerValue >= 17)
                        {
                            cout << "The dealer holds on the value " << dealerValue << endl;
                        }
                        else {
                            cout << "The dealer will begin drawing.\n";
                            int i = 2;
                            while (dealerValue < 17)
                            {
                                d.draw(Deck, DealerHand, Graveyard, dealerValue, dealerBust);
                                cout << "The dealer has drawn a " << DealerHand[i].getName()<< endl;
                                i++;
                            }
                        }
                    }
                    if (value == 21) {
                        cout << "You have hit blackjack.\n";
                    }
                    if (bust)
                        cout << "You have busted and lost this hand.\n";
                    else if (dealerBust)
                        cout << "The dealer has busted and lost this hand.\n";
                    else {
                        if (dealerValue > value)
                            cout << "The dealer has won this hand.\n";
                        else if (value > dealerValue)
                            cout << "You have won this hand.\n";
                    }
                    cout << endl;
                    //Places hands into graveyard

                    //make all cards alterable
                    for (int i = 0; i < Hand.size(); i++)
                        Hand[i].resetValue();
                    for (int i = 0; i < DealerHand.size(); i++)
                        DealerHand[i].resetValue();
                    Graveyard.reserve(Hand.size() + DealerHand.size());
                    Graveyard.insert(Graveyard.end(), Hand.begin(), Hand.end());
                    Graveyard.insert(Graveyard.end(), DealerHand.begin(), DealerHand.end());
                    while (!Hand.empty())
                        Hand.erase(Hand.begin());
                    while (!DealerHand.empty())
                        DealerHand.erase(DealerHand.begin());

                    value = 0;
                    dealerValue = 0;
                    bust = false;
                    hold = false;
                    dealerBust = false;
                    hitHold = -1;
                }

            }
            else if (option == 2)
            {
                end = true;
            }

        }
*/

    user_card_size = dealers_card_size = 0;
    //user_cards[0].card_number = random_card;
    //user_cards[0].card_suit = random_suit;
    ++user_card_size;



    //These card images are saved by a 55x80 resolution
    //Image_File = "Ace of Spades.png";
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
            images[i]->setPixmap(QString("Pictures/Ace of Spades.png"));
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

void MainWindow::Show_Card(string PictureName, int label_number) {
     QString CardName = QString::fromStdString(PictureName + ".png");
     images[label_number]->setPixmap(CardName);
}

void MainWindow::Display_Cards(vector <Card> &Hand, vector <Card> &DealerHand ) {
    for (int i = 0; i < 4; ++i) {
       if (i > 1)
            cout << "The dealers card number " << i-1 << " is "
                 << DealerHand[i-2].getName() << endl;
       else
           cout << "The Players card number " << i+1
                << " is " << Hand[i].getName() << endl;
    }
}

void MainWindow::on_pushButton_clicked()
{

    if (Image_File == "BackSide.png"){
        Image_File = "Pictures/Ace of Spades.png";
    }

    else {
        Image_File = "BackSide.png";
    }

    ui->label_2->setPixmap(Image_File);
    ui->label_4->setPixmap(Image_File);
}

