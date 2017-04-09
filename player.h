#ifndef PLAYER_H
#define PLAYER_H


#include "card.h"
#include "hand.h"
#include "bets.h"
#include <vector>
#include <QRect>
#include <iostream>

using namespace std;


class Player
{
private:
    vector<Hand> hands;  // Stores the information about a players hand(s)
    QRect card_coordinates; //Only seems to be used in the "Hit Cards" function. May be removed from this area later
    bool Is_player_dealer;
    vector<Poker_chips> chip_coordinates; //Stores information about players chips
    Bets players_bets;

    // Should add Is_Doubled_down() function for either cards or hand class. To be determined later...

    //int current_hand_count;  // Might not be necessary to have anymore.
public:
    Player()
    {
        hands.reserve(5);
        hands.resize(1);
        chip_coordinates.resize(2);
        Is_player_dealer = false;
    }

    Hand getHand(int id)
    {
        return hands[id];
    }

    //Checks to see if we can split the cards. If they are the same, then they can be splitted.
    bool Is_Splitable()
    {
        return hands[0].Same_Cards();
    }

    // Splits the cards into two seperate hands
    void Split()
    {
        int temp = 0;
        Card card;
        hands[0].Split_Cards(card, temp);
        hands.resize(hands.size() + 1);
        hands[hands.size() - 1].add_card(card, temp);


        int x = 322, y = 405, w = 51, h = 51;
        x = x + (32 * (hands.size() - 1));
        players_bets.Add_Bet(QRect(x, y, w, h));

    }

    void Double_Down()
    {
        int x = 322, y = 405, w = 51, h = 51;
        x = x + (32 * (hands.size() - 1));
        players_bets.Add_Bet(QRect(x, y, w, h));
    }

    // Get all the coordinates for the players poker chips
    vector<Poker_chips> Get_Poker_coordinates()
    {
        return players_bets.Get_Bets();
    }

    void Add_Bet(double val)
    {
        int x = 322, y = 405, w = 51, h = 51;
        x = x + (32 * (hands.size() - 1));
        QRect temp;
        temp.setRect(x, y, w, h);
        players_bets.Add_Bet(temp, val);
    }

    void Change_Bet(int bet_num, double value)
    {
        players_bets.Set_Bets(bet_num, value);
    }

    void Set_Total_ChipsAmount(double val)
    {
        players_bets.Set_TotalChips(val);
    }

    double Get_Total_ChipsAmount()
    {
        return players_bets.get_TotalChips();
    }


    // Shows the name of all the cards (for debugging purposes)
    void Display_Hands()
    {
        for (int i = 0; i < (int)hands.size(); ++i)
        {
            cout << "Hand " << i + 1 << ":" << endl;
            hands[i].Display_Cards();
        }
    }

    //Adds another card to the desired hand, returns bool value based on the result
    void Hit_card(int hand_number, Card& current_card)
    {
        // Maps out the next cards coordinates
        int x1, x2, y1, y2;

        if (hands[hand_number].Get_Card_Count() != 0)
        {
            hands[hand_number].get_Card_Coordinates(x1, y1, x2, y2);
        }
        else
        {
            x1 = 300;
            x2 = 360;
            if (Is_dealer())
            {
                y1 = 63;
                y2 = 153;

                //30, 120
            }
            else
            {
                y1 = 333;
                y2 = 423;
                //300, 390
            }
        }

        if (hands.size() == 1 || Is_dealer())
        {
            x1 = x1 + (30 * hands[hand_number].Get_Card_Count());
            x2 = x2 + (30 * hands[hand_number].Get_Card_Count());
        }
        else
        {
            y1 = y1 - (30 * hands[hand_number].Get_Card_Count());
            y2 = y2 - (30 * hands[hand_number].Get_Card_Count());
        }

        card_coordinates.setCoords(x1, y1, x2, y2);
        hands[hand_number].Add_Card(current_card, card_coordinates);

    }
    //Checks to see if the hand is able to double down
    bool Is_Double_Downable(int hand)
    {
        int Card_size = Get_Current_Hand_value(hand);
        int Ace_count = hands[hand].Ace_Count();
        int Non_ace_value = hands[hand].Non_Ace_value();
        cout << "Ace count is " << Ace_count << endl;
        cout << "Non ace value is " << Non_ace_value << endl;

        if ((Card_size >= 9 && Card_size <= 11) || (Non_ace_value + Ace_count >= 9 && Non_ace_value + Ace_count <= 11))
        {
            return true;
        }
        return false;
    }

    //Ends the turn for the current hand.
    void Hold() {}

    //Checks if the hand is busted or not
    bool Is_Busted(int hand_number)
    {
        int total;
        int temp;
        temp = hands.size();
        cout << "The current ammount of hands you have is " << temp << endl;
        total = hands[hand_number].Get_Total_value();
        if (total > 21)
            return true;
        else
            return false;
    }

    int Flip_Card(int hand_number)
    {
        return hands[hand_number].flip_card();
    }


    // Shows Hand onto the GUI screen
    void Show_Hand()
    {
        for (int i = 0; i < (int)hands.size(); ++i)
        {
            hands[i].Show_Cards();
        }
    }

    // Hides the hand from showing up on the GUI screen
    void Hide_Hand()
    {
        for (int i = 0; i < (int)hands.size(); ++i)
        {
            hands[i].Hide_Cards();
        }
    }

    //Gets the total value of the hand
    int Get_Current_Hand_value(int hand_number)
    {
        int temp = hands[hand_number].Get_Total_value();
        return temp;
    }

    //Returns the ammount of hands the player has
    int Get_Hand_Count()
    {
        return hands.size();
    }

    // Sets the player status (dealer or not?)
    void Set_Player_Identity(bool status)
    {
        Is_player_dealer = status;
    }

    // Checks if this is the dealer or not
    bool Is_dealer()
    {
        return Is_player_dealer;
    }

    //Manages the hand that just busted. (might remove the cards from the visual aspect)
    void Bust(int hand_number) { return; }

    ~Player() {
        hands.clear();
        Is_player_dealer = false;
    }

};

#endif // PLAYER_H

