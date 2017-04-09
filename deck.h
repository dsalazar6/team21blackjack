#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "player.h"
#include <iostream>

using namespace std;
//Card counting implemented to keep track of exact values and the low/high count
class deck {
private:
    vector<Card> Deck;
    vector<Card> Graveyard;
    vector<Card> Drawn_Cards;
    int cards_remaining[13];
    int num_decks;
    int lowCount; //card is an Ace or 2-7
    int highCount; //card is 8 or above

public:
    deck() {}

    // Creates all the cards needed for the deck(s)
    void addStandardDeck(int decks_used)
    {
        Card Temp;
        num_decks = decks_used;
        int total_cards = 52 * decks_used;
        for (int i = 0; i < total_cards; i++)
        {
            Temp = Card(i);
            Deck.push_back(Temp);
        }
        cards_remaining[0] = 0;
        cards_remaining[1] = 0;
        cards_remaining[2] = 0;
        cards_remaining[3] = 0;
        cards_remaining[4] = 0;
        cards_remaining[5] = 0;
        cards_remaining[6] = 0;
        lowCount = 0;
        cards_remaining[7] = 0;
        cards_remaining[8] = 0;
        cards_remaining[9] = 0;
        cards_remaining[10] = 0;
        cards_remaining[11] = 0;
        cards_remaining[12] = 0;
        highCount = 0;
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
            /*int temp = 4 * num_decks;
            cards_remaining[0] = temp; //Ace
            cards_remaining[1] = temp; //Two
            cards_remaining[2] = temp; //Three
            cards_remaining[3] = temp; //Four
            cards_remaining[4] = temp; //Five
            cards_remaining[5] = temp; //Six
            cards_remaining[6] = temp; //Seven
            lowCount = 7 * temp;
            cards_remaining[7] = temp; //Eight
            cards_remaining[8] = temp; //Nine
            cards_remaining[9] = temp; //Ten
            cards_remaining[10] = temp; //Jack
            cards_remaining[11] = temp; //Queen
            cards_remaining[12] = temp; //King
            highCount = 6 * temp;*/
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

    int getLowCount()
    {
        return lowCount;
    }

    int getHighCount()
    {
        return highCount;
    }

    int getCardCount(int index)
    {
        return cards_remaining[index];
    }

    void changeCardCount(int index, int change)
    {
        cards_remaining[index] += change;
        if (index <= 6)
        {
            lowCount += change;
        }
        else
        {
            highCount += change;
        }
    }

    ~deck()
    {
        Deck.clear();
        Graveyard.clear();
    }
};


#endif // DECK_H



