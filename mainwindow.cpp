#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRect>
#include <QString>
#include <QTextBrowser>
#include <QInputDialog>

QList<QLabel*> Images;
int free_index = 0;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	Chip_name = "Poker_Chip.png";

	//Change_user("BOB");

	for (int i = 0; i < 52; ++i) {
		Images.push_back(new QLabel(this));
	}

	for (int i = 0; i < 3; ++i) {
		Chip_Values.push_back(new QTextBrowser(this));
	}
	Chip_Values[2]->hide();


	Title_Message = "BlackJack Game: Version 1.0";
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
void MainWindow::Start_Game() {
	ui->New_Game->hide();
	ui->Split_Button->hide();
	ui->Double_Down->hide();
	ui->Surrender->show();

	for (int i = 0; i < 5; ++i) {
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


	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < (int)players.size(); ++j) {
			Deck.draw(players[j], 0); //Draws the first player and is their first hand
			if (j != 0)
				players[j].Hide_Hand();
		}
		Deck.draw(Dealer[0], 0);
		if (i == 1)
			Dealer[0].Flip_Card(0);

	}

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


	for (int k = 0; k <= (int)players.size(); ++k) {
		if (k == (int)players.size()) {
			cout << "The Dealers Cards are the Following:" << endl;
			Dealer[0].Display_Hands();
		}
		else {
			cout << "Player #" << k + 1 << " Cards are the Following:" << endl;
			players[k].Display_Hands();
		}

	}

	Players_Turn = "It is currently player #";
	Players_Turn += QString::number(current_player_number + 1);
	Players_Turn += "'s Turn\n";
	ui->textBrowser->setText(Players_Turn);


	for (int i = 0; i < Number_of_Players; ++i) {
		players[i].Set_Total_ChipsAmount(500.00);
		double bet_amount;
		do {
			bet_amount = QInputDialog::getInt(this, "Bet_Value", "Please enter the bet ammount you want to put in(Minimum $5.00)");
		} while (bet_amount < 5.00 || bet_amount > players[i].Get_Total_ChipsAmount());

		players[i].Add_Bet(bet_amount);

	}

	Chips_coordinates = players[current_player_number].Get_Poker_coordinates();
	for (int i = 0; i < 2; ++i) {
		Poker_Chips[i]->setGeometry(Chips_coordinates[i].chip_coordinates);
	}

	Poker_Chips[0]->show();
	Poker_Chips[1]->show();
	//Poker_Chips[0]->setGeometry(Chips_coordinates[0].chip_coordinates);
	//Poker_Chips[1]->setGeometry(Chips_coordinates[1].chip_coordinates);
	//ui->textBrowser_2->setText(QString("Total_Chips: " +  QString::number(players[current_player_number].Get_Total_ChipsAmount())));
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
	else {
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
	if (Dealers_Turn) {
		if (Dealer[0].Is_Busted(0)) {
			;//Dialog_Text = "Dealer Busted with a value of " + QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n";
		}
		else
			;//Dialog_Text = "Dealers current hand value is " + QString::number(Dealer[0].Get_Current_Hand_value(0)) + "\n";
	}

	else {
		if (players[current_player_number].Is_Busted(current_hand_number)) {
			//Dialog_Text = "You Busted with a value of " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n";
			ui->textBrowser->setText("You Busted with a value of " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n");
			on_Stay_Button_clicked();
			return;
		}
		else {
			Dialog_Text = "Your current hand value is " + QString::number(players[current_player_number].Get_Current_Hand_value(current_hand_number)) + "\n";
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
	}


	if (!players_out) {
		Dialog_Text = Players_Turn + Dialog_Text;
		ui->textBrowser->setText(Dialog_Text);
	}
}

void MainWindow::New_Game() {
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
	if (Dealers_Turn == true) {
		Dealers_Turn = false;
		current_player_number = 0;
		Players_Turn = "It is currently player #1's turn\n";
		players[players.size() - 1].Hide_Hand();
		players[0].Show_Hand();
	}

	else if (int(players.size()) == (current_player_number + 1) && (players[current_player_number].Get_Hand_Count() - 1 == current_hand_number)) {
		Dealers_Turn = true;
		Dealer[0].Flip_Card(0);
		Players_Turn = "It is currently the Dealers's turn\n";
		current_hand_number = 0;

		players_out = true;
		for (int i = 0; i < players[current_player_number].Get_Hand_Count();++i) {
			if (!(players[current_player_number].Is_Busted(i))) {
				players_out = false;
			}
		}

		if (players_out) {
			ui->textBrowser->setText(QString("The Dealer Won!"));
			ui->New_Game->show();
			return;
		}


		while (Dealer[0].Get_Current_Hand_value(0) < 17) {
			on_Hit_Button_clicked();
			Players_Turn += "The Dealer has a Total of ";
			Players_Turn += QString::number(Dealer[0].Get_Current_Hand_value(0));
		}

		if (Dealer[0].Get_Current_Hand_value(0) > 21) {
			Players_Turn += "\nThe Dealer has Busted!\n";
			ui->textBrowser->setText(QString(Players_Turn));
			for (int i = 0; i < players[current_player_number].Get_Hand_Count();++i) {
				if (!(players[current_player_number].Is_Busted(i))) {
					ui->textBrowser->setText(ui->textBrowser->toPlainText() + QString("Player 1 hand ") + QString::number(i + 1) + QString(": won \n"));
				}
			}

		}
		else {
			int Dealer_total = Dealer[0].Get_Current_Hand_value(0);
			bool Dealer_Beat_someone = false;
			ui->textBrowser->setText(QString(""));
			for (int i = 0; i < players[current_player_number].Get_Hand_Count(); ++i) {
				if (Dealer_total < players[current_player_number].Get_Current_Hand_value(i) && players[current_player_number].Get_Current_Hand_value(i) < 22) {
					ui->textBrowser->setText(ui->textBrowser->toPlainText() + QString("Player 1 hand ") + QString::number(i + 1) + QString(": won \n"));
				}
				else
					Dealer_Beat_someone = true;
			}
			if (Dealer_Beat_someone)
				ui->textBrowser->setText(ui->textBrowser->toPlainText() + QString("Dealer won"));

		}
		ui->New_Game->show();
	}
	else {
		if (current_hand_number == (int)players[current_player_number].Get_Hand_Count() - 1) {
			current_hand_number = 0;
			players[current_player_number].Hide_Hand();
			++current_player_number;

			players[current_player_number].Show_Hand();
			Players_Turn = "It is currently player #";
			Players_Turn += QString::number(current_player_number + 1);
			Players_Turn += "'s Turn\n";
		}
		else {
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
	if (players[current_player_number].Get_Total_ChipsAmount() - Chips_coordinates[Chips_coordinates.size() - 1].total_amount > 0) {
		players[current_player_number].Split();
		current_hand_number = 0;

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
	else {
		ui->textBrowser->setText(QString("You do not have enough money for a split"));
	}
}

void MainWindow::on_Double_Down_clicked()
{
	//Do the bet for doubling down
	if (players[current_player_number].Get_Total_ChipsAmount() - Chips_coordinates[Chips_coordinates.size() - 1].total_amount > 0) {
		Deck.draw(players[current_player_number], current_hand_number);
		//players[current_player_number].Flip_Card(current_hand_number);
		ui->Double_Down->hide();

		if (players[current_player_number].Get_Hand_Count() == 1) {
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
		else {
			players[current_player_number].Change_Bet(current_hand_number + 1, Chips_coordinates[Chips_coordinates.size() - 1].total_amount * 2);
			Chips_coordinates = players[current_player_number].Get_Poker_coordinates();
			Chip_Values[current_hand_number + 1]->setText(QString("$ " + QString::number(Chips_coordinates[current_hand_number + 1].total_amount)));
			Chip_Values[0]->setText(QString("Total_Chips: $" + QString::number(players[current_player_number].Get_Total_ChipsAmount())));
		}
		on_Stay_Button_clicked();
	}
	else {
		ui->textBrowser->setText(QString("You do not have enough money for Double Down"));
	}
}

void MainWindow::on_Surrender_clicked()
{
	if (players.size() == 1) {
		cout << "YOU LOST HALF OF YOUR MONEY!!!!!!!!" << endl;
		Chip_Values[0]->setText(QString("Total_Chips: $") + QString::number(Chips_coordinates[0].total_amount + (Chips_coordinates[1].total_amount / 2)));
		ui->textBrowser->setText("You Lost the game with half your money back");
		New_Game();
	}
	else {
		ui->Surrender->hide();
		on_Stay_Button_clicked();

	}

}
void MainWindow::on_New_Game_clicked()
{
	New_Game();
}

bool MainWindow::Change_user(string username) {
}

MainWindow::~MainWindow()
{
	for (int i = 0; i < Images.size(); ++i) {
		delete Images.takeAt(0);
	}
	delete ui;
}






