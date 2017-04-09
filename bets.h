#ifndef BETS_H
#define BETS_H

//#include "player.h"
#include <QRect>

struct Poker_chips
{
    QRect chip_coordinates;
    double total_amount;

    Poker_chips() {}
    Poker_chips(QRect temp, double price = 500.00)
    {
        chip_coordinates = temp;
        total_amount = price;
    }

};

class Bets
{
    private:
        vector<Poker_chips> Current_Bets;
    public:
    Bets()
    {
        Add_Bet(QRect(150, 335, 51, 51), 500.00);
    }
    Bets(double total_value)
    {
        Add_Bet(QRect(322, 405, 51, 51), total_value);
    }

    void Set_TotalChips(double value)
    {
        Current_Bets[0].total_amount = value;
    }

    double get_TotalChips()
    {
        return Current_Bets[0].total_amount;
    }

    void Add_Bet(QRect coords)
    {
        coords.setLeft(coords.left() + 35);
        coords.setRight(coords.right() + 35);
        Current_Bets.push_back(Poker_chips(coords, Current_Bets[Current_Bets.size()-1].total_amount));
        Current_Bets[0].total_amount -= Current_Bets[Current_Bets.size()-1].total_amount;

    }

    void Add_Bet(QRect coords, double price)
    {
        //Poker_chips temp;
        //temp.chip_coordinates = coords;
        //temp.total_amount = price;
        Current_Bets.push_back(Poker_chips(coords, price));
        Current_Bets[0].total_amount -= price;

    }

    void Set_Bets(int hand_num, double total_bet)
    {
        Current_Bets[0].total_amount -= Current_Bets[hand_num].total_amount;
        Current_Bets[hand_num].total_amount = total_bet;
    }

    int Get_BetCount()
    {
        return Current_Bets.size();
    }

    vector<Poker_chips> Get_Bets()
    {
        return Current_Bets;
    }

    void Lost_Hand(int hand_number)
    {
        Current_Bets[hand_number].total_amount = 0;
    }

    ~Bets()
    {
        Current_Bets.clear();
    }
};

#endif // BETS_H
