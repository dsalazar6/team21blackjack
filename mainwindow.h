#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QTextBrowser>
#include <vector>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

    // Stores all information about Player(s)
    vector<Player> players;

    // Stores information about the dealer. MUST REMAIN A VECTOR
    vector<Player> Dealer;

    vector<QTextBrowser*> Chip_Values;
    vector<QLabel*> Poker_Chips;
    vector<Poker_chips> Chips_coordinates;

    bool players_out;
    bool Dealers_Turn;
    int current_player_number;
    int current_hand_number;
    int Number_of_Players;
    int turns=1; //Patrick's modification
    bool surrender=false;
    int automatedBet=-1; //Patrick's automated bets

    QString Chip_name;
    QString Title_Message;
    QString Players_Turn;
    QString Dialog_Text;

    deck Deck;

private slots:

    void Update_Card_Count();

    // Whenever the user clicks on Hit, it will call this function
    void on_Hit_Button_clicked();

    // Whenever the user clicks on Stay, it will call this function
    void on_Stay_Button_clicked();

    // Whenever the user clicks on Split, it will call this function
    void on_Split_Button_clicked();

    // Whenever the user wants to start a new game
    void on_New_Game_clicked();

    //Whenever the user clicks on Double_Down, it will call this function
    void on_Double_Down_clicked();

    void on_Surrender_clicked();

    void on_pushButton_clicked();

    // Functions to change text colors for bust, surrender, win, and lose in the Settings - Color Settings
    void on_actionBust_triggered();

    void on_actionSurrender_triggered();

    void on_actionWin_triggered();

    void on_actionLose_triggered();

    // Functions to apply to the different Rule options of the game
    void on_actionDouble_Down_triggered();

    void on_actionDealer_Stays_on_triggered();

    void on_actionSurrender_return_values_triggered();

    void on_actionSplit_triggered();

    void on_actionChange_Autobet_triggered();

public:
    explicit MainWindow(QWidget *parent = 0);
   double gainslosses=0;

    //Patricks Modification for Turn increments and surrendering for bets
   //Is the user surrendering?
   const bool getSurrender(){
   return surrender;}
       ;
   void setUserSurrender(bool truefalse){
       surrender=truefalse;
   };
    const int get_Turn()
    {
        return turns;
    }
    void incrementTurn()
    {
        turns++;
    }

    //Could use two ints for Deck ammounts and player ammount
    void Create_Deck() { return; }

    // Starts the game over. Removes info about players, clears hands, and deletes all cards
    void New_Game();

    // This is called the first time when the game starts and whenever New_Game() is called
    void Start_Game();

    // Could allow the new game types to be accessed and returns a bool if done sucessfully or not
    bool Change_Game_Type(string game_type) { return false; }

    // You pass the total number of players and returns a bool if done sucessfully or not
    bool Add_Players(int total_players) { return false; }

    // For the betting part of this program
    bool Add_money() { return false; }

    //Clears out their money so they could "Cash out"
    bool Cash_out(string username) { return false; }

    // Allows the player to change to a different username
    bool Change_user(string username);

    const int getAutomatedBet(){
        return automatedBet;
    }
    void setAutoMatedBet(int automatedBet)
    {
     this->automatedBet= automatedBet;
    }

    ~MainWindow();

};

#endif // MAINWINDOW_H
