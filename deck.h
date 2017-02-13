#ifndef DECK_H
#define DECK_H
#include "card.h"

#include <iostream>
using namespace std;

class deck {
public:
    deck() {}
    void addStandardDeck(vector<Card> &Deck)
    {
        //Aces
        Card AceSpades("Ace of Spades",1, 11);
        Deck.push_back(AceSpades);

        Card AceHearts("Ace of Hearts", 1, 11);
        Deck.push_back(AceHearts);

        Card AceDiamonds("Ace of Diamonds", 1, 11);
        Deck.push_back(AceDiamonds);

        Card AceClubs("Ace of Clubs", 1, 11);
        Deck.push_back(AceClubs);

        //TWOS
        Card TwoSpades("Two of Spades", 2, 2);
        Deck.push_back(TwoSpades);

        Card TwoHearts("Two of Hearts", 2, 2);
        Deck.push_back(TwoHearts);

        Card TwoDiamonds("Two of Diamonds", 2, 2);
        Deck.push_back(TwoDiamonds);

        Card TwoClubs("Two of Clubs", 2, 2);
        Deck.push_back(TwoClubs);

        //THREES
        Card ThreeSpades("Three of Spades", 3, 3);
        Deck.push_back(ThreeSpades);

        Card ThreeHearts("Three of Hearts", 3, 3);
        Deck.push_back(ThreeHearts);

        Card ThreeDiamonds("Three of Diamonds", 3, 3);
        Deck.push_back(ThreeDiamonds);

        Card ThreeClubs("Three of Clubs", 3, 3);
        Deck.push_back(ThreeClubs);

        //FOURS
        Card FourSpades("Four of Spades", 4, 4);
        Deck.push_back(FourSpades);

        Card FourHearts("Four of Hearts", 4, 4);
        Deck.push_back(FourHearts);

        Card FourDiamonds("Four of Diamonds", 4, 4);
        Deck.push_back(FourDiamonds);

        Card FourClubs("Four of Clubs", 4, 4);
        Deck.push_back(FourClubs);


        //FIVES
        Card FiveSpades("Five of Spades", 5, 5);
        Deck.push_back(FiveSpades);

        Card FiveHearts("Five of Spades", 5, 5);
        Deck.push_back(FiveHearts);

        Card FiveDiamonds("Five of Spades", 5, 5);
        Deck.push_back(FiveDiamonds);

        Card FiveClubs("Five of Spades", 5, 5);
        Deck.push_back(FiveClubs);

        //SIXES
        Card SixSpades("Six of Spades", 6, 6);
        Deck.push_back(SixSpades);

        Card SixHearts("Six of Spades", 6, 6);
        Deck.push_back(SixHearts);

        Card SixDiamonds("Six of Spades", 6, 6);
        Deck.push_back(SixDiamonds);

        Card SixClubs("Six of Spades", 6, 6);
        Deck.push_back(SixClubs);

        //SEVENS
        Card SevenSpades("Seven of Spades", 7, 7);
        Deck.push_back(SevenSpades);

        Card SevenHearts("Seven of Spades", 7, 7);
        Deck.push_back(SevenHearts);

        Card SevenDiamonds("Seven of Spades", 7, 7);
        Deck.push_back(SevenDiamonds);

        Card SevenClubs("Seven of Spades", 7, 7);
        Deck.push_back(SevenClubs);

        //EIGHTS
        Card EightSpades("Eight of Spades", 8, 8);
        Deck.push_back(EightSpades);

        Card EightHearts("Eight of Spades", 8, 8);
        Deck.push_back(EightHearts);

        Card EightDiamonds("Eight of Spades", 8, 8);
        Deck.push_back(EightDiamonds);

        Card EightClubs("Eight of Spades", 8, 8);
        Deck.push_back(EightClubs);

        //NINES
        Card NineSpades("Nine of Spades", 9, 9);
        Deck.push_back(NineSpades);

        Card NineHearts("Nine of Spades", 9, 9);
        Deck.push_back(NineHearts);

        Card NineDiamonds("Nine of Spades", 9, 9);
        Deck.push_back(NineDiamonds);

        Card NineClubs("Nine of Spades", 9, 9);
        Deck.push_back(NineClubs);

        //TENS
        Card TenSpades("Ten of Spades", 10, 10);
        Deck.push_back(TenSpades);

        Card TenHearts("Ten of Spades", 10, 10);
        Deck.push_back(TenHearts);

        Card TenDiamonds("Ten of Diamonds", 10, 10);
        Deck.push_back(TenDiamonds);

        Card TenClubs("Ten of Clubs", 10, 10);
        Deck.push_back(TenClubs);



        //JACKS
        Card JackSpades("Jack of Spades", 10, 10);
        Deck.push_back(JackSpades);

        Card JackHearts("Jack of Hearts", 10, 10);
        Deck.push_back(JackHearts);

        Card JackDiamonds("Jack of Diamonds", 10, 10);
        Deck.push_back(JackDiamonds);

        Card JackClubs("Jack of Clubs", 10, 10);
        Deck.push_back(JackClubs);

        //QUEENS
        Card QueenSpades("Queen of Spades", 10, 10);
        Deck.push_back(QueenSpades);

        Card QueenHearts("Queen of Hearts", 10, 10);
        Deck.push_back(QueenHearts);

        Card QueenDiamonds("Queen of Diamonds", 10, 10);
        Deck.push_back(QueenDiamonds);

        Card QueenClubs("Queen of Clubs", 10, 10);
        Deck.push_back(QueenClubs);

        //KINGS

        Card KingSpades("King of Spades", 10, 10);
        Deck.push_back(KingSpades);

        Card KingHearts("King of Hearts", 10, 10);
        Deck.push_back(KingHearts);

        Card KingDiamonds("King of Diamonds", 10, 10);
        Deck.push_back(KingDiamonds);

        Card KingClubs("King of Clubs", 10, 10);
        Deck.push_back(KingClubs);
    }

    //returns random number
    int getRandomNumber(int max)
    {
        return (rand() % max);
    }

    void Shuffle(vector<Card> &Deck) //shuffle script
    {
        int j = 0;
        int rnd;

        for (int i = 0; i < Deck.size(); i++)
        {
            rnd = getRandomNumber(Deck.size()); //From the function above, it will generate a random number from the size of the deck being shuffled
            j = rnd; //every time this loops, it will select a random card from the list
            Card tmp = Deck[i]; //the first card is temporarily copied here.
            Card b = Deck[j];  //the second card is randomly selected
            Deck[i] = Deck[j];    //the first card becomes the second card
            Deck[j] = tmp;     //the second card becomes what the temp card copied.

                               // cout << Deck[i].getName() + " and " + Deck[j].getName() + " have swapped\n"; //used to see what's getting swapped

                               //thus they swap
        } // this will loop until we've gone through the entire deck.
        cout << "The deck has been shuffled\n";
    }

    //The Deck will give a player or dealer one card from the top of the deck.
    //If there are no cards in the deck, the cards from the graveyard will be added to the deck and the deck will be shuffled, then the hand will recieve a card
    //If the hand breaks the maximum, it will look for the first multivalued card and alter its value by the min value, then make let the vector know not to use that same card again
    //If the Hand busts all hands in play will go to the graveyard
    void draw(vector<Card> &Deck, vector<Card> &Hand, vector<Card> &Graveyard, int &value, bool &bust)
    {
        if (Deck.empty())
        {
            cout << "The deck has run out of cards and will be reshuffled with the discarded cards.\n";
            Deck = Graveyard;
            Shuffle(Deck);
            while (!Graveyard.empty())
                Graveyard.erase(Graveyard.begin());
        }
        Hand.push_back(Deck[0]); //Adds the top card of the vector to the hand
        Deck.erase(Deck.begin()); //Removes the top card of the vector

        //cout << "The card drawn is " << Hand[Hand.size()-1].getName() << endl;
        value += Hand[Hand.size()-1].getValue();
        if (value > 21)
        {
            for (int i = 0; i < Hand.size(); i++)
            {
                if (Hand[i].getMinValue() != Hand[i].getValue()); //if it's a multivalued card and the value hasn't changed
                {
                    if (!Hand[i].getMinValueUsed())
                    {
                        Hand[i].useMinValue();
                        value -= (Hand[i].getValue() - Hand[i].getMinValue());
                        i = Hand.size();
                    }
                }
            }
        }
        //cout << "The value of the current hand is " << value<< endl;
        if (value > 21)
        {
            //cout << "The hand has busted.\n";
            bust = true;
        }
    }
    ~deck() {}

};


#endif // DECK_H
