#pragma once
#include "Bot.h"


class Game
{
public:
	Game();
	~Game();
	void show(Player *p);
	int acc_NumberOfPlayers();
	int acc_WhichTurn();
	void WhichTurn_pp();
	bool game_over();
	void turn();
	void check_pattern(Player *p);
	void title();
	void finish();
private:
	int WhichTurn;
	int NumberOfPlayers;
	int NumberOfBots;
	vector<Player> players;
	vector<Bot> bots;
};

