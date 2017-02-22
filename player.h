#ifndef PLAYER_H
#define PLAYER_H


#include "card.h"
#include "hand.h"
#include <vector>
#include <QRect>
#include <iostream>

/*
#include <QApplication>
#include <QLabel>
#include "mainwindow.h"
#include <QMainWindow>
#include <QWidgetList>
#include <QWindowList>
#include "ui_mainwindow.h"
*/

using namespace std;


class Player {
public:
    Player() {
        hands.reserve(5);
        hands.resize(1);
        current_hand_count = 0;
        Is_player_dealer = false;
    }

    // Splits the cards into two seperate hands
    void Split() {
        int temp = 0;
        Card card;
        Hand nw_Hnd;
        //nw_Hnd.add_card(card, temp);
        hands[0].Split_Cards(card, temp);
        hands.push_back(nw_Hnd);
        hands[hands.size()-1].add_card(card, temp);
    }

    // Shows the name of all the cards (for debugging purposes)
    void Display_Hands() {
        for (int i = 0; i < (int)hands.size(); ++i) {
            cout << "Hand " << i+1 << ":" << endl;
            hands[i].Display_Cards();
        }
    }

    //Adds another card to the desired hand, returns bool value based on the result
    void Hit_card(int hand_number, Card& current_card) {
        // Maps out the next cards coordinates
        int x1 , x2, y1, y2;

        if (hands[hand_number].Get_Card_Count() != 0) {
        //Temporarly blocked. Look at function call for more details
            hands[hand_number].get_Card_Coordinates(x1, y1, x2, y2);
        }
        else {
                x1 = 300;
                x2 = 360;
                if (Is_dealer()) {
                    y1 = 30;
                    y2 = 120;
                }
                else {
                    y1 = 300;
                    y2 = 390;
                }
        }

        if (hands.size() == 1 || Is_dealer()) {
            x1 = x1 + (30 * hands[hand_number].Get_Card_Count());
            x2 = x2 + (30 * hands[hand_number].Get_Card_Count());
        }
        else {
            y1 = y1 - (30 * hands[hand_number].Get_Card_Count());
            y2 = y2 - (30 * hands[hand_number].Get_Card_Count());
        }
        /*
        if (!Is_dealer()) {
            if (hands.size() == 1) {//x1 = 300, x2 = 360
                x1 = 300 + (30 * hands[hand_number].Get_Card_Count());
                x2 = 360 + (30 * hands[hand_number].Get_Card_Count());
                y1 = 300;
                y2 = 390;
            }
            else {
                //The cards are split and are at different coordinates
                x1 = 300 + (30 * hand_number);
                x2 = 360 + (30 * hand_number);
                y1 = 300 - (30 * hands[hand_number].Get_Card_Count());
                y2 = 390 - (30 * hands[hand_number].Get_Card_Count());
            }
        }
        else {
            // Player is dealer and has different coordinates
            x1 = 300 + (30 * hands[hand_number].Get_Card_Count());
            x2 = 360 + (30 * hands[hand_number].Get_Card_Count());
            y1 = 30;
            y2 = 120;

        }
        */
        card_coordinates.setCoords(x1, y1, x2, y2);
         hands[hand_number].Add_Card(current_card, card_coordinates);

    }
    //Adds a card that shows the backside of the card until the end of the game
    bool Double_Down() {return false;}

    //Ends the turn for the current hand.
    void Hold() {}

    //Checks if the hand is busted or not
    bool Is_Busted(int hand_number) {
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


    // Shows Hand onto the GUI screen
    void Show_Hand() {
        for (int i = 0; i < (int)hands.size(); ++i) {
            hands[i].Show_Cards();
        }
    }

    // Hides the hand from showing up on the GUI screen
    void Hide_Hand() {
        for (int i = 0; i < (int)hands.size(); ++i) {
            hands[i].Hide_Cards();
        }
    }

    //Gets the total value of the hand
    int Get_Current_Hand_value(int hand_number) {
        int temp = hands[hand_number].Get_Total_value();
        return temp;
    }

    //Returns the ammount of hands the player has
    int Get_Hand_Count() {
        return hands.size();
    }

    // Sets the player status (dealer or not?)
    void Set_Player_Identity(bool status) {
        Is_player_dealer = status;
    }

    // Checks if this is the dealer or not
    bool Is_dealer() {
        return Is_player_dealer;
    }
    //Manages the hand that just busted. (might remove the cards from the visual aspect)
    void Bust(int hand_number) {return;}

    //This would clear the player at the end of every game.
    bool Clear_Player() {return false;}

    ~Player() {}

private:
    vector<Hand> hands;  // Stores the information about a players hand(s)
    QRect card_coordinates; //Only seems to be used in the "Hit Cards" function. May be removed from this area later
    bool Is_player_dealer;

    // Should add Is_Doubled_down() function for either cards or hand class. To be determined later...

    int current_hand_count;  // Might not be necessary to have anymore.



};

#endif // PLAYER_H
