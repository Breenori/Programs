#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<time.h>
using namespace std;

enum role_type { nitwit, propagator, suppressor };

void main()
{
	int n = 100000;

	srand((int)time(0));

	int propagators(1);
	int nitwits(n - 1);
	int suppressors(0);

	ofstream out("outputi.csv");
	out.imbue(locale("de"));

	string text("");
	text += "\"nitwits\";\"propagators\";\"suppressors\"\n";
	while (propagators > 0 && nitwits > 0)
	{
		int p1_index = rand() % (propagators + nitwits + suppressors);
		int p2_index = rand() % (propagators + nitwits + suppressors);

		while (p2_index == p1_index)
		{
			p2_index = rand() % n;
		}

		role_type person1;
		if (p1_index < nitwits)
		{
			person1 = nitwit;
		}
		else if (p1_index < (nitwits + propagators))
		{
			person1 = propagator;
		}
		else
		{
			person1 = suppressor;
		}

		role_type person2;
		if (p2_index < nitwits)
		{
			person2 = nitwit;
		}
		else if (p2_index < (nitwits + propagators))
		{
			person2 = propagator;
		}
		else
		{
			person2 = suppressor;
		}

		if (person1 == propagator && person2 == nitwit || person1 == nitwit && person2 == propagator)
		{
			propagators++;
			nitwits--;
		}
		else if (person1 == propagator && person2 == propagator)
		{
			suppressors += 2;
			propagators -= 2;
		}
		else if (person1 == propagator && person2 == suppressor || person1 == suppressor && person2 == propagator)
		{
			propagators--;
			suppressors++;
		}

		//out << nitwits << ";" << propagators << ";" << suppressors << std::endl;
		text += nitwits;
		text += ";";
		text += propagators;
		text += ";";
		text += suppressors;
		text += "\n";

		if (text.length() > 10000)
		{
			out << text;
			text.clear();
		}
		//cout << (nitwits * 1.0) / n << ";" << (propagators * 1.0) / n << ";" << (suppressors * 1.0) / n << std::endl;
	}
	out << text;
	out.close();

	cout << (nitwits * 1.0) / n << ";" << (propagators * 1.0) / n << ";" << (suppressors * 1.0) / n << std::endl;
}