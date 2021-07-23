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
	void roll();
	void roll(int x);
	int reroll();
	int get_RollADice(int x);
	int get_NumberOfPoints();
	int get_TurnPoints();
	void set_RollADice(int x);
	void set_TurnPoints(int x);
	void set_NumberOfPoints(int x);
	void set_Name(string _name);
	string get_Name();
	
private:
	int TurnPoints = 0;
	int NumberOfPoints = 0;
	int RollADice[5]{};
	string Name;
};

