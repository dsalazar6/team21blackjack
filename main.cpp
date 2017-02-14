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
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    // If you want to run this as a gui program, uncomment everthing
    // from this line until the return statement. Also make sure to comment
    // everything from mainwindow.cpp from line 18 to line 164
    vector<Card> Deck;
    vector<Card> Hand;
    vector<Card> DealerHand;
    vector<Card> Graveyard;

    deck d;
    d.addStandardDeck(Deck);
    d.Shuffle(Deck);

    bool hold = false;
    bool bust = false;
    bool dealerBust = false;

    int value = 0;
    int dealerValue = 0;
    int hitHold = -1; //determines whether you want to hit, hold or exit

    //while (hitHold != 3)
    //{
        cout << "The dealer is giving you cards.\n";
        d.draw(Deck, Hand, Graveyard, value, bust);
        d.draw(Deck, Hand, Graveyard, value, bust);
        cout << "The dealer is giving himself cards cards.\n";

        d.draw(Deck, DealerHand, Graveyard, dealerValue, dealerBust);
        d.draw(Deck, DealerHand, Graveyard, dealerValue, dealerBust);

        w.Display_Cards(Hand, DealerHand);

        for (int i = 0; i < 3; ++i) {
            if (i == 2)
                w.Show_Card(DealerHand[0].getName(), i);

            else
                w.Show_Card(Hand[i].getName(), i);
        }


    return a.exec();
}
