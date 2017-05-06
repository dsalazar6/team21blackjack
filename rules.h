#ifndef RULES_H
#define RULES_H

#include <string>
#include <fstream>
#include <iostream>
//#include <QString>
using namespace std;

class Rules
{
private:
QString winColor;
QString loseColor;
int doubleDownMin;
int doubleDownMax;
int dealerStay;
bool countPrecision; 	//If 0, shows high/low count; if 1. shows precise count
bool countType;     // If 0, shows cards played; if 1 shows cards remaining
bool splitOnFace;	//If 1, allows player to split on cards of the same value
bool allowSurrender;
double surrenderPay;
double winPay;
double defaultBet; //The default bet the player makes
double minBet; //The minimum amount of the money the player can bet
double startMoney;

public:
Rules()
 {
	winColor = QString("#00ff00");
    loseColor = QString("#ff0000");
	doubleDownMin = 9;
	doubleDownMax = 11;
	dealerStay = 17;
    countPrecision = false;
	countType = false;
	splitOnFace = false;
	allowSurrender = true;
	surrenderPay = 0.5;
	winPay = 1.0;
	defaultBet = 5.00;
	minBet = 5.00;
	startMoney = 500.00;
 }

void importRules() //Assumes file is formatted correctly
 {
    string currentLine;
    fstream file;
    file.open("options.txt", ios::in);
    if (file.is_open() == false)
    {
       cout << "file not found" << endl;
        writeRules();
	   return;
    }
    getline(file, currentLine);
    winColor = QString::fromStdString(currentLine);
    getline(file, currentLine);
    loseColor = QString::fromStdString(currentLine);
	file >> doubleDownMin;
	file >> doubleDownMax;
	file >> dealerStay;
    file >> countPrecision;
	file >> countType;
	file >> splitOnFace;
	file >> allowSurrender;
	file >> surrenderPay;
	file >> winPay;
	file >> defaultBet;
	file >> minBet;
	file >> startMoney;
	file.close();
 }

QString getWinColor(){ return winColor; }

QString getLoseColor(){ return loseColor; }

int getDDMin(){ return doubleDownMin; }

int getDDMax(){ return doubleDownMax; }

int getStay(){ return dealerStay; }

bool getCountPrecision(){ return countPrecision; }

bool getCountType(){ return countType; }

bool getSplitFace(){ return splitOnFace; }

bool getAllowSurrender(){ return allowSurrender; }

double getSurrenderPay(){ return surrenderPay; }

double getWinPay(){ return winPay; }

double getDefaultBet(){ return defaultBet; }

double getMinBet(){ return minBet; }

double getStartMoney(){ return startMoney; }

void writeRules()
{
    fstream file;
    file.open("options.txt", ios::out);
    file << winColor.toStdString() << endl;
    file << loseColor.toStdString() << endl;
	file << doubleDownMin << endl;
	file << doubleDownMax << endl;
	file << dealerStay << endl;
    file << countPrecision << endl;
	file << countType << endl;
	file << splitOnFace << endl;
	file << allowSurrender << endl;
	file << surrenderPay << endl;
	file << winPay << endl;
	file << defaultBet << endl;
	file << minBet << endl;
	file << startMoney << endl;
	file.close();
    //printAll();
}

void updateWinColor(string newWin)
{
    winColor = QString::fromStdString(newWin);
}

void updateLoseColor(string newLose)
{
    loseColor = QString::fromStdString(newLose);
}

void updateDoubleDown(int min, int max) {
    doubleDownMin = min;
    doubleDownMax = max;
}

void updateDealerStay(int stay) {
    dealerStay = stay;
}

void updateSplit(bool face) {
    splitOnFace = face;
}

void updateSurrender(bool surr) {
    allowSurrender = surr;
}

void updateSurrenderPay(double sPay) {
    surrenderPay = sPay;
}

void updateWinPay (double wPay) {
    winPay = wPay;
}

void updateCardCount(bool count)
{
	countType = count;
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

void reset() {
    winColor = QString("#00ff00");
    loseColor = QString("#ff0000");
    doubleDownMin = 9;
    doubleDownMax = 11;
    dealerStay = 17;
    countPrecision = false;
    countType = false;
    splitOnFace = false;
    allowSurrender = true;
    surrenderPay = 0.5;
    winPay = 1.0;
    defaultBet = 5.00;
    minBet = 5.00;
    startMoney = 500.00;
}

void printAll() //used for debug
{
	cout << winColor.toStdString() << endl;
    cout << loseColor.toStdString() << endl;
	cout << doubleDownMin << endl;
	cout << doubleDownMax << endl;
	cout << dealerStay << endl;
    cout << countPrecision << endl;
	cout << countType << endl;
	cout << splitOnFace << endl;
	cout << allowSurrender << endl;
	cout << surrenderPay << endl;
	cout << winPay << endl;
	cout << defaultBet << endl;
	cout << minBet << endl;
	cout << startMoney << endl;
}

 ~Rules() {}
};
#endif // RULES_H
