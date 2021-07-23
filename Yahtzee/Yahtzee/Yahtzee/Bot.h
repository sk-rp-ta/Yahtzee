#pragma once
#include "Player.h"
class Bot :
	public Player
{
public:
	
	bool do_roll(vector<Player> &players, vector<Bot> &bots, int number_of_players);
	void set_Aggression(int x);
	int get_Aggression();
	int place(vector<Player> &players, vector<Bot> &bots, int number_of_players);
	void b_roll();

private:
	int Aggression=0;
};

