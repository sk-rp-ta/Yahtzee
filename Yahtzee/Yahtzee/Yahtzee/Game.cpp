#include "Game.h"

Game::Game()
{
	//tile

	title();

	//inserting number of players
	do
	{
		cout << "Insert number of players (including bots) (1-10): " << endl;
		cin >> NumberOfPlayers;

		//wrong input security
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (NumberOfPlayers < 1 || NumberOfPlayers > 10);

	//inserting number of bots
	do
	{
		cout << "Insert number of bots: " << endl;
		cin >> NumberOfBots;

		//wrong input security
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (NumberOfBots > NumberOfPlayers || NumberOfBots < 0);

	//memory allocation for players and bots

	players.resize(NumberOfPlayers - NumberOfBots);
	bots.resize(NumberOfBots);

	system("cls");

	//setting names 
	for (auto &player : players)
	{
		static int counter = 1;
		cout << "Insert name of player " << counter << ":" << endl;
		string temp;
		cin >> temp;
		if (temp.size() > 0) player.set_Name(temp);
		else
		{
			stringstream sstm;
			sstm << "Player " << counter;
			player.set_Name(sstm.str());
		}
		system("cls");
		counter++;
	}
	//setting names of bots
	for (auto &bot : bots)
	{
		static int counter = 1;
		stringstream sstm;
		sstm << "Bot " << counter;
		bot.set_Name(sstm.str());
		bot.set_Aggression(rand() % 3 + 1); //1-careful 2-normal 3-agressive
		counter++;
	}
	WhichTurn = 1;
}

int Game::get_WhichTurn()
{
	return WhichTurn;
}

bool Game::game_over()
{
	if (WhichTurn > 13) return false;
	return true;
}

void Game::show(Player *p)
{
	cout << "Turn:" << WhichTurn << endl << endl;
	cout << p->get_Name().c_str() << endl;
	cout << "Actual number of points: " << p->get_NumberOfPoints() << endl << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << p->get_RollADice(i) << " ";
	}
	cout << endl << endl;
	//number of each dice
	check_pattern(p);
	system("PAUSE");
}

int Game::get_NumberOfPlayers()
{
	return NumberOfPlayers;
}

void Game::check_pattern(Player *p)
{
	//Yahtzee - All five dice the same - 50 points
	//Large Straight - Five sequential dice (1 - 2 - 3 - 4 - 5 or 2 - 3 - 4 - 5 - 6) - 40 points
	//Small Straight - Four sequential dice(1 - 2 - 3 - 4, 2 - 3 - 4 - 5, or 3 - 4 - 5 - 6) - 30 points
	//Full House - Three of one number and two of another - 25 points
	//Four of a kind - At least four dice the same - Sum of all dice
	//Three of a kind - At least three dice the same - Sum of all dice
	//Chance - Any combination - Sum of all dice
	bool yahtzee = false;
	bool l_straight = false;
	bool s_straight = false;
	bool f_house = false;
	bool four_ok = false;
	bool three_ok = false;
	bool pair = false;

	//for straights
	int temp_fs[6] = { 0 };

	map<int, int> NumberOfValues;
	int sum = 0;
	//defining number of each dice value as 0
	for (int i = 1; i <= 6; i++)
	{
		NumberOfValues[i] = 0;
	}

	//counting number of each dice value and sum
	for (int i = 0; i <5; i++)
	{
		NumberOfValues[p->get_RollADice(i)] += 1;
		sum += (p->get_RollADice(i));
	}

	//showing number of each dice value, checing four conditions and making temp arrays for another two
	for (int i = 1; i <= 6; i++)
	{
		temp_fs[i - 1] = NumberOfValues[i];
		if (NumberOfValues[i] > 1) temp_fs[i - 1] = 1;
		else temp_fs[i - 1] = NumberOfValues[i];

		if (NumberOfValues[i] == 5) yahtzee = true;
		if (NumberOfValues[i] == 4) four_ok = true;
		if (NumberOfValues[i] == 3) three_ok = true;
		if (NumberOfValues[i] == 2) pair = true;
	}

	bool l_straight1 = (temp_fs[0] == 1 && temp_fs[1] == 1 && temp_fs[2] == 1 && temp_fs[3] == 1 && temp_fs[4] == 1); // 1 2 3 4 5
	bool l_straight2 = (temp_fs[1] == 1 && temp_fs[2] == 1 && temp_fs[3] == 1 && temp_fs[4] == 1 && temp_fs[5] == 1); // 2 3 4 5 6

	if (l_straight1 || l_straight2 ) l_straight = true;

	bool s_straight1 = (temp_fs[0] == 1 && temp_fs[1] == 1 && temp_fs[2] == 1 && temp_fs[3] == 1); // 1 2 3 4
	bool s_straight2 = (temp_fs[1] == 1 && temp_fs[2] == 1 && temp_fs[3] == 1 && temp_fs[4] == 1); // 2 3 4 5
	bool s_straight_3 = (temp_fs[2] == 1 && temp_fs[3] == 1 && temp_fs[4] == 1 && temp_fs[5] == 1); // 3 4 5 6

	if ( s_straight1 || s_straight2  || s_straight_3 ) s_straight = true;

	if (three_ok && pair) f_house = true;

	if (yahtzee)
	{
		cout << "Yahtzee!" << endl;
		cout << "Number of points:" << 50 << endl;
		p->set_TurnPoints(50);
	}
	else if (l_straight)
	{
		cout << "Large Straight!" << endl;
		cout << "Number of points:" << 40 << endl;
		p->set_TurnPoints(40);
	}
	else if (s_straight)
	{
		cout << "Small Straight!" << endl;
		cout << "Number of points:" << 30 << endl;
		p->set_TurnPoints(30);
	}
	else if (f_house)
	{
		cout << "Full House!" << endl;
		cout << "Number of points:" << 25 << endl;
		p->set_TurnPoints(25);
	}
	else if (four_ok)
	{
		cout << "Four of a kind!" << endl;
		cout << "Number of points:" << sum << endl;
		p->set_TurnPoints(sum);
	}
	else if (three_ok)
	{
		cout << "Three of a kind!" << endl;
		cout << "Number of points:" << sum << endl;
		p->set_TurnPoints(sum);
	}
	else
	{
		cout << "Chance!" << endl;
		cout << "Number of points:" << sum << endl;
		p->set_TurnPoints(sum);
	}
	cout << endl;
}


void Game::turn()
{
	system("cls");

	for (auto &i : players)
	{
		i.roll();
		show(&i);

		if (i.reroll())
		{
			system("cls");
			show(&i);

			if (i.reroll())
			{
				system("cls");
				show(&i);
			}
		}
		i.set_NumberOfPoints(i.get_TurnPoints());
		system("cls");
	}
	for (auto &bot : bots)
	{
		bot.roll();
		show(&bot);

		if (bot.do_roll(players,bots,NumberOfPlayers))
		{
			bot.b_roll();
			system("cls");
			show(&bot);
			if (bot.do_roll(players, bots, NumberOfPlayers))
			{
				bot.b_roll();
				system("cls");
				show(&bot);
			}
		}
		bot.set_NumberOfPoints(bot.get_TurnPoints());
		system("cls");
	}
	WhichTurn++;
}
void Game::title()
{

std::cout << R"(
	____    ____  ___       __    __  .___________. ________   _______  _______ 
	\   \  /   / /   \     |  |  |  | |           ||       /  |   ____||   ____|
	 \   \/   / /  ^  \    |  |__|  | `---|  |----``---/  /   |  |__   |  |__   
	  \_    _/ /  /_\  \   |   __   |     |  |        /  /    |   __|  |   __|  
	    |  |  /  _____  \  |  |  |  |     |  |       /  /----.|  |____ |  |____ 
	    |__| /__/     \__\ |__|  |__|     |__|      /________||_______||_______|
  










					   by sk_rp_ta      


                                                                                                                                                    
 
)" << endl;

system("pause");
system("cls");

}

void Game::finish()
{
	int num=0;
	string winner;
	for (auto player : players)
	{
		if (player.get_NumberOfPoints() > num)
		{
			num = player.get_NumberOfPoints();
			winner = player.get_Name();
		}
	}
	for (auto bot : bots)
	{
		if (bot.get_NumberOfPoints() > num)
		{
			num = bot.get_NumberOfPoints();
			winner = bot.get_Name();
		}
	}
	cout << "Winner is " << winner << " with " << num << " points!" << endl;
}