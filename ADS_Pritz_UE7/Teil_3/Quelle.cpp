#include<iostream>
#include<string>
#include<time.h>
#include<iomanip>
#include<stdlib.h>
using namespace std;

enum mode_type { mt_color, mt_third, mt_number, mt_quit, mt_none };
enum color_type { ct_red, ct_black};

// Returns the mode the user chose in an interactive dialogue
mode_type choose_mode();
// Returns whether the user won with the chosen color
bool check_color(color_type const color);
// Returns the color that the user chose in an interactive dialogue
color_type choose_color();
// Returns whether the user won with the chosen third
bool check_third(int const third_index);
// Returns the index of the third, that the user chose 
int choose_third();
// Returns whether the user won with the chosen number
bool check_number(int const guess);
// Returns the number that the user chose. With error handling!
int choose_number();
// Returns the amount of money the user wants to start with
__int64 get_chips();
// Returns the amount of money the user wants to use for the current bet
__int64 place_bet(__int64& money);
// Prints current money, mode and bet.
void print_info(__int64 const money, __int64 const bet, mode_type const mode = mt_none);
// Prints a fancy placeholder that spells "roulette" in ascii art.
void print_placeholder();

void main()
{
	srand((int)time(0));

	__int64 money(get_chips());

	bool playing(true);
	bool won(false);
	bool first(true);
	// As long as the user has money or doesn't decide to quit, he can continue playing.
	while (playing)
	{
		print_info(money, 0);
		if (!first)
		{
			if (won)
			{
				cout << fixed << setw(36) << "!!!!YOU WON!!!\n\n";
				won = false;
			}
			else
			{
				cout << fixed << setw(36) << "!!!YOU LOST!!!\n\n";
			}
		}
		// Since there is nothing to print in the first round we need a flag
		first = false;

		if (money > 0)
		{
			mode_type mode(choose_mode());
			print_info(money, 0, mode);

			if (mode != mt_quit)
			{
				__int64 bet(place_bet(money));
				print_info(money, bet, mode);


				// It usually would be better to first generate the random number and then pass it to the function
				// However, that way the result can be determined via breakpoints which encourages cheating.
				if (mode == mt_color)
				{
					color_type guess(choose_color());


					if (check_color(guess))
					{
						// Depending on the mode, the player gets a different amount of money on win
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
			// If the user has no money, stop the game.
			cout << fixed << setw(45) << ">>You don't have any chips<<\n\n";
			cout << fixed << setw(43) << "!!!THANKS FOR PLAYING!!!\n\n";
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
	// Make the user choose one of the options.
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
		// Black wins with a certainty of 18/37
		return num > 0 && num <= 18;
	}
	else
	{
		// Red wins with a certainty of 18/37
		return num > 18 && num <= 36;
	}
	// So there's a 1/37th chance of rolling 0 -> can't win with either color
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
	// Thirds are between 1-12, 13-24 and 25-36
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

	int ans;
	cin >> ans;
	while (ans > 36 && ans < 0 || cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please choose a number between 0 and 36: ";
		cin >> ans;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return ans;
}
__int64 get_chips()
{
	__int64 money;
	cout << "How much money do you want to spend on chips?\n";
	cin >> money;
	while (money < 0 || cin.fail())
	{
		cin.clear();
		cin.ignore(INT64_MAX, '\n');
		cout << "Please enter a valid number:\n";
		cin >> money;
	}
	cin.clear();
	cin.ignore(INT64_MAX, '\n');

	return money;
}
__int64 place_bet(__int64& money)
{
	__int64 bet;
	cout << "How much do you want to bet?\n";
	cin >> bet;
	while (bet < 0 || bet > money || cin.fail())
	{
		cin.clear();
		cin.ignore(INT64_MAX, '\n');
		cout << "Please place a valid bet:\n";
		cin >> bet;
	}
	cin.clear();
	cin.ignore(INT64_MAX, '\n');
	money -= bet;

	return bet;
}

void print_info(__int64 const money, __int64 const bet, mode_type const mode)
{
	system("CLS");
	// I had to use dollars since console window doesn't support unicode out of the box, which is why it cant print €

	// First we print default info
	cout << "Money: " << fixed << setw(20) << money << "$";
	cout << fixed << setw(10) << "Bet: " << fixed << setw(20) << bet << "$\n";
	// Then the selected mode.
	if (mode != mt_none)
	{
		cout << fixed << setw(38) << "Mode: ";
		if (mode == mt_number)
		{
			cout << fixed << setw(22) << "number\n";
		}
		else if (mode == mt_third)
		{
			cout << fixed << setw(22) << "third\n";
		}
		else if (mode == mt_color)
		{
			cout << fixed << setw(22) << "color\n";
		}
		print_placeholder();
		cout << endl;
	}
	else
	{
		cout << endl;
		print_placeholder();
		cout << endl;
	}
}
void print_placeholder()
{
	for (int i(0); i < 3; i++)
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

