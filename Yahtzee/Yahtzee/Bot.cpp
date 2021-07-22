#include "Bot.h"

void Bot::set_Agression(int x)
{
	Agression = x;
}

int Bot::acc_Agression()
{
	return Agression;
}

int Bot::place(vector<Player> &players, vector<Bot> &bots, int number_of_players)
{
	int _place = number_of_players;
	for (auto i : players)
	{
		if (this->acc_NumberOfPoints() > i.acc_NumberOfPoints()) _place++;
	}
	for (auto i : bots)
	{
		if (this->acc_NumberOfPoints() > i.acc_NumberOfPoints()) _place++;
	}
	return _place;
}
bool Bot::do_roll(vector<Player> &players, vector<Bot> &bots, int number_of_players)
{
	//this function decides if bot is rolling dices again
	double risk = 0;  //actual number of points divided by maximum possible to get
	risk = (this->acc_TurnPoints()/50.0);
	if (Agression == 1)
	{
		if (risk < (0.50 + 0.05 * (place(players,bots,number_of_players) - 1))) return true; //lowest posiible value is 6 1+1+1+1+2 so (6/50+1)/2=0.56
		else return false;
	}
	if (Agression == 2)
	{
		if (risk < (0.55 + 0.075 * (place(players, bots, number_of_players) - 1))) return true; // additional value is representation of playing more risky when being on lower places
		else return false;
	}
	if (Agression == 3)
	{
		if (risk < (0.60 + 0.1 * (place(players, bots, number_of_players) - 1))) return true;
		else return false;
	}
}
void Bot::b_roll()
{
	//this function decides how many dices and which of them should be rolled
	bool roll_1 = false;
	bool roll_2 = false;
	bool roll_3 = false;

	//for showing which dices are getting rerolled
	stringstream temp;

	//for straights
	int temp_fs[6] = { 0 };

	//saving first values of map
	int first = 0;

	map<int, int> NumberOfValues;
	int sum = 0;

	//defining number of each dice value as 0
	for (int i = 1; i <= 6; i++)
	{
		NumberOfValues[i] = 0;
	}
	int doublevalue=0;
	int value = 0;
	//counting number of each dice value and sum
	for (int i = 0; i < 5; i++)
	{
		NumberOfValues[this->acc_RollADice(i)] += 1;
		sum += (this->acc_RollADice(i));
	}
	
	for (int i = 1; i <= 6; i++)
	{
		temp_fs[i - 1] = NumberOfValues[i];
		if (NumberOfValues[i] > 1)
		{
			temp_fs[i - 1] = 1;
			doublevalue = i;
		}
		else temp_fs[i - 1] = NumberOfValues[i];

		if (NumberOfValues[i] == 4) roll_1 = true;
		if (NumberOfValues[i] == 3) roll_2 = true;
		if (NumberOfValues[i] == 2) roll_3 = true;
	}

	//definitions of small straights
	bool s_straight1 = (temp_fs[0] == 1 && temp_fs[1] == 1 && temp_fs[2] == 1 && temp_fs[3] == 1); // 1 2 3 4
	bool s_straight2 = (temp_fs[1] == 1 && temp_fs[2] == 1 && temp_fs[3] == 1 && temp_fs[4] == 1); // 2 3 4 5
	bool s_straight3 = (temp_fs[2] == 1 && temp_fs[3] == 1 && temp_fs[4] == 1 && temp_fs[5] == 1); // 3 4 5 6

	//close to small straight
	bool close_ss_1 = (temp_fs[0] == 1 && temp_fs[1] == 1 && temp_fs[2] == 1); // 1 2 3
	bool close_ss_2 = (temp_fs[1] == 1 && temp_fs[2] == 1 && temp_fs[3] == 1); // 2 3 4
	bool close_ss_3 = (temp_fs[2] == 1 && temp_fs[3] == 1 && temp_fs[4] == 1); // 3 4 5
	bool close_ss_4 = (temp_fs[3] == 1 && temp_fs[4] == 1 && temp_fs[5] == 1); // 4 5 6

	cout << endl;

	// if small straight, bot shoud try to get large straight
	if ( s_straight1 || s_straight2 || s_straight3 )
	{
		for (int i = 0; i < 5; i++)
		{
			if (NumberOfValues[this->acc_RollADice(i)] == 2) value = i;
		}
		if (value == 0 && s_straight1) //when 1 2 3 4 and 6
		{
			for (int i = 0; i < 5; i++)
			{
				if (this->acc_RollADice(i) == 6) value = i;
			}
		}
		if (value == 0 && s_straight3) //when 1 and 3 4 5 6
		{
			for (int i = 0; i < 5; i++)
			{
				if (this->acc_RollADice(i) == 1) value = i;
			}
		}
		cout << "Rerolling: " << value+1 << endl;
		this->set_RollADice(value);
	}
	else if ((close_ss_1 || close_ss_2 ||close_ss_3 || close_ss_4) && doublevalue == 0)
	{
		if (close_ss_1)
		{
			for (int i = 0; i < 5; i++)
			{
				if (this->acc_RollADice(i) > 3)
				{
					temp << i+1;
					this->set_RollADice(doublevalue);
				}
			}
		}
		if (close_ss_2)
		{
			for (int i = 0; i < 5; i++)
			{
				if (this->acc_RollADice(i) < 2 || this->acc_RollADice(i)>4)
				{
					temp << i+1;
					this->set_RollADice(doublevalue);
				}
			}
		}
		if (close_ss_3)
		{
			for (int i = 0; i < 5; i++)
			{
				if (this->acc_RollADice(i) < 3 || this->acc_RollADice(i) > 5)
				{
					temp << i+1;
					this->set_RollADice(doublevalue);
				}
			}
		}
		if (close_ss_4)
		{
			for (int i = 0; i < 5; i++)
			{
				if (this->acc_RollADice(i) < 4)
				{
					temp << i+1;
					this->set_RollADice(doublevalue);
				}
			}
		}
		cout << "Rerolling: " << temp.str() << endl;
	}
	else if (roll_1)
	{
		for (auto it = NumberOfValues.begin(); it!=NumberOfValues.end();it++)
		{
			if (it->second == 1) first = it->first;
		}
		for (int i = 0; i < 5; i++)
		{
			if (acc_RollADice(i) == first)
			{
				temp << i + 1;
				this->set_RollADice(i);
			}
		}
		cout << "Rerolling: " << temp.str() << endl;
	}

	else if (roll_2)
	{
		int second=0;
		for (auto it = NumberOfValues.begin(); it != NumberOfValues.end(); it++)
		{
			if (it->second == 2)
			{
				if(first < it->first) first = it->first;
			}

			if (it->second == 1)
			{
				if (first == 0) first = it->first;
				else second = it->first;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (acc_RollADice(i) == first || acc_RollADice(i)==second)
			{
				temp << i+1;
				this->set_RollADice(i);
			}
		}
		cout << "Rerolling: " << temp.str() << endl;
	}

	else if (roll_3)
	{
		for (auto it = NumberOfValues.begin(); it != NumberOfValues.end(); it++)
		{
			if (it->second == 2) first = it->first;
		}
		for (int i = 0; i < 5; i++)
		{
			if (acc_RollADice(i) !=first)
			{
				temp << i + 1;
				this->set_RollADice(i);
			}
		}
		cout << "Rerolling: " << temp.str() << endl;
	}
	cout << endl;
	system("pause");
}
