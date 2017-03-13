#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <vector>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    //Could use two ints for Deck ammounts and player ammount
    void Create_Deck() {return;}

    // Starts the game over. Removes info about players, clears hands, and deletes all cards
    void New_Game();

    // This is called the first time when the game starts and whenever New_Game() is called
    void Start_Game();

    // Could allow the new game types to be accessed and returns a bool if done sucessfully or not
    bool Change_Game_Type(string game_type) {return false;}

    // You pass the total number of players and returns a bool if done sucessfully or not
    bool Add_Players(int total_players) {return false;}

    // For the betting part of this program
    bool Add_money() {return false;}

    //Clears out their money so they could "Cash out"
    bool Cash_out(string username) {return false;}

    // Allows the player to change to a different username
    bool Change_user(string username);



    ~MainWindow();


private slots:
    // Whenever the user clicks on Hit, it will call this function
    void on_Hit_Button_clicked();

    // Whenever the user clicks on Stay, it will call this function
    void on_Stay_Button_clicked();

    // Whenever the user clicks on Split, it will call this function
    void on_Split_Button_clicked();

    // Whenever the user wants to start a new game
    void on_New_Game_clicked();

private:
    Ui::MainWindow *ui;

    // Stores all information about Player(s)
    vector<Player> players;

    // Stores information about the dealer. MUST REMAIN A VECTOR
    vector<Player> Dealer;

    bool Dealers_Turn;
    int current_player_number;
    int current_hand_number;
    int Number_of_Players;

    QString Title_Message;
    QString Players_Turn;
    QString Dialog_Text;

    deck Deck;

};

#endif // MAINWINDOW_H
