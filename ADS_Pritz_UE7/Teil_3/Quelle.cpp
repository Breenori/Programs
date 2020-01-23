#include<iostream>
#include<string>
#include<time.h>
#include<iomanip>
#include<stdlib.h>
using namespace std;

enum mode_type { mt_color, mt_third, mt_number, mt_quit, mt_none };
enum color_type { ct_red, ct_black};

mode_type choose_mode();
bool check_color(color_type const color);
color_type choose_color();
bool check_third(int const third_index);
int choose_third();
bool check_number(int const guess);
int choose_number();
__int64 place_bet(__int64& money);
void print_info(__int64 const money, __int64 const bet, mode_type const mode = mt_none);
void print_placeholder(int offset = 0);

void main()
{
	srand((int)time(0));

	__int64 money(0);
	cout << "Please enter your investment:\n";
	cin >> money;

	bool playing(true);
	bool won(false);
	while (playing)
	{
		print_info(money, 0);
		if (won)
		{
			cout << fixed << setw(50) << "!!!!YOU WON!!!\n\n";
			won = false;
		}

		if (money > 0)
		{
			mode_type mode(choose_mode());
			print_info(money, 0, mode);

			if (mode != mt_quit)
			{
				__int64 bet(place_bet(money));
				print_info(money, bet, mode);

				if (mode == mt_color)
				{
					color_type guess(choose_color());


					if (check_color(guess))
					{
						money += 2 * bet;
						won = true;
					}
				}
				else if (mode == mt_third)
				{
					int guess(choose_third());

					if (check_third(guess))
					{
						money += 3 * bet;
						won = true;
					}
				}
				else if (mode == mt_number)
				{
					int guess(choose_number());

					if (check_number(guess))
					{
						money += 36 * bet;
						won = true;
					}
				}
			}
			else
			{
				cout << fixed << setw(50) << "!!!!THANKS FOR PLAYING!!!\n\n";
				playing = false;
				system("pause");
			}
		}
		else
		{
			cout << fixed << setw(50) << "!!!!YOU LOST!!!\n\n";
			cout << fixed << setw(50) << "!!!!YOU LOST!!!\n\n";
			cout << fixed << setw(50) << "!!!!YOU LOST!!!\n\n";
			playing = false;
			system("pause");
		}
	}
	cout << endl;
}

mode_type choose_mode()
{
	cout << "What do you want to do?\n";
	cout << "(1) Bet on color\n";
	cout << "(2) Bet on third\n";
	cout << "(3) Bet on number\n";
	cout << "(4) Quit\n";
	cout << endl;
	string ans;
	getline(cin, ans);
	while (ans != "1" && ans != "2" && ans != "3" && ans != "4")
	{
		cout << "Please choose one of the options: ";
		getline(cin, ans);
	}

	if (ans == "1")
	{
		return mt_color;
	}
	else if (ans == "2")
	{
		return mt_third;
	}
	else if (ans == "3")
	{
		return mt_number;
	}
	else
	{
		return mt_quit;
	}
}
bool check_color(color_type const color)
{
	unsigned int num(rand() % 37);
	if (color == ct_black)
	{
		return (num % 2)==0;
	}
	else
	{
		return !((num % 2)==0);
	}
}
color_type choose_color()
{
	cout << "Pick your color:\n";
	cout << "(1) Red\n";
	cout << "(2) Black\n";
	cout << endl;

	string ans;
	getline(cin, ans);
	while (ans != "1" && ans != "2")
	{
		cout << "Please choose one of the options: ";
		getline(cin, ans);
	}

	if (ans == "1")
	{
		return ct_red;
	}
	else {
		return ct_black;
	}
}
bool check_third(int const third_index)
{
	unsigned int num(rand() % 37);
	return (num > third_index * 12) && (num <= (third_index + 1) * 12);
}
int choose_third()
{
	cout << "Pick your third:\n";
	cout << "(1) 1-12\n";
	cout << "(2) 13-24\n";
	cout << "(3) 25-36\n";
	cout << endl;

	string ans;
	getline(cin, ans);
	while (ans != "1" && ans != "2" && ans != "3")
	{
		cout << "Please choose one of the options: ";
		getline(cin, ans);
	}

	if (ans == "1")
	{
		return 0;
	}
	else if (ans == "2")
	{
		return 1;
	}
	else {
		return 2;
	}
}
bool check_number(int const guess)
{
	return guess == rand() % 37;
}
int choose_number()
{
	cout << "Pick your number:\n";
	cout << endl;

	int ans;
	cin >> ans;
	while (ans > 36 && ans < 0 || cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please choose a number between 0 and 36: ";
		cin >> ans;
	}

	return ans;
}
__int64 place_bet(__int64& money)
{
	__int64 bet;
	cout << "How much do you want to bet?\n";
	cin >> bet;
	while (bet < 0 || bet > money || cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please place a valid bet that doesn't exceed your capital:\n";
		cin >> bet;
	}
	money -= bet;

	return bet;
}

void print_info(__int64 const money, __int64 const bet, mode_type const mode)
{
	system("CLS");
	cout << "Money: " << fixed << setw(20) << money;
	cout << fixed << setw(32) << "Bet: " << fixed << setw(20) << bet << "\n";
	if (mode != mt_none)
	{
		cout << fixed << setw(60) << "Mode: ";
		if (mode == mt_number)
		{
			cout << fixed << setw(20) << "number\n";
		}
		else if (mode == mt_third)
		{
			cout << fixed << setw(20) << "third\n";
		}
		else if (mode == mt_color)
		{
			cout << fixed << setw(20) << "color\n";
		}
		print_placeholder(1);
		cout << endl;
	}
	else
	{
		print_placeholder(2);
	}
}
void print_placeholder(int offset)
{
	for (int i(0); i < 3+offset; i++)
	{
		cout << endl;
	}
	cout << "                         888          888   888\n" <<
			"                         888          888   888\n" <<
			"                         888          888   888\n" <<
			"888d888 .d88b.  888  888 888  .d88b. 888888888888   .d88b.\n" <<
			"888P\"  d88\"\"88b 888  888 888 d8P  Y8b 888   888    d8P  Y8b\n" <<
			"888    888  888 888  888 888 88888888 888   888    88888888\n" <<
			"888    Y88..88P Y88b 888 888 Y8b      .Y88b .Y88b  .Y8b.\n" <<
			"888     \"Y88P\"   \"Y88888 888 \"Y8888    \"Y888 \"Y888  \"Y8888\n";
	for (int i(0); i < 3; i++)
	{
		cout << endl;
	}
}

