#ifndef CARD_H
#define CARD_H

using std::string;
class Card
{
public:
	Card() {}
	Card(string name, int minValue, int value)
	{
		this->name = name;
		this->minValue = minValue;
		this->value = value;
		this->minValueUsed = false;
	}

	Card(int index)
	{
		index = index % 52;
		int suit = index / 13;
		string suitNames[4] = { "Hearts", "Spades", "Diamonds", "Clubs" };
		int temp_value = index % 13;
		string valueNames[13] = { "Ace of ", "Two of ", "Three of ", "Four of ", "Five of ", "Six of ", "Seven of ", "Eight of ", "Nine of ", "Ten of ", "Jack of ", "Queen of ", "King of " };
		if (temp_value == 0)
		{
			this -> minValue = 1;
			this -> value = 11;
		}
		else
		{
			if (temp_value <= 9)
			{
				this->minValue = 1 + temp_value;
				this->value = 1 + temp_value;
			}
			else
			{
				this->minValue = 10;
				this->value = 10;
			}
		}
		this->name = valueNames[temp_value] + suitNames[suit];
		this->minValueUsed = false;
	}
	~Card() {}
	string getName() {
		return this->name;
	}
	int getMinValue()
	{
		return this->minValue;
	}
	int getValue() {
		if (minValueUsed)
		{
			return this->value;
		}
		return this->minValue;
	}
	bool getMinValueUsed()
	{
		return this->minValueUsed;
	}
	void resetValue()
	{
		minValueUsed = false;
	}
	void useMinValue()
	{
		minValueUsed = true;
	}
private:
	string name;
	int value;
	int minValue;
	bool minValueUsed = false;
};





#endif // CARD_H

