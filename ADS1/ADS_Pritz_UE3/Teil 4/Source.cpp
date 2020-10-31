#include<iostream>
#include<time.h>
using std::string;
using std::cin;
using std::cout;

char ask_user();
bool action(char ans, bool chambers[6], int& cur);
void print_evaluation(int bullet_fired, int successes);

void main()
{
	srand(time(0));

	bool chamber_states[6] = { false, false, false, false, false, false};
	chamber_states[rand() % 6] = true;

	int current_chamber(0);
	int successes(0);
	bool bullet_fired = false;
	char answer(' ');

	while (successes < 10 && !bullet_fired)
	{
		cout << "Round: " << (successes + 1) << std::endl;

		answer = ask_user();

		if (action(answer, chamber_states, current_chamber))
		{
			bullet_fired = true;
		}
		else
		{
			cout << "klick" << std::endl << std::endl;
			successes++;
		}
	}

	print_evaluation(bullet_fired, successes);
}

char ask_user()
{
	string answer(" ");
	while (answer != "y" && answer != "n")
	{
		cout << "Do you want to turn before shooting? (y/n) ";
		cin >> answer;
	}

	return answer[0];
}
bool action(char ans, bool chambers[6], int& cur)
{
	if (ans == 'y')
	{
		cur = rand() % 6;
	}

	if (chambers[cur])
	{
		cur = (cur + 1) % 6;
		return true;
	}
	else
	{	
		cur = (cur + 1) % 6;
		return false;
	}
	
}
void print_evaluation(int bullet_fired, int successes)
{
	cout << std::endl;
	if (bullet_fired)
	{
		cout << "peng!" << std::endl << std::endl;
		cout << "You lost!" << std::endl;
		cout << "You survived " << successes << "/10 rounds.";
	}
	else
	{
		cout << "You won!\n";
		cout << "You survived all 10 rounds.";
	}
	cout << std::endl;
}