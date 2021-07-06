#pragma once
#include "Player.h"
class Bot :
	public Player
{
public:
	
	bool do_roll(vector<Player> players, vector<Bot> bots, int number_of_players);
	void set_Agression(int x);
	int acc_Agression();
	int place(vector<Player> players, vector<Bot> bots, int number_of_players);
	void b_roll();

private:
	int Agression;
};

