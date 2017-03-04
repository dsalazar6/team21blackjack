#include <string> 
#include <vector>
#include <list>

#include "deck.h"
#include "card.h"
#include <vector>

#include <time.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL));

	vector<Card> Deck;
	vector<Card> Hand;
	vector<Card> DealerHand;
	vector<Card> Graveyard;

	deck d;

	bool end = false; //will end the game when true



	cout << "Welcome to Blackjack\n";
	while(true){
		int option;
		while (!end) {
			//phase 1 start game
			cout << "1) New game\n";
			cout << "2) Exit\n";
			cin >> option;
			if (option == 1)
			{
				d.addStandardDeck(Deck);
				//			cout << "cards successfully added in the following order with a length of " << Deck.size() <<"\n";

				//			for (int i = 1; i < Deck.size(); i++)
				//				cout << Deck[i].getName() << endl;

				d.Shuffle(Deck); //The deck is being shuffled
								 //			cout << "cards successfully shuffled in the following order with a length of " << Deck.size() << "\n";

								 //			for (int i = 1; i < Deck.size(); i++)
								 //				cout << Deck[i].getName() << endl;


								 //Phase 2 Draw card for player and Dealer

				bool hold = false;
				bool bust = false;
				bool dealerBust = false;

				int value = 0;
				int dealerValue = 0;
				int hitHold = -1; //determines whether you want to hit, hold or exit

				while (hitHold != 3)
				{
					cout << "The dealer is giving you cards.\n";
					d.draw(Deck, Hand, Graveyard, value, bust);
					d.draw(Deck, Hand, Graveyard, value, bust);
					cout << "The dealer is giving himself cards.\n";

					d.draw(Deck, DealerHand, Graveyard, dealerValue, dealerBust);
					d.draw(Deck, DealerHand, Graveyard, dealerValue, dealerBust);

					//Phase 3 Player may draw or hit
					while (!bust && !hold && value != 21) //while the player isn't choosing to stand and hasn't busted and hasn't already drawn 21
					{

						cout << "\n\nYou currently have the following cards:\n";
						for (int i = 0; i < Hand.size(); i++)
							cout << " " << Hand[i].getName() << endl;
						cout << "the current value of your hand is " << value << endl;
						cout << "The Dealer currently has a\n " << DealerHand[0].getName() << "\n a face down card";
						cout << "\nSelect an option :\n1)Hit\n2)Hold\n3)End Game\n";
						cin >> hitHold;

						if (hitHold == 1)
						{
							d.draw(Deck, Hand, Graveyard, value, bust);
							cout << "You have drawn a " << Hand[Hand.size() - 1].getName() << endl;
						}
						else if (hitHold == 2)
							hold = true;
						else if (hitHold == 3) {
							cout << "Would you like to restart the game or quit?"
								<< "\n1) Quit"
								<< "\n2) Restart\n";
							int junk;
							cin >> junk;
							if (junk == 1)
								return 0;
							option = -1;
						}
					}

					//Phase 4 Dealer will Draw or hit if the player didn't bust and the player hasn't quit the game
					if (!bust && value != 21 && hitHold != 3)
					{
						cout << "The dealer has revealed his face down card is the " << DealerHand[1].getName() << endl;
						if (dealerValue == 21)
						{
							cout << "the dealer hit blackjack.\n";
						}
						else if (dealerValue >= 17)
						{
							cout << "The dealer holds on the value " << dealerValue << endl;
						}
						else {
							cout << "The dealer will begin drawing.\n";
							int i = 2;
							while (dealerValue < 17)
							{
								d.draw(Deck, DealerHand, Graveyard, dealerValue, dealerBust);
								cout << "The dealer has drawn a " << DealerHand[i].getName() << endl;
								i++;
							}
						}
					}
					if (value == 21) {
						cout << "You have hit blackjack.\n";
					}
					if (bust)
						cout << "You have busted and lost this hand.\n";
					else if (dealerBust)
						cout << "The dealer has busted and lost this hand.\n";
					else {
						if (dealerValue > value)
							cout << "The dealer has won this hand.\n";
						else if (value > dealerValue)
							cout << "You have won this hand.\n";
						else if (value == dealerValue)
							cout << "In a draw the dealer has won the hand.";
					}
					cout << endl;
					//Places hands into graveyard

					//make all cards alterable
					for (int i = 0; i < Hand.size(); i++)
						Hand[i].resetValue();
					for (int i = 0; i < DealerHand.size(); i++)
						DealerHand[i].resetValue();
					Graveyard.reserve(Hand.size() + DealerHand.size());
					Graveyard.insert(Graveyard.end(), Hand.begin(), Hand.end());
					Graveyard.insert(Graveyard.end(), DealerHand.begin(), DealerHand.end());
					while (!Hand.empty())
						Hand.erase(Hand.begin());
					while (!DealerHand.empty())
						DealerHand.erase(DealerHand.begin());

					value = 0;
					dealerValue = 0;
					bust = false;
					hold = false;
					dealerBust = false;
					hitHold = -1;
				}

			}
			else if (option == 2)
			{
				end = true;
			}
			
		}
		return 0;
	}

}

