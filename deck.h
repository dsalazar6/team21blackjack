#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "player.h"
#include <iostream>

using namespace std;
//Card counting implemented to keep track of exact values and the low/high count
class deck
{
private:
    vector<Card> Deck;
    vector<Card> Graveyard;
    vector<Card> Drawn_Cards;
    int cards_remaining[13];
    int cards_used[13];
    int num_decks;
    int lowCountR; //card is an Ace or 2-7
    int lowCountU; //card is an Ace or 2-7
    int highCountR; //card is 8 or above
    int highCountU; //card is 8 or above
    bool remainingUsed; //if true cards_remaining is used

public:
    deck() {}

    // Creates all the cards needed for the deck(s)
    void addStandardDeck(int decks_used)
    {
        remainingUsed = true;
        Card Temp;
        num_decks = decks_used;
        int total_cards = 52 * decks_used;
        for (int i = 0; i < total_cards; i++)
        {
            Temp = Card(i);
            Deck.push_back(Temp);
        }
        int value = 4 * decks_used;
        for (int i = 0; i < 13; i++)
        {
            cards_remaining[i] = 0;
            cards_used[i] = value;
        }
        lowCountR = 0;
        highCountR = 0;
        lowCountU = 7 * value;
        highCountU = 6 * value;
    }

    // returns random number
    int getRandomNumber(int max)
    {
        return (rand() % max);
    }

    void Discard_Current_Cards()
    {
        for (int i = Drawn_Cards.size()-1; i >= 0; --i) {
            if (Drawn_Cards[i].getMinValueUsed())
                Drawn_Cards[i].resetValue();
            //if (Drawn_Cards[i].isFaceDown() == true)
            //{
            //    changeCardCount(Drawn_Cards[i].getId(), -1);
            //}
            Graveyard.push_back(Drawn_Cards[i]);
            Drawn_Cards.pop_back();
        }
    }

    // An Algorithm that shuffles the deck(s)
    void Shuffle()
    {
        int j = 0;
        int rnd;
        Card tmp;
        Card b;
        for (int i = 0; i < (int)Deck.size(); i++)
        {
            rnd = getRandomNumber(Deck.size());
            j = rnd;
            tmp = Deck[i];
            b = Deck[j];
            Deck[i] = Deck[j];
            Deck[j] = tmp;
        }
        for (int i = 0; i < (int)Deck.size(); i++)
        {
            changeCardCount(Deck[i].getId(), 1);
        }
        cout << "The deck has been shuffled\n";
    }

    /*The Deck will give a player or dealer one card from the top of the deck.
    If there are no cards in the deck, the cards from the graveyard will be added to the deck and the deck will be shuffled, then the hand will recieve a card
    If the hand breaks the maximum, it will look for the first multivalued card and alter its value by the min value, then make let the vector know not to use that same card again
    If the Hand busts all hands in play will go to the graveyard*/
    void draw(Player& current_player, int hand_number, bool faceDown = false)
    {
        cout << "The amount of cards in the deck is " << Deck.size() << endl;
        if (Deck.empty())
        {
            cout << "The deck has run out of cards and will be reshuffled with the discarded cards.\n";
            Deck = Graveyard;
            Shuffle();
            Graveyard.clear();
            //while (!Graveyard.empty())
            //Graveyard.erase(Graveyard.begin());
        }

        //cout << "Checking for busting " << current_player.Is_Busted(hand_number) << endl;
        if (current_player.Is_Busted(hand_number) == false)
        {
            int id = Deck[0].getId();
            current_player.Hit_card(hand_number, Deck[0]); //Adds the top card of the vector to the hand
            //current_player.getHand(hand_number).setDeck(this);
            Deck[0].setFaceDown(faceDown);
            Drawn_Cards.push_back(Deck[0]);
            //cout << "Setting cards_remaining[ " << id << "] to " << cards_remaining[id] - 1 << endl;
            if (faceDown == false)
            {
                changeCardCount(id, -1);
            }

            //Graveyard.push_back(Deck[0]);
            Deck.erase(Deck.begin()); //Removes the top card of the vector
            cout << "The value of the current hand is " << current_player.Get_Current_Hand_value(hand_number) << endl;
        }
        else
        {
            cout << "Current hand is busted!" << endl;
        }

    }

    /* Functions to help with keeping track of cards used, taking account of card value
       getLowCount()
       getHighCount()
       getCardCount()
       changeCardCount()
       setRemainingUsed()
    */
    int getLowCount()
    {
        if (remainingUsed)
        {
            return lowCountR;
        }
        return lowCountU;
    }

    int getHighCount()
    {
        if (remainingUsed)
        {
            return highCountR;
        }
        return highCountU;
    }

    int getCardCount(int index)
    {
        if (remainingUsed)
        {
            return cards_remaining[index];
        }
        return cards_used[index];
    }

    void changeCardCount(int index, int change)
    {
        cards_remaining[index] += change;
        cards_used[index] -= change;
        if (index <= 6)
        {
            lowCountR += change;
            lowCountU -= change;
        }
        else
        {
            highCountR += change;
            highCountU -= change;
        }
    }

    void setRemainingUsed(bool value)
    {
        remainingUsed = value;
    }

    ~deck()
    {
        Deck.clear();
        Graveyard.clear();
    }
};

#endif // DECK_H
