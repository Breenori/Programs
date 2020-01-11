/*#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<random>
#include<iomanip>
using namespace std;

enum role_type { rt_nitwit, rt_propagator, rt_suppressor};
enum method_type { mt_daley, mt_maki, mt_maki_linear};

// Reads and returns a number and makes sure it's valid
int read_number();
// Runs a simulation of rumour spreading with the defined method and population size and logs the values to a file.
void rumour_simulation(vector<role_type>& population, int const size, method_type const method, string const& outputfile);

void main()
{
	cout << "Please enter the population size: ";
	int population_size(read_number());

	// Create the vector: Vector has standard value of nitwit (because nitwit = 0) and therefore doesn't have to be initialized.
	vector<role_type> population(population_size);
	// We set the first person in the vector to propagator. It literally doesn't matter where we place it.
	population[0] = rt_propagator;

	if (population_size > 10000)
	{
		cout << "Please wait! Based on the entered number this can take a while...\n";
	}
	rumour_simulation(population, population_size, mt_daley, "output.csv");
}

void rumour_simulation(vector<role_type>& population, int const size, method_type const method, string const& outputfile)
{
	// Normal rand function can only return numbers up to about 32000.
	// That's why another random function is needed.
	random_device rand_dev;
	mt19937 rand_gen(rand_dev());
	uniform_real_distribution<> rand_distrib(0, size);

	// We start with one propagator amidst nitwits.
	int propagators(1);
	int nitwits(size - 1);
	int suppressors(0);

	ofstream out(outputfile);
	out << "\"nitwits\";\"propagators\";\"suppressors\"\n";

	while (nitwits > 0 && propagators > 0)
	{
		// Choose the first person. For maki_linear method, this will always be a propagator
		int p1_index(rand_distrib(rand_gen));
		if (method == mt_maki_linear)
		{
			if (propagators >= 1)
			{
				int index(0);
				while (population[p1_index] != rt_propagator)
				{
					p1_index = index;
					index++;
				}
			}
		}

		// Choose the 2nd person, this cannot be the same as the first.
		int p2_index(rand_distrib(rand_gen));
		while (p1_index == p2_index)
		{
			p2_index = rand_distrib(rand_gen);
		}

		if (population[p1_index] == rt_propagator && population[p2_index] == rt_nitwit)
		{
			population[p2_index] = rt_propagator;
			propagators++;
			nitwits--;
		}
		else if (population[p1_index] == rt_nitwit && population[p2_index] == rt_propagator)
		{
			population[p1_index] = rt_propagator;
			propagators++;
			nitwits--;
		}
		// If both persons are propagators:
		// Daley: Both become suppressors
		// Maki: Only one becomes a suppressor
		else if (population[p1_index] == rt_propagator && population[p2_index] == rt_propagator)
		{
			population[p1_index] = rt_suppressor;
			suppressors += 1;
			propagators -= 1;

			if (method == mt_daley)
			{
				population[p2_index] = rt_suppressor;
				suppressors += 1;
				propagators -= 1;
			}
		}
		else if (population[p1_index] == rt_propagator && population[p2_index] == rt_suppressor)
		{
			population[p1_index] = rt_suppressor;
			propagators--;
			suppressors++;
		}
		else if (population[p1_index] == rt_suppressor && population[p2_index] == rt_propagator)
		{
			population[p2_index] = rt_suppressor;
			suppressors++;
			propagators--;
		}

		out << to_string(nitwits) + ";" + to_string(propagators) + ";" + to_string(suppressors) + "\n";
	}
	out.close();

	// Print the endresult to the console.
	cout << "nitwits: " << setw(20-7) << fixed << setprecision(1) << nitwits * 100.0 / size << "%\n";
	cout << "propagators: " << setw(20 - 11) << fixed << setprecision(1) << propagators * 100.0 / size << "%\n";
	cout << "suppressors: " << setw(20 - 11) << fixed << setprecision(1) << suppressors * 100.0 / size << "%";
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
*/