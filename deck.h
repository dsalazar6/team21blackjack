#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "player.h"
#include <iostream>
#include <math.h>

using namespace std;

class deck {
public:
    deck() {}

    // Creates all the cards needed for the deck(s)
    void addStandardDeck(int decks_used)
    {
        Card temp;
        int total_cards = 52 * decks_used;
        for (int i = 0; i < total_cards; i++)
        {
            temp = Card(i);
            Deck.push_back(temp);
        }

    }

    // returns random number
    int getRandomNumber(int max)
    {
        return (rand() % max);
    }

    void Discard_Current_Cards() {
        for (int i = Drawn_Cards.size()-1; i >= 0; --i) {
            if (Drawn_Cards[i].getMinValueUsed())
                Drawn_Cards[i].resetValue();

            Graveyard.push_back(Drawn_Cards[i]);
            Drawn_Cards.pop_back();
        }
    }

    // An Algorithm that shuffles the deck(s)
    void Shuffle()
    {
        int j = 0;
        int rnd;

        for (int i = 0; i < (int)Deck.size(); i++)
        {
            rnd = getRandomNumber(Deck.size());
            j = rnd;
            Card tmp = Deck[i];
            Card b = Deck[j];
            Deck[i] = Deck[j];
            Deck[j] = tmp;
        }
        cout << "The deck has been shuffled\n";
    }

    //The Deck will give a player or dealer one card from the top of the deck.
    //If there are no cards in the deck, the cards from the graveyard will be added to the deck and the deck will be shuffled, then the hand will recieve a card
    //If the hand breaks the maximum, it will look for the first multivalued card and alter its value by the min value, then make let the vector know not to use that same card again
    //If the Hand busts all hands in play will go to the graveyard
    void draw(Player& current_player, int hand_number)
    {
        cout << "The amount of cards in the deck is " << Deck.size() << endl;
        if (Deck.empty())
        {
            cout << "The deck has run out of cards and will be reshuffled with the discarded cards.\n";
            Deck = Graveyard;
            Shuffle();
            Graveyard.clear();
        }

        cout << "Checking for busting " << current_player.Is_Busted(hand_number) << endl;
        if (!current_player.Is_Busted(hand_number)) {
            current_player.Hit_card(hand_number, Deck[0]); //Adds the top card of the vector to the hand
            Drawn_Cards.push_back(Deck[0]);
            Deck.erase(Deck.begin()); //Removes the top card of the vector
            cout << "The value of the current hand is "
                 << current_player.Get_Current_Hand_value(hand_number) << endl;
        }
        else {
            cout << "Current hand is busted!" << endl;
        }

    }
    double High_Card_Count() {
      int counter = 0;
      double percentage = 0;
      for(int i = 0; i < (int)Graveyard.size(); ++i) {
          if (Graveyard[i].getValue() == 10) {
              counter++;
          }
      }
      for (int i = 0; i < (int)Drawn_Cards.size(); ++i) {
          if (i != 3) {
              if (Drawn_Cards[i].getValue() == 10) {
                  counter++;
              }
          }
      }
      percentage = ((52- counter)/52.00)* 100;
      return (floor(percentage*100)/100);
    }

    double Low_Card_Count() {
        int counter = 0;
        double percentage = 0;
        for(int i = 0; i < (int)Graveyard.size(); ++i) {
            if (Graveyard[i].getValue() != 10) {
                counter++;
            }
        }
        for (int i = 0; i < (int)Drawn_Cards.size(); ++i) {
            if (i != 3) {
                if (Drawn_Cards[i].getValue() != 10) {
                    counter++;
                }
            }
        }
        percentage = ((52- counter)/52.00)* 100;
        return (floor(percentage*100)/100);
    }




    ~deck() {
        Deck.clear();
        Graveyard.clear();
    }

private:
    vector<Card> Deck;
    vector<Card> Graveyard;
    vector<Card> Drawn_Cards;

};


#endif // DECK_H
