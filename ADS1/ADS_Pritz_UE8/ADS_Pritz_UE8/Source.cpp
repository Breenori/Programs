#include<iostream>
#include<string>
#include<fstream>
#include<random>
#include<iomanip>
#include<regex>
using namespace std;

enum role_type { rt_nitwit, rt_propagator, rt_suppressor };
enum method_type { mt_daley, mt_maki, mt_maki_prop, mt_daley_prop };

// Returns the role of a random person (with their index) based on the number of the roles.
role_type get_random_role(int const index, int const nitwits, int const propagators, int const suppressors);
// Runs a simulation of rumour spreading with the defined method and population size and logs the values to a file.
void rumour_simulation(int const size, method_type method, string const& outputfile);
// Reads and returns a number and makes sure it's valid
int read_number();
// Returns the method by asking for user input.
method_type read_method();

void main()
{
	cout << "Please enter the population size: ";
	int population_size(read_number());
	if (population_size > 0)
	{
		method_type method(read_method());
		if (population_size > 10000)
		{
			cout << "Please wait! Based on the entered number this can take a while...\n";
		}
		rumour_simulation(population_size, method, "output.csv");
	}
	else
	{
		cout << "Entered size was too low. Terminating.";
	}
}

void rumour_simulation(int const size, method_type const method, string const& outputfile)
{
	// Normal rand() function can only get numbers up to about 32000.
	// Thats why a different random number function is needed.
	random_device rand_dev;
	mt19937 rand_gen(rand_dev());
	uniform_real_distribution<> rand_distrib(0, size);

	// At the beginning there is only 1 propagator, the rest is made up of nitwits.
	int propagators(1);
	int nitwits(size - 1);
	int suppressors(0);

	// The files should be written to a file that can be opened in excel.
	ofstream out(outputfile);

	out << "\"nitwits\";\"propagators\";\"suppressors\"\n";
	out << to_string(nitwits) + ";" + to_string(propagators) + ";" + to_string(suppressors) + "\n";
	while (propagators > 0 && nitwits > 0)
	{
		// First, we need 2 random people.
		int p1_index = rand_distrib(rand_gen);
		int p2_index = rand_distrib(rand_gen);

		// If the same person has been selected twice, make sure they are different afterwards.
		while (p2_index == p1_index)
		{
			p2_index = rand_distrib(rand_gen);
		}

		// Since this is the approach without a vector, the role has to be determined using the index and the distribution of roles.
		role_type person1(get_random_role(p1_index, nitwits, propagators, suppressors));
		role_type person2(get_random_role(p2_index, nitwits, propagators, suppressors));

		if (method == mt_maki_prop || method == mt_daley_prop)
		{
			if (propagators > 1 || (person2 != rt_propagator && propagators == 1))
			{
				person1 = rt_propagator;
			}
		}

		if (person1 == rt_propagator && person2 == rt_nitwit || person1 == rt_nitwit && person2 == rt_propagator)
		{
			propagators++;
			nitwits--;
		}
		else if (person1 == rt_propagator && person2 == rt_propagator)
		{
			// Only one propagator becomes a suppressor for maki, but both become one for kendal method.
			suppressors += 1;
			propagators -= 1;
			if (method == mt_daley || method == mt_daley_prop)
			{
				suppressors += 1;
				propagators -= 1;
			}
		}
		else if (person1 == rt_propagator && person2 == rt_suppressor || person1 == rt_suppressor && person2 == rt_propagator)
		{
			propagators--;
			suppressors++;
		}

		// Write the current state to the specified file
		out << to_string(nitwits) + ";" + to_string(propagators) + ";" + to_string(suppressors) + "\n";
	}
	out.close();

	// Write the summary to the console with 1 number after the comma.
	// Role-name length has been accounted for in the width, so the values are in line.
	cout << "nitwits: " << setw(20 - 7) << fixed << setprecision(1) << nitwits * 100.0 / size << "%\n";
	cout << "propagators: " << setw(20 - 11) << fixed << setprecision(1) << propagators * 100.0 / size << "%\n";
	cout << "suppressors: " << setw(20 - 11) << fixed << setprecision(1) << suppressors * 100.0 / size << "%";
}
role_type get_random_role(int const index, int const nitwits, int const propagators, int const suppressors)
{
	// Taking the index and the number of certain roles into account, a random role can be determined without a vector.
	if (index < nitwits)
	{
		return rt_nitwit;
	}
	else if (index < (nitwits + propagators))
	{
		return rt_propagator;
	}
	else
	{
		return rt_suppressor;
	}
}
int read_number()
{
	int num(0);
	cin >> num;

	// make sure the user enters a valid number
	while (cin.fail())
	{
		num = 0;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "The value must be numeric (MAX:" << INT_MAX << "): ";
		cin >> num;
	}
	// If there's something after the number, clear it.
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return num;
}
method_type read_method()
{
	char ans_basic(' ');
	while (ans_basic != 'd' && ans_basic != 'D' && ans_basic != 'm' && ans_basic != 'M')
	{
		cout << "Do you want to use the Daley or Maki method? (D/M): ";
		cin >> ans_basic;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	char ans_ext(' ');
	while (ans_ext != 'y' && ans_ext != 'Y' && ans_ext != 'n' && ans_ext != 'N')
	{
		cout << "Do you want one person to ALWAYS propagate? (Y/N): ";
		cin >> ans_ext;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	if (ans_basic == 'd' || ans_basic == 'D')
	{
		if (ans_ext == 'y' || ans_ext == 'Y')
		{
			return mt_daley_prop;
		}
		else
		{
			return mt_daley;
		}
	}
	else
	{
		if (ans_ext == 'y' || ans_ext == 'Y')
		{
			return mt_maki_prop;
		}
		else
		{
			return mt_maki;
		}
	}
}
