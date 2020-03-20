#include<iostream>
#include<stdlib.h>
using std::cout;
using std::cin;
using std::string;
using std::endl;

enum action_t { start, take_l, take_r, take_both };

// Returns a number entered by the user. Displays the given message for input information.
int get_number(string const& message = "Please enter a number:");
// Defines the amount of stones left and right with user input.
void initialize(size_t& amount_l, size_t& amount_r);
// Computer makes move corresponding to the current stones left
action_t make_move(size_t& amount_l, size_t& amount_r);
// Let the user decide and make a move.
action_t user_move(size_t& amount_l, size_t& amount_r);
// Prints the current state of the game.
void print_gamestate(size_t const amount_l, size_t const amount_r, action_t action);
// Runs the game-loop and returns the winning user
size_t play_game(size_t& amount_l, size_t& amount_r);

void main()
{
	size_t amount_l(0);
	size_t amount_r(0);
	initialize(amount_l, amount_r);

	if (play_game(amount_l, amount_r) == 0)
	{
		cout << "Congratulations! You won!";
	}
	else
	{
		cout << "You lost! Better luck next time. ;)";
	}
}

int get_number(string const& message)
{
	{
		cout << message << endl;
		int num(0);
		cin >> num;
		// As long as input for int failed, repeat read
		while (cin.fail())
		{
			cout << "Invalid value. Please enter a number.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> num;
		}
		// In case something is entered after int. ex "10a". Isn't counted as cin.fail().
		cin.clear();
		cin.ignore(INT_MAX, '\n');


		return num;
	}
}
void initialize(size_t& amount_l, size_t& amount_r)
{
	while (amount_l < 5 || amount_l > 25)
	{
		amount_l = get_number("Please enter the number of stones on the left (5-25)");
	}
	while (amount_r < 5 || amount_r > 25)
	{
		amount_r = get_number("Please enter the number of stones on the right (5-25)");
	}
	system("cls");
}
action_t make_move(size_t& amount_l, size_t& amount_r)
{
	// If there is one left on both sides, remove both to win.
	if (amount_l == 1 && amount_r == 1)
	{
		amount_l--;
		amount_r--;
		return take_both;
	}
	// If one side has one left and other side is odd - remove both to ensure win.
	else if ((amount_r == 1 && amount_l % 2 != 0) || (amount_l == 1 && amount_r % 2 != 0))
	{
		amount_l--;
		amount_r--;
		return take_both;
	}
	// If left is one and right is even - remove left to ensure win.
	else if (amount_l == 1 && amount_r % 2 == 0)
	{
		amount_l--;
		return take_l;
	}
	// If right is one and left is even - remove right to ensure win.
	else if (amount_r == 1 && amount_l % 2 == 0)
	{
		amount_r--;
		return take_r;
	}
	// If 2 left on both sides, make it odd (else the enemy could just take both side and win)
	else if (amount_l == 2 && amount_r == 2)
	{
		amount_l--;
		return take_l;
	}
	// Maintain even sides by taking both
	else if (amount_l >= 1 && amount_r >= 1 && amount_l - amount_r == 0)
	{
		amount_l--;
		amount_r--;
		return take_both;
	}
	// Create even sides
	else if (amount_l > amount_r)
	{
		amount_l--;
		return take_l;
	}
	else if (amount_r > amount_l)
	{
		amount_r--;
		return take_r;
	}
}
action_t user_move(size_t& amount_l, size_t& amount_r)
{
	cout << "What would you like to do?\n";
	cout << "(1) Take left\n";
	cout << "(2) Take right\n";
	cout << "(3) Take both\n";

	size_t ans(0);
	while (ans < 1 || ans > 3)
	{
		ans = get_number("");
		if (ans == 1 && amount_l == 0)
		{
			cout << "Left side has no stones left! Please re-enter: ";
			ans = 0;
		}
		else if (ans == 2 && amount_r == 0)
		{
			cout << "Right side has no stones left! Please re-enter: ";
			ans = 0;
		}
		else if (ans == 3 && (amount_l == 0 || amount_r == 0))
		{
			cout << "One of the sides is already empty! Please re-enter: ";
			ans = 0;
		}
	}

	if (ans == 1)
	{
		amount_l--;
		return take_l;
	}
	else if (ans == 2)
	{
		amount_r--;
		return take_r;
	}
	else
	{
		amount_l--;
		amount_r--;
		return take_both;
	}
}
void print_gamestate(size_t const amount_l, size_t const amount_r, action_t action)
{
	if (action != start)
	{
		if (action == take_l)
		{
			cout << "1 taken from left.";
		}
		else if (action == take_r)
		{
			cout << "1 taken from right.";
		}
		else if (action == take_both)
		{
			cout << "1 taken from both sides.";
		}
		cout << endl;
		cout << "\t|\n";
		cout << "\tv";
		cout << endl;
	}
	cout << amount_l << " | " << amount_r << endl;
	for (size_t i(0); i < amount_l; i++)
	{
		cout << (char)220 << " ";
	}
	cout << "|";
	for (size_t i(0); i < amount_r; i++)
	{
		cout << " " << (char)220;
	}
	cout << endl << endl << endl;
}
size_t play_game(size_t& amount_l, size_t& amount_r)
{
	size_t current_user(0);
	action_t last_action(start);
	while (amount_l > 0 || amount_r > 0)
	{
		if (current_user == 1)
		{
			system("cls");
		}
		print_gamestate(amount_l, amount_r, last_action);

		if (current_user == 0)
		{
			last_action = user_move(amount_l, amount_r);
		}
		else
		{
			cout << "Computers turn:\n";
			last_action = make_move(amount_l, amount_r);
		}
		current_user = (current_user + 1) % 2;
	}
	print_gamestate(amount_l, amount_r, last_action);

	return current_user = (current_user + 1) % 2;
}