#ifndef RULES_H
#define RULES_H

using std::string;
#include <string>
#include <fstream>
#include <iostream>
#include <QColor>
class Rules
{
private:
int winColor[3];
QColor winQColor;
int loseColor[3];
QColor loseQColor;
int doubleDownMin;
int doubleDownMax;
int dealerStay;
bool showCount; //If 1, shows the card count
bool showRemaining; //If 1, shows the cards remaining in the deck
bool showPrecise; //If 1, shows the counts for the individual cards. If 0, shows high/low count.
bool splitOnFace;
bool allowSurrender;
double surrenderPay;
double winPay;
double defaultBet; //The default bet the player makes
double minBet; //The minimum amount of the money the player can bet
double startMoney;

public:
Rules()
 {
	winColor[0] = 0;
	winColor[1] = 255;
	winColor[2] = 0;
	winQColor = QColor(0,255,0);
	loseColor[0] = 255;
	loseColor[1] = 0;
	loseColor[2] = 0;
	loseQColor = QColor(255,0,0);
	doubledownMin = 9;
	doubledownMax = 11;
	dealerStay = 17;
	showCount = true;
	showRemaining = true;
	showPrecise = true;
	splitOnFace = false;
	allowSurrender = true;
	surrenderPay = 0.5;
	winPay = 1.0;
	defaultBet = 5.00;
	minBet = 5.00;
	startMoney = 500.00;
	importRules();
 }

void importRules() //Assumes file is formatted correctly
 {
    string currentLine = "*";
    fstream file;
    file.open("options.txt", ios::in);
    if (file.is_open() == false)
    {
	   writeRules();
	   return;
    }
    int i = 0;
    for (int filled = 0; filled < 3; filled ++)
    {
	   winColor[filled] = readInt(currentLine) % 256;
    }
	winQColor = QColor(winColor[0], winColor[1], winColor[2]);
    getline(file,currentLine);
    i = 0;
    for (int filled = 0; filled < 3; filled ++)
    {
	   loseColor[filled] = readInt(currentLine) % 256;
    }
	loseQColor = QColor(loseColor[0], loseColor[1], loseColor[2]);
    getline(file,currentLine);
    doubleDownMin = readInt(currentLine);
	doubleDownMax = readInt(currentLine);
    getline(file,currentLine);
	dealerStay = readInt(currentLine);
	getline(file, currentLine);
    showCount = (currentLine.compare("1") || currentLine.compare("true"));
    getline(file,currentLine);
    showRemaining = (currentLine.compare("1") || currentLine.compare("true"));
    getline(file,currentLine);
    showPrecise = (currentLine.compare("1") || currentLine.compare("true"));
    getline(file,currentLine);
	splitOnFace = (currentLine.compare("1") || currentLine.compare("true"));
	getline(file, currentLine);
	allowSurrender = (currentLine.compare("1") || currentLine.compare("true"));
	getline(file, currentLine);
	surrenderPay = readDouble(currentLine);
	getline(file, currentLine);
	winPay = readDouble(currentLine);
	getline(file, currentLine);
    defaultBet = readDouble(currentLine);
    getline(file,currentLine);
    minBet = readDouble(currentLine);
    getline(file,currentLine);
    startMoney = readDouble(currentLine);
    file.close();
 }

int readInt(string &line)
{
	int i = 0;
	while (currentLine[i] < '0' or currentLine[i] > '9')
	{
		i ++;
	}
	int value = 0;
	while (currentLine[i] >= '0' and currentLine[i] <= '9')
	{
		value = value * 10;
		value = value + ((int)currentLine[i] - 48);
		i ++;
	}
	line = line.substr(i);
	return value;
}

double readDouble(string &line)
{
    int i = 0;
    while (line[i] < '0' or line[i] > '9')
	   {
		  i ++;
	   }
	   double decimal = 0;
	   int point = 0;
	   while ((line[i] >= '0' and line[i] <= '9'))
	   {
		  decimal = decimal * 10;
		  decimal = decimal + ((int)line[i] - 48);
		  i ++;
	   }
	   if (line[i] == '.')
	   {
		  while ((line[i] >= '0' and line[i] <= '9'))
		  {
			 decimal = decimal * 10;
			 decimal = decimal + ((int)line[i] - 48);
			 point ++;
			 i ++;
		  }
		  for (i = 0; i < point; i ++)
		  {
			 decimal = decimal / 10.0;
		  }
	   }
	line = line.substr(i);
    return decimal;
}

void writeRules()
{
    fstream file;
    file.open("options.txt", ios::out);
    file << winColor[0] << ' ' << winColor[1] << ' ' << winColor[2] << '\n';
    file << loseColor[0] << ' ' << loseColor[1] << ' ' << loseColor[2] << '\n';
	file << doubleDownMin << ' ' << doubleDownMax << '\n';
	file << dealerStay << '\n';
    file << showCount << '\n';
    file << showRemaining << '\n';
    file << showPrecise << '\n';
	file << splitOnFace << '\n';
	file << allowSurrender << '\n';
	file << surrenderPay << '\n';
	file << winPay << '\n';
    file << defaultBet << '\n';
    file << minBet << '\n';
    file << startMoney << '\n';
    file.close();
    printAll();
}

void updateWinColor(int r, ing g, int b)
{
	winColor[0] = r % 256;
	winColor[1] = g % 256;
	winColor[2] = b % 256;
	winQColor = QColor(winColor[0], winColor[1], winColor[2]);
}

void updateLoseColor(int r, ing g, int b)
{
	loseColor[0] = r % 256;
	loseColor[1] = g % 256;
	loseColor[2] = b % 256;
	loseQColor = QColor(loseColor[0], loseColor[1], loseColor[2]);
}

void updateCasinoRules(int min, int max, int stay, bool onFace, bool surrender, double sPay, double wPay)
{
	doubleDownMin = min;
	doubleDownMax = max;
	dealerStay = stay;
	spliOnFace = onFace;
	allowSurrender = surrender;
	surrenderPay = sPay;
	winPay = wPay;
}

void updateCardCount(bool show, bool rem, bool pres)
{
	showCount = show;
	showRmaining = rem;
	showPrecise = pres;
}

void updateDefaultBet(double bet)
{
	defaultBet = bet;
}

void updateMoney(double mBet, double base)
{
	minBet = mBet;
	startMoney = base;
}

void printAll() //used for debug
{
	cout << winColor[0] << ' ' << winColor[1] << ' ' << winColor[2] << '\n';
	cout << loseColor[0] << ' ' << loseColor[1] << ' ' << loseColor[2] << '\n';
	cout << doubleDownMin << ' ' << doubleDownMax << '\n';
	cout << dealerStay << '\n';
	cout << showCount << '\n';
	cout << showRemaining << '\n';
	cout << showPrecise << '\n';
	cout << splitOnFace << '\n';
	cout << allowSurrender << '\n';
	cout << surrenderPay << '\n';
	cout << winPay << '\n';
	cout << defaultBet << '\n';
	cout << minBet << '\n';
	cout << startMoney << '\n';
}

 ~Rules() {}
};
#endif // RULES_H