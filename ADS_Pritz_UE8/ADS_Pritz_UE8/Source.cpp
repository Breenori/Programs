
/*#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<time.h>
using namespace std;

enum role_type {nitwit, propagator, suppressor};

void main()
{
	int n = 1000000;
	vector<role_type> population(n);
	
	for (size_t i(0); i < n; i++)
	{
		population[i] = nitwit;
	}


	srand((int)time(0));
	population[rand() % n] = propagator;

	int propagators(1);
	int nitwits(n - 1);
	int suppressors(0);

	ofstream out("output1.csv");
	out.imbue(locale("de"));
	out << "\"nitwits\";\"propagators\";\"suppressors\"\n";
	while(nitwits > 0 && propagators > 0)
	{
		int p1_index = rand() % n;
		int p2_index = rand() % n;

		while (p2_index == p1_index)
		{
			p2_index = rand() % n;
		}
		

		if (population[p1_index] == propagator && population[p2_index] == nitwit)
		{
			population[p2_index] = propagator;
			propagators++;
			nitwits--;
		}
		else if (population[p2_index] == propagator && population[p1_index] == nitwit)
		{
			population[p1_index] = propagator;
			propagators++;
			nitwits--;
		}
		else if (population[p1_index] == propagator && population[p2_index] == propagator)
		{
			population[p1_index] = suppressor;
			population[p2_index] = suppressor;
			suppressors+=2;
			propagators-=2;
			//suppressors += 1;
			//propagators -= 1;
		}
		else if (population[p1_index] == propagator && population[p2_index] == suppressor)
		{
			population[p1_index] = suppressor;
			propagators--;
			suppressors++;
		}
		else if (population[p2_index] == propagator && population[p1_index] == suppressor)
		{
			population[p2_index] = suppressor;
			suppressors++;
			propagators--;
		}

		out << nitwits << ";" << propagators << ";" << suppressors << std::endl;
	}
	out.close();

	cout << (nitwits*1.0)/n << ";" << (propagators*1.0)/n << ";" << (suppressors*1.0)/n << std::endl;
}
*/