#pragma once
#include "Bot.h"


class Game
{
public:
	Game();
	void show(Player *p);
	int get_NumberOfPlayers();
	int get_WhichTurn();
	bool game_over();
	void turn();
	void check_pattern(Player *p);
	void finish();
	void title();
private:
	int WhichTurn;
	int NumberOfPlayers;
	int NumberOfBots;
	vector<Player> players;
	vector<Bot> bots;
};

