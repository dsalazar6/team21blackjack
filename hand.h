#ifndef HAND_H
#define HAND_H

#include <vector>
#include "card.h"
#include <QLabel>
#include <QRect>
#include <iostream>
#include "mainwindow.h"


using namespace std;

extern QList<QLabel*> Images;
extern int free_index;

class Hand {
public:
    Hand() {
        Ace_found = false;
        Ace_index = 0;
        card_size = 0;
        Doubled_down = false;
        busted = false;
        //cards.reserve(10);
        //images.reserve(10);
        cards.resize(0);
        //images.resize(1);
    }

    //Adds a card to the hand
    void Add_Card(Card& cardinfo,QRect image_coordinates) {
        cards.push_back(cardinfo);

        //Saves the image of the card and the coordinates in the GUI Array
        //To be displayed onto the GUI Display
        Images[free_index]->setPixmap(cardinfo.getFileName());
        Images[free_index]->setGeometry(image_coordinates);
        Images[free_index]->show();
        image_indexes.push_back(free_index);
        ++free_index;

        //images.push_back(temp);
    }

    // This is used for when the user splits cards
    // It is unessecary for the card image to be created again,
    // so we direct the hands card to the previous index in the array
    void add_card(Card& cardinfo, int card_index) {
        cards.push_back(cardinfo);
        image_indexes.push_back(card_index);

    }

    // This outputs all the cards that are in the hand (for debugging purposes)
    void Display_Cards() {
        for (int i = 0; i < (int)cards.size(); ++i) {
            cout << cards[i].getName() << endl;
        }
    }

    // Makes the cards visible for the GUI screen
    void Show_Cards() {
        for (int i = 0; i < (int)image_indexes.size(); ++i) {
            Images[image_indexes[i]]->show();
        }
    }

    // Makes the cards invisible for the GUI screen
    void Hide_Cards() {
        for (int i = 0; i < (int)image_indexes.size(); ++i) {
            Images[image_indexes[i]]->hide();
        }
    }

    //Gets The total Worth of the Hand (ex: The value of the hand is 21)
    int Get_Total_value() {
        int total = 0;
        for(int i = 0; i < (int)cards.size(); ++i) {
            if (cards[i].getMinValue() != cards[i].getValue()) {
                Ace_found = true;
                Ace_index= i;
            }
            total += cards[i].getValue();
        }
        // If there is an ace and its greater than 21, use the ace as value 1
        // There might be an issue here with multiple Aces in the cards
        // Replace vector Ace_index[0] with something else later
         if (total > 21 && Ace_found == true && (cards[Ace_index].getMinValueUsed() == false)) {
                cards[Ace_index].useMinValue();
                total -= 10;
        }
        return total;
    }

    //Returns how many cards are in the current hand
    int Get_Card_Count() {
        return cards.size();
    }

    bool Is_Busted() {return true;} //Returns if this hand is busted or not
    void Double_down_hand() {} //Makes the last cards image the backside of the card until the end of the game


    void get_Card_Coordinates(int& x1, int& y1, int& x2, int& y2) {
       //Has the issue of on the first cards that it doesn't have any qeometry
       // Need to fix this somehow
            QRect temp = Images[image_indexes[0]]->geometry();
            int *_x1, *_y1, *_x2, *_y2;
            _x1 = &x1;
            _y1 = &y1;
            _x2 = &x2;
            _y2 = &y2;
            temp.getCoords(_x1, _y1, _x2, _y2);

    }

    void Set_Card_Coordinates(int image_index, QRect coords) {

    }

    // Starts the process of spliting the cards by taking/removing the last card from the hand
    // Also saves the index of where the last card was located
    void Split_Cards(Card& current_card, int& Image_index) {
        Image_index = image_indexes[image_indexes.size()-1];
        image_indexes.pop_back();
        QRect temp = Images[Image_index]->geometry();
        int _x1, _x2, _y1, _y2;
        int *x1 = &_x1,
            *x2 = &_x2,
            *y1 = &_y1,
            *y2 = &_y2;

        temp.getCoords(x1, y1, x2, y2);

        _x1 = _x1 + 50;
        _x2 = _x2 + 50;
        temp.setCoords(_x1, _y1, _x2, _y2);
        Images[Image_index]->setGeometry(temp);

        current_card = cards[cards.size()-1];
        cards.pop_back();
    }


    ~Hand() {}

private:
    vector<Card> cards;
    int card_size;
    vector<int> image_indexes; //Contains the indexes of the cards in the GUI Array
    bool busted;
    bool Ace_found;
    int Ace_index;
    bool Doubled_down;
};


#endif // HAND_H
