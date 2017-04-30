#ifndef RULES_H
#define RULES_H

using std::string;
#include <string>
#include <fstream>
#include <iostream>
class Rules
{
public:
unsigned short[3] winColor;
unsigned short[3] loseColor;
string casinoRules; //The collection of casino rules used
bool showCount; //If 1, shows the card count
bool showRemaining; //If 1, shows the cards remaining in the deck
bool showPrecise; //If 1, shows the counts for the individual cards. If 0, shows high/low count.
double defaultBet; //The default bet the player makes
double minBet; //The minimum amount of the money the player can bet
double startMoney; 
Rules()
 {
	 winColor = [0, 255, 0];
	 loseColor = [255, 0, 0];
	 casinoRules = "default";
	 showCount = true;
	 showRemaining = true;
	 showPrecise = true;
	 defaultBet = 5.00;
	 minBet = 5.00;
	 startMoney = 500.00;
 }
 
void importRules() //Assumes file is formatted correctly
 {
	string currentLine = "*";
	fstream file;
	file.open("options.txt", ios::in);
	if (file.is_open() == False)
	{
		return;
	}
	int i = 0;
	for (int filled = 0; filled < 3; filled ++)
	{
		while (currentLine[i] < '0' or currentLine[i] > '9')
		{
			i ++;
		}
		unsigned short value = 0;
		while (currentLine[i] >= '0' and currentLine[i] <= '9')
		{
			value = value * 10;
			value = value + ((int)currentLine[i] - 48);
			i ++;
		}
		winColor[filled] = value;
	}
	getline(myfile,currentLine);
	i = 0;
	for (int filled = 0; filled < 3; filled ++)
	{
		while (currentLine[i] < '0' or currentLine[i] > '9')
		{
			i ++;
		}
		unsigned short value = 0;
		while (currentLine[i] >= '0' and currentLine[i] <= '9')
		{
			value = value * 10;
			value = value + ((int)currentLine[i] - 48);
			i ++;
		}
		loseColor[filled] = value;
	}
	getline(myfile,currentLine);
	casinoRules = currentLine;
	getline(myfile,currentLine);
	showCount = (currentLine.compare("1") or currentLine.compare("True"));
	getline(myfile,currentLine);
	showRemaining = (currentLine.compare("1") or currentLine.compare("true"));
	getline(myfile,currentLine);
	showPrecise = (currentLine.compare("1") or currentLine.compare("true"));
	getline(myfile,currentLine);
	defaultBet = readDouble(currentLine);
	getline(myfile,currentLine);
	minBet = readDouble(currentLine);
	getline(myfile,currentLine);
	startMoney = readDouble(currentLine);
	file.close();
 }
 
double readDouble(string line)
{
	int i = 0;
	while (line[i] < '0' or line[i] > '9')
		{
			i ++;
		}
		double decimal = 0;
		int point = 0;
		while ((currentLine[i] >= '0' and currentLine[i] <= '9')
		{
			decimal = decimal * 10;
			decimal = decimal + ((int)currentLine[i] - 48);
			i ++;
		}
		if (currentLine[i] == '.')
		{
			while ((currentLine[i] >= '0' and currentLine[i] <= '9')
			{
				decimal = decimal * 10;
				decimal = decimal + ((int)currentLine[i] - 48);
				point ++;
				i ++;
			}
			for (i = 0; i < point; i ++)
			{
				decimal = decimal / 10.0;
			}
		}
	return decimal;	
}

void writeRules()
{
	fstream file;
	file.open("options.txt", ios::out);
	file << winColor[0] << ' ' << winColor[1] << ' ' << winColor[2] << '\n';
	file << loseColor[0] << ' ' << loseColor[1] << ' ' << loseColor[2] << '\n';
	file << casinoRules << '\n';
	file << showCount << '\n';
	file << showRemaining << '\n';
	file << showPrecise << '\n';
	file << defaultBet << '\n';
	file << minBet << '\n';
	file << startMoney << '\n';
	file.close();
}

void printAll() //used for debug
{
	cout << winColor[0] << ' ' << winColor[1] << ' ' << winColor[2] << '\n';
	cout << loseColor[0] << ' ' << loseColor[1] << ' ' << loseColor[2] << '\n';
	cout << casinoRules << '\n';
	cout << showCount << '\n';
	cout << showRemaining << '\n';
	cout << showPrecise << '\n';
	cout << defaultBet << '\n';
	cout << minBet << '\n';
	cout << startMoney << '\n';
}

 ~Rules() {}
};
#endif // RULES_H
