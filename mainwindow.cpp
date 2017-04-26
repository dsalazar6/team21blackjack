#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRect>
#include <QString>
#include <QTextBrowser>
#include <QInputDialog>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>


QList<QLabel*> Images;
int free_index = 0;
bool showPrecise = true; //if set to true, shows the count of each type of card
bool showUsed = true; //if set to false, shows the cards left in the deck and if true, shows cards in hand and in discard
bool doubledDown = false;
QString bustColor = "black";
QString surrenderColor = "black";
QString winColor = "black";
QColor defaultColor = "black";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap picBust("C:/Users/Anguyen14/Documents/QT/build-Blackjack-Desktop_Qt_5_8_0_MinGW_32bit-Debug/bust.jpg"); //Place the image location here for the "bust" image, use only '/' slashes
    QPixmap picWin("C:/Users\Anguyen14/Documents/QT/build-Blackjack-Desktop_Qt_5_8_0_MinGW_32bit-Debug/win.jpg");   //Place the image location here for the "win" image, use only '/' slashes
    QPixmap picLoss("C:/Users/Anguyen14/Documents/QT/build-Blackjack-Desktop_Qt_5_8_0_MinGW_32bit-Debug/dealerwon.png");   //Place the image location here for the "win" image, use only '/' slashes
    //image size should be 520x218

    ui->labelWin->setPixmap(picWin);
    ui->labelBust->setPixmap(picBust);
    ui->labelLoss->setPixmap(picLoss);

    //USE THIS TO PLAY BUST
                QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
                ui->labelBust->setGraphicsEffect(eff);
                QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
                a->setDuration(5000);
                a->setStartValue(0); //change this to 1
                a->setEndValue(0);
                a->start(QPropertyAnimation::DeleteWhenStopped);

    // USE THIS TO PLAY WIN
                QGraphicsOpacityEffect *eff2 = new QGraphicsOpacityEffect(this);
                ui->labelWin->setGraphicsEffect(eff2);
                QPropertyAnimation *b = new QPropertyAnimation(eff2,"opacity");
                b->setDuration(5000);
                b->setStartValue(0); //change this to 1
                b->setEndValue(0);
                b->start(QPropertyAnimation::DeleteWhenStopped);

    // USE THIS TO PLAY LOSS
                QGraphicsOpacityEffect *eff3 = new QGraphicsOpacityEffect(this);
                ui->labelLoss->setGraphicsEffect(eff3);
                QPropertyAnimation *c = new QPropertyAnimation(eff3,"opacity");
                c->setDuration(5000);
                c->setStartValue(0); //change this to 1
                c->setEndValue(0);
                c->start(QPropertyAnimation::DeleteWhenStopped);

    Chip_name = "Poker_Chip.png";
    //Change_user("BOB");
    for (int i = 0; i < 52; ++i)
    {
        Images.push_back(new QLabel(this));
    }

    for (int i = 0; i < 3; ++i)
    {
        Chip_Values.push_back(new QTextBrowser(this));
    }
    Chip_Values[2]->hide();
    Title_Message = "BlackJack Game: Version 1.9";
    this->setWindowTitle(Title_Message);
    Deck.addStandardDeck(1);
    Deck.Shuffle();
    //Asks for the number of players playing
    Number_of_Players = 1;
    //Asks for the number of players. DO NOT DELETE!!
    /*
    do {
    Number_of_Players = QInputDialog::getInt(this, "Player Counter", "Please enter the number of players currently playing(Maximum 5)");
    } while(Number_of_Players < 1 || Number_of_Players > 5);

    */
    Start_Game();
}

void MainWindow::Update_Card_Count()
{
    Deck.setRemainingUsed(!showUsed);
    if (!showUsed)
    {
        if (showPrecise)
        {
            ui->textBrowser_2->setText(QString("Aces remaining: ") + QString::number(Deck.getCardCount(0)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nTwos remaining: ") + QString::number(Deck.getCardCount(1)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nThrees remaining: ") + QString::number(Deck.getCardCount(2)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nFours remaining: ") + QString::number(Deck.getCardCount(3)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nFives remaining: ") + QString::number(Deck.getCardCount(4)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nSixes remaining: ") + QString::number(Deck.getCardCount(5)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nSevens remaining: ") + QString::number(Deck.getCardCount(6)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nEights remaining: ") + QString::number(Deck.getCardCount(7)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nNines remaining: ") + QString::number(Deck.getCardCount(8)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nTens remaining: ") + QString::number(Deck.getCardCount(9)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nJacks remaining: ") + QString::number(Deck.getCardCount(10)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nQueens remaining: ") + QString::number(Deck.getCardCount(11)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nKings remaining: ") + QString::number(Deck.getCardCount(12)));
        }
        else
        {
            ui->textBrowser_2->setText(QString("Low Cards (A-7) remaining: ") + QString::number(Deck.getLowCount()));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nHigh Cards(8 - K) remaining: ") + QString::number(Deck.getHighCount()));
        }
    }
    else
    {
        if (showPrecise)
        {
            ui->textBrowser_2->setText(QString("Aces used: ") + QString::number(Deck.getCardCount(0)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nTwos used: ") + QString::number(Deck.getCardCount(1)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nThrees used: ") + QString::number(Deck.getCardCount(2)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nFours used: ") + QString::number(Deck.getCardCount(3)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nFives used: ") + QString::number(Deck.getCardCount(4)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nSixes used: ") + QString::number(Deck.getCardCount(5)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nSevens used: ") + QString::number(Deck.getCardCount(6)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nEights used: ") + QString::number(Deck.getCardCount(7)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nNines used: ") + QString::number(Deck.getCardCount(8)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nTens used: ") + QString::number(Deck.getCardCount(9)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nJacks used: ") + QString::number(Deck.getCardCount(10)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nQueens used: ") + QString::number(Deck.getCardCount(11)));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nKings used: ") + QString::number(Deck.getCardCount(12)));
        }
        else
        {
            ui->textBrowser_2->setText(QString("Low Cards (A-7) used: ") + QString::number(Deck.getLowCount()));
            ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText() + QString("\nHigh Cards(8 - K) used: ") + QString::number(Deck.getHighCount()));
        }
    }

}

void MainWindow::Start_Game()
{
    ui->New_Game->hide();
    ui->Split_Button->hide();
    ui->Double_Down->hide();
    ui->Surrender->show();
    for (int i = 0; i < 5; ++i)
    {
        Poker_Chips.push_back(new QLabel(this));
        Poker_Chips[i]->setPixmap(Chip_name);
        Poker_Chips[i]->hide();
    }
    current_player_number = 0;
    current_hand_number = 0;
    Dealers_Turn = false;
    players.resize(Number_of_Players);
    Dealer.resize(1);
    Chips_coordinates = players[0].Get_Poker_coordinates();
    //Poker_Chips.resize(1);
    //Chips_coordinates.resize(1);
    Dealer[0].Set_Player_Identity(true);
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < (int)players.size(); ++j)
        {
            Deck.draw(players[j], 0); //Draws the first player and is their first hand
            if (j != 0)
                players[j].Hide_Hand();
        }
        Deck.draw(Dealer[0], 0, i == 1);
        if (i == 1)
            Dealer[0].Flip_Card(0);
    }

    Update_Card_Count();

    for (int k = 0; k <= (int)players.size(); ++k)
    {
        if (k == (int)players.size()) {
            cout << "The Dealers Cards are the Following:" << endl;
            Dealer[0].Display_Hands();
        }
        else {
            cout << "Player #" << k + 1 << " Cards are the Following:" << endl;
            players[k].Display_Hands();
        }
    }

    Players_Turn = "<font color=black>It is currently player #";
    Players_Turn += QString::number(current_player_number + 1);
    Players_Turn += "'s Turn</font><br>";
    ui->textBrowser->setText(Players_Turn);

    for (int i = 0; i < Number_of_Players; ++i)
    {
        players[i].Set_Total_ChipsAmount(500.00+gainslosses);
        if (players[i].Get_Total_ChipsAmount() <= 0) {
            QMessageBox::information(this, "GAME OVER", "You have run out of money to bet. The game will now close.");
            QApplication::quit();
        }
        else {
            Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));

            double bet_amount;
            do
            {
                bet_amount = QInputDialog::getInt(this, "Bet_Value", "Please enter the bet amount you want to put in(Minimum $5.00)",5);
            }
            while (bet_amount < 5.00 || bet_amount > players[i].Get_Total_ChipsAmount());

        players[i].Add_Bet(bet_amount);
        }
    }

    Chips_coordinates = players[current_player_number].Get_Poker_coordinates();
    for (int i = 0; i < 2; ++i)
    {
        Poker_Chips[i]->setGeometry(Chips_coordinates[i].chip_coordinates);
    }

    Poker_Chips[0]->show();
    Poker_Chips[1]->show();
    /*Poker_Chips[0]->setGeometry(Chips_coordinates[0].chip_coordinates);
    Poker_Chips[1]->setGeometry(Chips_coordinates[1].chip_coordinates);
    ui->textBrowser_2->setText(QString("Total_Chips: " +  QString::number(players[current_player_number].Get_Total_ChipsAmount())));*/
    Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));
    Chip_Values[0]->setGeometry(QRect(110, 400, 131, 31));
    Chip_Values[1]->setText(QString("$ " + QString::number(Chips_coordinates[1].total_amount)));
    QRect temp = Chips_coordinates[1].chip_coordinates;
    temp.setTop(temp.top() + 50);
    temp.setX(temp.x() - 20);
    temp.setWidth(70);
    temp.setHeight(20);
    Chip_Values[1]->setGeometry(temp);

    if (players[current_player_number].Is_Splitable())
        ui->Split_Button->show();

    if (players[current_player_number].Is_Double_Downable(current_hand_number))
        ui->Double_Down->show();
}

// This needs to check the hand size and needs to allow them to hit based on how many hands they have
void MainWindow::on_Hit_Button_clicked()
{
    if (Dealers_Turn)
        Deck.draw(Dealer[0], 0);
    else
    {
        if (ui->Split_Button->isVisible())
            ui->Split_Button->hide();
        if (ui->Surrender->isVisible())
            ui->Surrender->hide();

        Deck.draw(players[current_player_number], current_hand_number);
        if (players[current_player_number].Is_Double_Downable(current_hand_number))
            ui->Double_Down->show();
        else
            ui->Double_Down->hide();
    }
   /*if (Dealers_Turn)
    {
        if (Dealer[0].Is_Busted(0))
        {
            ;//Dialog_Text = "Dealer Busted with a value of " + QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n";
        }
        else
            ;//Dialog_Text = "Dealers current hand value is " + QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n";
    }
    else
    {
        if (players[current_player_number].Is_Busted(current_hand_number))
        {
            //Dialog_Text = "You Busted with a value of " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n";
            //ui->textBrowser->setText("You Busted with a value of " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n");
            on_Stay_Button_clicked();
            gainslosses -= (Chips_coordinates[1].total_amount);
            return;
        }
        else
        {
            Dialog_Text = "Your current hand value is " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n";

            ui->textBrowser->setText((QString)"Your current hand value is " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + (QString)"\n");
        }
    }*/
    if (Dealers_Turn)
        {
            if (Dealer[0].Is_Busted(0))
            {
                QGraphicsOpacityEffect *eff2 = new QGraphicsOpacityEffect(this);
                ui->labelWin->setGraphicsEffect(eff2);
                QPropertyAnimation *b = new QPropertyAnimation(eff2,"opacity");
                b->setDuration(5000);
                b->setStartValue(1);
                b->setEndValue(0);
                b->start(QPropertyAnimation::DeleteWhenStopped);
                ;//Dialog_Text = "Dealer Busted with a value of " + QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n";
            }
            else
                ;//Dialog_Text = "Dealers current hand value is " + QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n";
        }
        else
        {
            if (players[current_player_number].Is_Busted(current_hand_number))
            {
                //Dialog_Text = "You Busted with a value of " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n";
                //ui->textBrowser->setText("You Busted with a value of " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n");
                on_Stay_Button_clicked();
                gainslosses -= (Chips_coordinates[1].total_amount);


                //Play Bust animation
                ui->labelBust->show();

                QGraphicsOpacityEffect *eff2 = new QGraphicsOpacityEffect(this);
                ui->labelBust->setGraphicsEffect(eff2);
                QPropertyAnimation *b = new QPropertyAnimation(eff2,"opacity");
                b->setDuration(5000);
                b->setStartValue(1);
                b->setEndValue(0);
                b->start(QPropertyAnimation::DeleteWhenStopped);
                return;
            }
            else
            {
                Dialog_Text = "Your current hand value is " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n";
                ui->textBrowser->setText((QString)"Your current hand value is " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + (QString)"\n");
            }
        }


    if (!players_out)
    {
        Dialog_Text = Players_Turn + "\n" +Dialog_Text;
        ui->textBrowser->setTextColor(defaultColor);
        ui->textBrowser->setText(Dialog_Text);
    }
    Update_Card_Count();
}

void MainWindow::New_Game()
{
    Deck.Discard_Current_Cards();
    players.clear();
    Dealer.clear();
    Poker_Chips[2]->hide();
    Poker_Chips.clear();
    Chip_Values[2]->hide();
    ui->textBrowser->setText(QString(""));
    Start_Game();
}

void MainWindow::on_Stay_Button_clicked()
{
    if (ui->Surrender->isVisible())
        ui->Surrender->hide();
    cout << "Players size is " << players.size() << endl;
    if (Dealers_Turn == true)
    {
        Dealers_Turn = false;
        current_player_number = 0;
        Players_Turn = "It is currently player #1's turn\n";
        players[players.size() - 1].Hide_Hand();
        players[0].Show_Hand();
    }

    else if (int(players.size()) == (current_player_number + 1) && (players[current_player_number].Get_Hand_Count() - 1 == current_hand_number))
    {
        Dealers_Turn = true;
        int id = Dealer[0].Flip_Card(0);
        Deck.changeCardCount(id, -1);
        Players_Turn = "<font color=black>It is currently the Dealer's turn";
        current_hand_number = 0;

        players_out = true;
        for (int i = 0; i < players[current_player_number].Get_Hand_Count();++i)
        {
            if (!(players[current_player_number].Is_Busted(i)))
            {
                players_out = false;
            }
        }

        if (players_out)
        {
            QColor color1 = bustColor;
            ui->textBrowser->setTextColor(color1);
            ui->textBrowser->append("You Busted with a value of " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)));
            ui->textBrowser->append("<font color=black>\nThe Dealer Won!\n</font>");
            //
            ui->New_Game->show();
            return;
        }
        Update_Card_Count();

        while (Dealer[0].Get_Current_Hand_value(0) < 17)
        {
            on_Hit_Button_clicked();
            Players_Turn += "<br>The Dealer has a Total of ";
            Players_Turn += QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n</font>";
        }

        if (Dealer[0].Get_Current_Hand_value(0) > 21)
        {
            Players_Turn += "<br>The Dealer has Busted!\n</font><br>";
            ui->textBrowser->setTextColor(defaultColor);
            ui->textBrowser->setText(QString(Players_Turn));
            for (int i = 0; i < players[current_player_number].Get_Hand_Count();++i)
            {
                if (!(players[current_player_number].Is_Busted(i)) && !getSurrender())
                {
                    //we need to update the bet money at this point
                    QColor color3 = winColor;
                    ui->textBrowser->setTextColor(color3);
                    ui->textBrowser->setText(ui->textBrowser->toPlainText() + QString("Player 1 hand ") + QString::number(i + 1) + QString(": won \n"));
                    gainslosses+=(Chips_coordinates[1].total_amount);

                    //Play win animation
                    QGraphicsOpacityEffect *eff2 = new QGraphicsOpacityEffect(this);
                    ui->labelWin->setGraphicsEffect(eff2);
                    QPropertyAnimation *b = new QPropertyAnimation(eff2,"opacity");
                    b->setDuration(5000);
                    b->setStartValue(1);
                    b->setEndValue(0);
                    b->start(QPropertyAnimation::DeleteWhenStopped);
                }
            }
            for (int i = 0; i < players[current_player_number].Get_Hand_Count();++i)
            {
                Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));
            }

        }
        else
        {
            int Dealer_total = Dealer[0].Get_Current_Hand_value(0);
            bool Dealer_Beat_someone = false;
            ui->textBrowser->setText(QString(""));
            for (int i = 0; i < players[current_player_number].Get_Hand_Count(); ++i)
            {
                if (Dealer_total < players[current_player_number].Get_Current_Hand_value(i) && players[current_player_number].Get_Current_Hand_value(i) < 22 && !getSurrender())
                {
                    QColor color3 = winColor;
                    ui->textBrowser->setTextColor(color3);
                    ui->textBrowser->setText(ui->textBrowser->toPlainText() + QString("Player 1 hand ") + QString::number(i + 1) + QString(": won \n"));
                    gainslosses+=(Chips_coordinates[1].total_amount);
                    if (doubledDown)
                    {
                        gainslosses+=(Chips_coordinates[1].total_amount);
                    }

                    //Play win animation
                    QGraphicsOpacityEffect *eff2 = new QGraphicsOpacityEffect(this);
                    ui->labelWin->setGraphicsEffect(eff2);
                    QPropertyAnimation *b = new QPropertyAnimation(eff2,"opacity");
                    b->setDuration(5000);
                    b->setStartValue(1);
                    b->setEndValue(0);
                    b->start(QPropertyAnimation::DeleteWhenStopped);

                }
                else
                {
                    Dealer_Beat_someone = true;
                    /*if (!getSurrender())
                    {
                         ui->textBrowser->setText(ui->textBrowser->toPlainText() + QString("Player 1 hand ") + QString::number(i + 1) + QString(": lost \n"));
                        gainslosses-=(Chips_coordinates[1].total_amount);
                        if (doubledDown)
                        {
                            gainslosses-=(Chips_coordinates[1].total_amount);
                        }
                        ui->textBrowser->setText(ui->textBrowser->toPlainText() + QString("Dealer won"));
                    }*/
                }

            }
             Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));
            if (Dealer_Beat_someone && !getSurrender())
            {
                gainslosses-=(Chips_coordinates[1].total_amount);
                if (doubledDown)
                {
                    gainslosses-=(Chips_coordinates[1].total_amount);
                }
                ui->textBrowser->setText(ui->textBrowser->toPlainText() + QString("Dealer won"));

                //Play loss animation

                QGraphicsOpacityEffect *eff3 = new QGraphicsOpacityEffect(this);
                ui->labelLoss->setGraphicsEffect(eff3);
                QPropertyAnimation *c = new QPropertyAnimation(eff3,"opacity");
                c->setDuration(5000);
                c->setStartValue(1);
                c->setEndValue(0);
                c->start(QPropertyAnimation::DeleteWhenStopped);

            }
        }
        setUserSurrender(false);
        ui->New_Game->show();
    }
    else
    {
        if (current_hand_number == (int)players[current_player_number].Get_Hand_Count() - 1)
        {
            current_hand_number = 0;
            players[current_player_number].Hide_Hand();
            ++current_player_number;
            players[current_player_number].Show_Hand();
            Players_Turn = "It is currently player #";
            Players_Turn += QString::number(current_player_number + 1);
            Players_Turn += "'s Turn\n";
        }
        else
        {
            ++current_hand_number;
            Players_Turn = "It is currently player #";
            Players_Turn += QString::number(current_player_number + 1);
            Players_Turn += "'s Turn\nHand number " + QString::number(current_hand_number + 1);
        }//ui->textBrowser->setText(Players_Turn);
    }
    ui->Split_Button->hide();
    ui->Double_Down->hide();
}

void MainWindow::on_Split_Button_clicked()
{
    if (players[current_player_number].Get_Total_ChipsAmount() - Chips_coordinates[Chips_coordinates.size() - 1].total_amount > 0)
    {
        players[current_player_number].Split();
        current_hand_number = 0;
        Chips_coordinates[1].total_amount *= 2;
        ui->Split_Button->hide();
        ui->Surrender->hide();
        Chips_coordinates = players[current_player_number].Get_Poker_coordinates();
        QRect temp = Chips_coordinates[Chips_coordinates.size() - 1].chip_coordinates;
        temp.setTop(temp.top() + 50);
        temp.setWidth(70);
        temp.setHeight(20);
        Chip_Values[Chips_coordinates.size() - 1]->setGeometry(temp);
        Chip_Values[Chips_coordinates.size() - 1]->setText(QString("$ " + QString::number(Chips_coordinates[Chips_coordinates.size() - 1].total_amount)));
        Poker_Chips[Chips_coordinates.size() - 1]->setGeometry(Chips_coordinates[Chips_coordinates.size() - 1].chip_coordinates);
        Poker_Chips[Chips_coordinates.size() - 1]->show();
        Chip_Values[Chips_coordinates.size() - 1]->show();
        Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));
    }
    else
    {
        ui->textBrowser->setText(QString("You do not have enough money for a split"));
    }
}

void MainWindow::on_Double_Down_clicked()
{
    //Do the bet for doubling down
    if (players[current_player_number].Get_Total_ChipsAmount() - Chips_coordinates[Chips_coordinates.size() - 1].total_amount > 0)
    {
        Deck.draw(players[current_player_number], current_hand_number);
        //players[current_player_number].Flip_Card(current_hand_number);
        doubledDown = true;
        ui->Double_Down->hide();

        if (players[current_player_number].Get_Hand_Count() == 1)
        {
            players[current_player_number].Double_Down();
            Chips_coordinates = players[current_player_number].Get_Poker_coordinates();
            QRect temp = Chips_coordinates[Chips_coordinates.size() - 1].chip_coordinates;
            temp.setTop(temp.top() + 50);
            temp.setX(temp.x() + 30);
            temp.setWidth(70);
            temp.setHeight(20);
            Chip_Values[Chips_coordinates.size() - 1]->setGeometry(temp);
            Chip_Values[Chips_coordinates.size() - 1]->setText(QString("$ " + QString::number(Chips_coordinates[Chips_coordinates.size() - 1].total_amount)));
            Poker_Chips[Chips_coordinates.size() - 1]->setGeometry(Chips_coordinates[Chips_coordinates.size() - 1].chip_coordinates);
            Poker_Chips[Chips_coordinates.size() - 1]->show();
            Chip_Values[Chips_coordinates.size() - 1]->show();
            Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));
        }
        else
        {
            players[current_player_number].Change_Bet(current_hand_number + 1, Chips_coordinates[Chips_coordinates.size() - 1].total_amount * 2);
            Chips_coordinates = players[current_player_number].Get_Poker_coordinates();
            Chip_Values[current_hand_number + 1]->setText(QString("$ " + QString::number(Chips_coordinates[current_hand_number + 1].total_amount)));
            Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));
        }
        on_Stay_Button_clicked();
    }
    else
    {
        ui->textBrowser->setText(QString("You do not have enough money for Double Down"));
    }
}
const bool getSurrender();
void setUserSurrender(bool);

void MainWindow::on_Surrender_clicked()
{
    if (players.size() == 1)
    {
        cout << "YOU LOST HALF OF YOUR MONEY!!!!!!!!" << endl;
        Chip_Values[0]->setText(QString("Total_Chips: $") + QString::number(Chips_coordinates[0].total_amount + (Chips_coordinates[1].total_amount / 2)));
        gainslosses-=(Chips_coordinates[1].total_amount/2);
        QColor color2 = surrenderColor;
        ui->textBrowser->setTextColor(color2);
        ui->textBrowser->setText("You Lost the game with half your money back");
        //New_Game();
        setUserSurrender(true);
        on_Stay_Button_clicked();
    }
    else
    {
        ui->Surrender->hide();
        on_Stay_Button_clicked();
    }

}
void MainWindow::on_New_Game_clicked()
{
    ui->textBrowser->clear();
    //else {
        for (int i = 0; i < players[current_player_number].Get_Hand_Count();++i)
        {
            Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));
        }
        doubledDown = false;
        New_Game();
    //}
}

bool MainWindow::Change_user(string username)
{
    //To be implemented in 3rd iteration, excluded from class diagram
    return true;
}

void MainWindow::on_pushButton_clicked()
{
    //if the card count is visible, hide it. Otherwise, make it hidden
    if (ui->textBrowser_2->isVisible())
        ui->textBrowser_2->hide();
    else
        ui->textBrowser_2->show();
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < Images.size(); ++i)
    {
        delete Images.takeAt(0);
    }
    delete ui;
}

void MainWindow::on_actionBust_triggered()
{
    bustColor = QInputDialog::getText(this, "Bust Color","Enter color name or RGB code: ", QLineEdit::Normal, bustColor);
    if(bustColor.isEmpty())
       bustColor = "black";

}

void MainWindow::on_actionSurrender_triggered()
{
    surrenderColor = QInputDialog::getText(this, "Surrender Color","Enter color name or RGB code: ", QLineEdit::Normal, surrenderColor);
    if(surrenderColor.isEmpty())
       surrenderColor = "black";
}

void MainWindow::on_actionWin_triggered()
{
    winColor = QInputDialog::getText(this, "Win Color","Enter color name or RGB code: ", QLineEdit::Normal, winColor);
    if(winColor.isEmpty())
       winColor = "black";
}
