#include "Player.h"

int Player::get_RollADice(int x)
{
	return RollADice[x];
}

int Player::get_NumberOfPoints()
{
	return NumberOfPoints;
}

int Player::get_TurnPoints()
{
	return TurnPoints;
}

void Player::set_TurnPoints(int x)
{
	TurnPoints = x;
}
void Player::set_NumberOfPoints(int x)
{
	NumberOfPoints+=x;
}
void Player::set_RollADice(int x)
{
	RollADice[x] = rand() % 6 + 1;
}

void Player::roll()
{
	for (int i = 0; i < 5; i++)
	{
		RollADice[i] = rand() % 6 + 1;
	}
}
void Player::roll(int x) //rolling again
{
	string a;
	string temp;

	cin.ignore();
	cout << "Which dices you want to reroll? (type number of dices separated by spaces. If u changed your mind type 0)" << endl;
	getline(cin, a);

	//checking if whole string is digit
	for (auto it = a.begin(); it != a.end(); it++)
	{
		//if value is digit copy it to temp string
		if (isdigit(*it))
		{
			temp.push_back(*it);
		}
	}

	//deleting duplicates

	//sorting string
	sort(temp.begin(), temp.end());

	//picking unique values
	auto res = unique(temp.begin(), temp.end());
	a = string(temp.begin(), res);

	//deleting numbers 0,6,7,8,9
	char chars[] = "06789";
	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		a.erase(std::remove(a.begin(), a.end(), chars[i]), a.end());
	}
	cout << "Rerolling: " << a << endl;

	// converting string to int piece by piece
	int reroll;
	for (int i = 0; i < a.length(); i++)
	{
		string t;
		t.push_back(a[i]);
		reroll = stoi(t);
		int n_value = rand() % 6 + 1;
		RollADice[reroll - 1] = n_value;
		t.erase(t.begin(), t.end());
	}
	system("pause");
}
void Player::set_Name(string _Name)
{
	Name = _Name;
}

string Player::get_Name()
{
	return Name;
}

int Player::reroll()
{
	string x;

	do
	{
		cout << "Do you want to reroll any dice? (y/n)" << endl;
		cin >> x;
	} while ((x[0]!='n') && (x[0]!='y'));

	//if no
	if (x[0] == 'n') return 0;
	//if yes 
	if (x[0] == 'y')
	{
		roll(1);
		return 1;
	}

}