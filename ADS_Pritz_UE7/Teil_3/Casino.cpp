#include<iostream>
#include<string>
#include<time.h>
#include<iomanip>
using namespace std;

enum mode_type { mt_color, mt_third, mt_number, mt_quit };
enum color_type { ct_red, ct_black };

mode_type choose_mode();
bool check_color(color_type const color, int const num);
color_type choose_color();
bool check_third(int const third_index, int const num);
unsigned int choose_third();
bool check_number(int const guess, int const num);
unsigned int choose_number();


void main()
{
	srand((int)time(0));

	__int64 money(0);
	cout << "Please enter your investment:\n";
	cin >> money;

	bool playing(true);
	while (playing)
	{
		cout << money << endl << endl;
		mode_type mode(choose_mode());
		__int64 bet(0);
		cout << "How much do you want to bet?\n";
		cin >> bet;
		money -= bet;
		unsigned int result(0);

		if (mode == mt_color)
		{
			color_type guess(choose_color());

			result = rand() % 37;
			if (check_color(guess, result))
			{
				money += 2 * bet;
			}
		}
		else if (mode == mt_third)
		{
			unsigned int guess(choose_third());

			result = rand() % 37;
			if (check_third(guess, result))
			{
				money += 3 * bet;
			}
		}
		else if (mode == mt_number)
		{
			unsigned int guess(choose_number());

			result = rand() % 37;
			if (check_number(guess, result))
			{
				money += 36 * bet;
			}
		}
		else
		{
			playing = false;
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
bool check_color(color_type const color, int const num)
{
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
bool check_third(int const third_index, int const num)
{
	return (num > third_index * 12) && (num <= (third_index + 1) * 12);
}
unsigned int choose_third()
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
bool check_number(int const guess, int const num)
{
	return guess == num;
}
unsigned int choose_number()
{
	cout << "Pick your number:\n";
	cout << endl;

	unsigned int ans;
	cin >> ans;
	while (ans > 36)
	{
		cout << "Please choose a number between 0 and 36: ";
		cin >> ans;
	}

	return ans;
}
