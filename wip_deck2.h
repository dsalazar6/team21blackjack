#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "player.h"
#include <iostream>

using namespace std;
//A prototype implementation of the card counting.
//It is not yet complete and may be changed many times before the 2nd iteration is released.
class deck {
private:
    vector<Card> Deck;
    vector<Card> Graveyard;
    vector<Card> Drawn_Cards;
	int[13] cards_remaining;
	int num_decks;

public:
    deck() {}

    // Creates all the cards needed for the deck(s)
    void addStandardDeck(int decks_used)
    {
        Card temp;
		num_decks = decks_used;
        int total_cards = 52 * decks_used;
        for (int i = 0; i < total_cards; i++)
        {
            temp = Card(i);
            Deck.push_back(temp);
        }
		int temp = 4 * decks_used;
		card_remaining[0] = temp;
		card_remaining[1] = temp;
		card_remaining[2] = temp;
		card_remaining[3] = temp;
		card_remaining[4] = temp;
		card_remaining[5] = temp;
		card_remaining[6] = temp;
		card_remaining[7] = temp;
		card_remaining[8] = temp;
		card_remaining[9] = temp;
		card_remaining[10] = temp;
		card_remaining[11] = temp;
		card_remaining[12] = temp;
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
			int temp = 4 * num_decks;
			card_remaining[0] = temp;
			card_remaining[1] = temp;
			card_remaining[2] = temp;
			card_remaining[3] = temp;
			card_remaining[4] = temp;
			card_remaining[5] = temp;
			card_remaining[6] = temp;
			card_remaining[7] = temp;
			card_remaining[8] = temp;
			card_remaining[9] = temp;
			card_remaining[10] = temp;
			card_remaining[11] = temp;
			card_remaining[12] = temp;
            //while (!Graveyard.empty())
           //     Graveyard.erase(Graveyard.begin());
        }

        cout << "Checking for busting " << current_player.Is_Busted(hand_number) << endl;
        if (!current_player.Is_Busted(hand_number)) {
            current_player.Hit_card(hand_number, Deck[0]); //Adds the top card of the vector to the hand
            Drawn_Cards.push_back(Deck[0]);
			card_remaining[Deck[0].cardId[1]] --;
            //Graveyard.push_back(Deck[0]);
            Deck.erase(Deck.begin()); //Removes the top card of the vector
            cout << "The value of the current hand is "
                 << current_player.Get_Current_Hand_value(hand_number) << endl;
        }
        else {
            cout << "Current hand is busted!" << endl;
        }

    }
    ~deck()
	{
        Deck.clear();
        Graveyard.clear();
    }



};


#endif // DECK_H


