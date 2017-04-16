#ifndef CARD_H
#define CARD_H

using std::string;
#include <QString>

class Card
{
private:
    string name;
    int value;
    int minValue;
    int cardId[2];
    bool minValueUsed;
    bool faceDown;

public:
    Card()
    {
        name = "NULL";
        value = minValue = 0;
        minValueUsed = false;
    }
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
        cardId[0] = suit;
        string suitNames[4] = { "Hearts", "Spades", "Diamonds", "Clubs" };
        int temp_value = index % 13;
        cardId[1] = temp_value;
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
        faceDown = false;
        this->name = valueNames[temp_value] + suitNames[suit];
        this->minValueUsed = false;
    }

    string getName()
    {
        return this->name;
    }
    QString getFileName()
    {
        QString CardFile = QString::fromStdString(name + ".png");
        return CardFile;
    }

    int getMinValue()
    {
        return this->minValue;
    }

    int getValue()
    {
        if (minValueUsed)
        {
            return this->minValue;
        }
        return this->value;
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

    void setFaceDown(bool input)
    {
        faceDown = input;
    }

    bool isFaceDown()
    {
        return faceDown;
    }

    int getId()
    {
        return cardId[1];
    }

    ~Card() {}
};
#endif // CARD_H
