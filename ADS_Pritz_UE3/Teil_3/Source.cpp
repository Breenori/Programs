#include<iostream>
#include<string>
#include<stdlib.h>
using std::string;
using std::cin;
using std::cout;

void draw_ASCII(int fails);
void print_state(string s, int tries);
void print_state(string s, int tries, bool outcome);
void prepare_string(string& s, bool is_secret);
char make_guess();
void check_guess(string s, string& secret, char guess, int& tries);

void main()
{
	cout << "Please enter your word: " << std::endl;
	string s("");
	std::getline(cin,s);
	prepare_string(s, false);

	string secret = s;
	prepare_string(secret, true);

	char guess;
	int tries(10);
	bool guessed(false);

	while (tries > 0 && !guessed)
	{
		print_state(secret, tries);

		guess = make_guess();
		
		check_guess(s, secret, guess, tries);
		

		if (secret == s)
		{
			guessed = true;
		}
	}

	print_state(s, tries, guessed);
}

void print_state(string s, int tries)
{
	system("CLS");

	for (int i(0); i < s.length(); i++)
	{
		cout << s[i] << " ";
	}

	draw_ASCII(10 - tries);

	cout << tries << " tries remaining." << std::endl;
}
void print_state(string s, int tries, bool outcome)
{
	system("CLS");

	if (tries < 10)
		draw_ASCII(10 - tries);

	cout << tries << " tries remaining." << std::endl;

	if (outcome == true)
	{
		cout << "Congratulations, you won!" << std::endl;
	}
	else
	{
		cout << "You lost!" << std::endl;
	}

	cout << "The secret word was:" << std::endl << std::endl;

	for (int i(0); i < s.length(); i++)
	{
		cout << s[i] << " ";
	}

	cout << std::endl << std::endl;
}
void prepare_string(string& s, bool is_secret)
{
	if (is_secret)
	{
		for (int i(0); i < s.length(); i++)
		{
			if (s[i] != ' ')
			{
				s[i] = '_';
			}
		}
	}
	else
	{
		for (int i(0); i < s.length(); i++)
		{
			if (s[i] >= 'a' && s[i] <= 'z')
			{
				s[i] = std::toupper(s[i]);
			}
		}
	}
}
void draw_ASCII(int fails)
{
	cout << std::endl;
	if (fails == 0)
	{
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;

	}
	else if (fails == 1)
	{
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << " _____" << std::endl;
	}
	else if (fails == 2)
	{
		cout << "" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}
	else if (fails == 3)
	{
		cout << "  ________" << std::endl;
		cout << "  |/" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}
	else if (fails == 4)
	{
		cout << "  ________" << std::endl;
		cout << "  |/     |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}
	else if (fails == 5)
	{
		cout << "  ________" << std::endl;
		cout << "  |/     |" << std::endl;
		cout << "  |     (_)" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}
	else if (fails == 6)
	{
		cout << "  ________" << std::endl;
		cout << "  |/     |" << std::endl;
		cout << "  |     (_)" << std::endl;
		cout << "  |	 |" << std::endl;
		cout << "  |      |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}
	else if (fails == 7)
	{
		cout << "  ________" << std::endl;
		cout << "  |/     |" << std::endl;
		cout << "  |     (_)" << std::endl;
		cout << "  |	 |/" << std::endl;
		cout << "  |      |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}
	else if (fails == 8)
	{
		cout << "  ________" << std::endl;
		cout << "  |/     |" << std::endl;
		cout << "  |     (_)" << std::endl;
		cout << "  |     \\|/" << std::endl;
		cout << "  |      |" << std::endl;
		cout << "  |" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}
	else if (fails == 9)
	{
		cout << "  ________" << std::endl;
		cout << "  |/     |" << std::endl;
		cout << "  |     (_)" << std::endl;
		cout << "  |     \\|/" << std::endl;
		cout << "  |      |" << std::endl;
		cout << "  |     /" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}
	else if (fails == 10)
	{
		cout << "  ________" << std::endl;
		cout << "  |/     |" << std::endl;
		cout << "  |     (_)" << std::endl;
		cout << "  |     \\|/" << std::endl;
		cout << "  |      |" << std::endl;
		cout << "  |     / \\" << std::endl;
		cout << "  |" << std::endl;
		cout << " _|___" << std::endl;
	}

	cout << std::endl;
}
char make_guess() {
	bool wrong_input = false;
	string guess_string = "???";

	while (guess_string.length() != 1)
	{
		if (!wrong_input)
		{
			cout << "Please enter your guess:" << std::endl;;
		}
		else
		{
			cout << "Please enter ONE character only:" << std::endl;;
			wrong_input = false;
		}

		cin >> guess_string;

		if (guess_string.length() != 1)
		{
			wrong_input = true;
		}
	}

	char guess_char = std::toupper(guess_string[0]);

	return guess_char;
}
void check_guess(string s, string& secret, char guess, int& tries)
{
	if (s.find(guess, 0) != string::npos)
	{
		int offset(0);
		while (s.find(guess, offset) != string::npos)
		{
			secret[s.find(guess, offset)] = guess;
			offset = s.find(guess, offset) + 1;
		}
	}
	else
	{
		tries--;
	}

}