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
        this->minValueUsed=false;
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
private:
    string name;
    int value;
    int minValue;
    bool minValueUsed = false;
};





#endif // CARD_H
