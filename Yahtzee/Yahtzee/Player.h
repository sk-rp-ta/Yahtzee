#pragma once
#include <string>
#include <cstdlib>     
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>

using namespace std;
class Player
{
public:
	Player();
	~Player();
	void roll();
	void roll(int x);
	int reroll();
	int acc_RollADice(int x);
	int acc_NumberOfPoints();
	int acc_TurnPoints();
	void set_RollADice(int x);
	void set_TurnPoints(int x);
	void set_NumberOfPoints(int x);
	void set_Name(string _name);
	string acc_Name();
	
private:
	int TurnPoints;
	int NumberOfPoints;
	int RollADice[5];
	string Name;
};

